#include <string>
#include <vector>
#include <iostream>

using namespace std;

int numOfPrimeNum = 0;

bool isPrimeNum(int num)
{
	for (int i = 2; i < num; i++)
	{
		if (num % i == 0)
			return false;
	}
	return true;
}

void searchString(string numbers, string temp = "")
{
	for (string::iterator it = numbers.begin(); it != numbers.end(); it++)
	{
		temp.push_back(*it);
		searchString(numbers, temp);

		if (temp.size() == numbers.size())
			if (isPrimeNum(stoi(temp)))
				numOfPrimeNum++;

		temp.clear();
	}
}

int solution(string numbers) {
    int answer = 0;


    return answer;
}

int main()
{
	string s = "1234";
	searchString(s);
}