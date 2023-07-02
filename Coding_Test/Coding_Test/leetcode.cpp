#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdarg>
#include <cassert>
using namespace std;

struct ListNode {
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}
	ListNode(int _count, int ...) {
		assert(_count >= 0);
		va_list list;
		va_list copy;

		va_start(list, _count);
		va_copy(copy, list);
		
		val = (int)va_arg(copy, int);
		ListNode* it = this;
		for (int i = 0; i < _count - 1; i++) {
			ListNode* node = new ListNode((int)va_arg(copy, int));
			it->next = node;
			it = it->next;
		}

		va_end(list);
		va_end(copy);
	}
};

ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
	ListNode* it1 = l1;
	ListNode* it2 = l2;
	ListNode* answer = new ListNode(0);
	unsigned long long sum = 0;

	unsigned long long coeff = 1;
	// add each values of each lists into number
	while (it1 != nullptr || it2 != nullptr) {
		if (it1 != nullptr) {
			sum += it1->val * coeff;
			it1 = it1->next;
		}
		if (it2 != nullptr) {
			sum += it2->val * coeff;
			it2 = it2->next;
		}

		coeff *= 10;
	}
	delete it1;
	delete it2;

	ListNode* it = answer;
	while (sum > 0) {
		int i = sum % 10;
		it->next = new ListNode(i);
		it = it->next;
		sum /= 10;
	}
	if (answer->next != nullptr)
		answer = answer->next;

	return answer;
}

int main() {
	ListNode* l1 = new ListNode(31, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1);
	ListNode* l2 = new ListNode(3, 5, 6, 4);

	ListNode* answer = addTwoNumbers(l1, l2);
	while (answer != nullptr) {
		cout << answer->val << ' ';
		answer = answer->next;
	}
	cout << '\n';
}