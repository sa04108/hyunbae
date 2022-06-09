#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

vector<int> solution(vector<int> array, vector<vector<int>> commands) {
    vector<int> answer;
    vector<int> temp;
    int start, end;
    
    for (auto command : commands)
    {
        start = command[0] - 1;
        end = command[1] - 1;
        temp.assign(array.begin() + start, array.begin() + end + 1); // pointer 연산, end를 end()처럼 사용하기 위해 +1을 한다.
        sort(temp.begin(), temp.end());
        answer.push_back(temp[command[2] - 1]);
    }

    return answer;
}

int main()
{
    vector<int> array = { 1, 5, 2, 6, 3, 7, 4 };
    vector<vector<int>> commands = { {2, 5, 3}, {4, 4, 1}, {1, 7, 3} };

    vector<int> answer = solution(array, commands);

    cout << "[ ";
    for (auto element : answer)
        cout << element << ", ";
    cout << "\b\b ]\n";
}