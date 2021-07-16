#include <string>
#include <vector>
#include <iostream>

using namespace std;

int solution(vector<int> numbers, int target) {
    int answer = 0;
    int size = 1 << numbers.size();

    for (int i = 1; i <= size; i++) {
        int temp = 0;
        for (int j = 0; j < numbers.size(); j++)
        {
            if (i & (1 << j)) {
                temp -= numbers[j];
            }
            else temp += numbers[j];
        }
        if (temp == target) answer++;
    }
    return answer;
}

int main()
{
	vector<int> v = { 1,2,2 };
	int t = 5;

	cout << solution(v, t) << endl;

	return 0;
}