#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int solution(int n, vector<int> lost, vector<int> reserve) {
    int answer = n;

    sort(lost.begin(), lost.end());
    sort(reserve.begin(), reserve.end());

    lost.push_back(0);
    reserve.push_back(0);

    vector<int>::iterator it_l = lost.begin();
    vector<int>::iterator it_r = reserve.begin();

    while (*it_l != 0 && *it_r != 0)
    {
        if (*it_r - 1 == *it_l || *it_r + 1 == *it_l)
        {
            if (*(it_l + 1) == *it_r)
            {
                it_l = lost.erase(it_l + 1);
                it_r++;
            }
            else if (*(it_r + 1) == *it_l)
            {
                it_l = lost.erase(it_l);
                it_r += 2;
            }
            else
            {
                it_l = lost.erase(it_l);
                it_r++;
            }
        }
        else if (*it_l == *it_r)
        {
            it_l = lost.erase(it_l);
            it_r++;
        }
        else if (*it_l > *it_r)
            it_r++;
        else
            it_l++;
    }

    answer -= (lost.size() - 1);

    return answer;
}

int main()
{
    int n = 5;
    vector<int> lost = { 1, 2, 3, 4, 5 };
    vector<int> reserve = { 1, 2, 3, 4, 5 };

    int answer = solution(n, lost, reserve);
    cout << answer;
}