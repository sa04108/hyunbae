#include <string>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

int solution(vector<int> priorities, int location) {
    int answer = 0;
    priority_queue<int> h;

    for (unsigned int i = 0; i < priorities.size(); i++)
    {
        h.push(priorities[i]);
    }

    while (!priorities.empty())
    {
        if (priorities.front() == h.top()) {
            answer++;
            if (location == 0)
                break;
            h.pop();
        }
        else
            priorities.push_back(priorities.front());

        priorities.erase(priorities.begin());
        location--;
        if (location == -1)
            location = priorities.size() - 1;
    }
    
    return answer;
}

int main()
{
    vector<int> p;
    p.push_back(2);
    p.push_back(1);
    p.push_back(3);
    p.push_back(2);

    cout << solution(p, 3);
}