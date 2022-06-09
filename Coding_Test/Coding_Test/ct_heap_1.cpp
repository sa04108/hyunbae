#include <string>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

int solution(vector<int> scoville, int K) {
    int first, second, mix;
    int answer = -1;
    priority_queue<int, vector<int>, greater<int>> h;

    // initialize priority queue
    for (unsigned int i = 0; i < scoville.size(); i++)
    {
        h.push(scoville[i]);
    }

    for (unsigned int i = 1; h.size() >= 2; i++)
    {
        first = h.top(); h.pop();
        second = h.top(); h.pop();

        mix = first + second * 2;
        h.push(mix);

        if (h.top() >= K)
        {
            answer = i;
            break;
        }
    }

    return answer;
}

int main()
{
    vector<int> v;

    v.push_back(24);
    v.push_back(2);
    v.push_back(21);
    v.push_back(6);
    v.push_back(23);
    v.push_back(27);
    v.push_back(4);
    v.push_back(13);
    v.push_back(15);
    v.push_back(8);
    v.push_back(17);

    int k = 250;

    cout << solution(v, k);
}