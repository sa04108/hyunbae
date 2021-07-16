#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iostream>

using namespace std;

bool compare(int a, int b)
{
    if (a <= 0 || b <= 0)
    {
        return a > b;
    }

    // true means ascending, sort a < b
    // false means descending, sort a > b
    int len_a = log10(a) + 1;
    int len_b = log10(b) + 1;

    int temp_a = a * pow(10, len_b) + b;
    int temp_b = b * pow(10, len_a) + a;

    return temp_a > temp_b;
}

string solution(vector<int> numbers) {
    string answer;
    sort(numbers.begin(), numbers.end(), compare);

    for (int num : numbers)
    {
        answer += to_string(num);
    }

    if (answer[0] == '0')
        return string{ '0' };

    return answer;
}

int main()
{
    vector<int> numbers = { 0, 0 };
    string ans = solution(numbers);

    cout << ans;
}