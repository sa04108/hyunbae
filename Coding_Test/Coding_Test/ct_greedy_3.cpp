#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string solution(string number, int k) {
    string temp = number;
    string answer;
    int len = number.length();
    int max;
    int minIdx = -1;
    int restNum = len - k;

    sort(temp.begin(), temp.end(), greater<char>());

    for (int i = 0; i < len && restNum > 0; i++)
    {
        max = temp[i] - 48;
        int index = number.find(max + 48, minIdx + 1);
        if (index <= len - restNum)
        {
            answer.push_back(max + 48);
            minIdx = index;
            restNum--;
        }
        else
        {
            answer.append(number.substr(minIdx + 1, restNum));
        }
    }

    return answer;
}

int main(int argc, char* argv[])
{
    cout << solution("4224113", 3);

    return 0;
}