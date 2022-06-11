#include <iostream>
#include <string>
#include <vector>
#include <stack>

using namespace std;

vector<int> solution(vector<int> prices) {
    vector<int> answer(prices.size());
    stack<int> s;
    int size = prices.size();
    for (int i = 0; i < size; i++) {
        while (!s.empty() && prices[s.top()] > prices[i]) {
            answer[s.top()] = i - s.top();
            s.pop();
        }
        s.push(i);
    }
    while (!s.empty()) {
        answer[s.top()] = size - s.top() - 1;
        s.pop();
    }
    return answer;
}

int main() {
	vector<int> list = { 1,2,4,3,4,7,5,1,2 };
	vector<int> ans = solution(list);

	for (int i = 0; i < list.size(); i++)
	{
		cout << ans[i] << endl;
	}

	return 0;
}