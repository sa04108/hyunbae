#include <iostream>
#include <deque>

using namespace std;

int main()
{
	deque<int> dq(4);
	dq.push_back(3);
	dq.push_front(4);

	deque<int>::iterator it;
	for (it = dq.begin(); it != dq.end(); it++)
	{
		cout << *it << ' ';
	}
}