#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

vector<int> pNums;

bool isPrimeNum(int num)
{
	for (int i = 2; i < sqrt(num); i++)
	{
		if (num % i == 0)
			return false;
	}
	return num <= 1 ? false : true;
}

void search(string leftNum, string checkNum, int count)
{
	for (unsigned int i = 0; i < leftNum.length(); i++)
	{
		string tmp1 = leftNum;
		string tmp2 = checkNum;
		tmp2.push_back(leftNum[i]);

		if (count == 0) {
			int n = stoi(tmp2);

			if (isPrimeNum(n))
				pNums.push_back(n);
		}
		else
		{
			tmp1.erase(i, 1);
			search(tmp1, tmp2, count - 1);
		}
	}
}

int solution(string numbers) {
	for (unsigned int i = 0; i < numbers.length(); i++)
	{
		search(numbers, "", i);
	}

	sort(pNums.begin(), pNums.end());

	vector<int>::iterator prev = pNums.begin();
	vector<int>::iterator it = prev + 1;

	while (it != pNums.end())
	{
		if (*prev == *it)
			it = pNums.erase(it);
		else
		{
			prev++;
			it++;
		}
	}

	int answer = pNums.size();
	return answer;
}

int main()
{
	cout << solution("111111");
}