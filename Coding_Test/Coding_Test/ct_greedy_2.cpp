#include <string>
#include <vector>
#include <iostream>

using namespace std;

int solution(string name) {
    int ud = 0;
    int lr = 0;
    int maxA = 0;

    for (auto i : name)
    {
        if (i < 'N')
            ud += (i - 'A');
        else
            ud += ('[' - i);
    }

    int left = 0;
    for (auto it = name.begin() + 1; it != name.end(); it++)
    {
        left++;
        if (*it != 'A')
            break;
    }
    left = name.length() - left;

    int right = 0;
    for (auto it = name.rbegin(); it != name.rend(); it++)
    {
        right++;
        if (*it != 'A')
            break;
    }
    right = name.length() - right;

    lr = min(left, right);

    string temp;
    temp.append(name.length(), 'A');
    size_t findPos = name.find(temp);
    while (findPos == string::npos)
    {
        temp.pop_back();
        findPos = name.find(temp);
    }

    int dualWay = name.length() * 2;
    if (!temp.empty())
    {
        left = findPos - 1;
        right = name.length() - (findPos + temp.length());
        int ltor = right * 2 + left;
        int rtol = left * 2 + right;
        dualWay = min(ltor, rtol);
    }

    lr = min(lr, dualWay);

    int answer = ud + lr;
    return answer;
}

int  main()
{
    // cout << solution("ABAAAAAAAAABB");
    cout << solution("AAABAAAAAAAAABA");
}