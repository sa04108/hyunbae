#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

void increase(int& a, int& b)
{
	a++; b++;
}

void decrease(int& a, int& b)
{
	a--; b--;
}

int gcd(int a, int b) {
	while (b != 0) {
		int r = a % b;
		a = b;
		b = r;
	}
	return a;
}

int main()
{
	int num, a, b;

	cin >> num;
	vector<vector<int>> answer(num);

	for (int i = 0; i < num; i++)
	{
		cin >> a >> b;
		answer[i].push_back(a);
		answer[i].push_back(b);
	}

	// solution
	for (int i = 0; i < num; i++)
	{
		cout << answer[i].front() << " " << abs(answer[i].front() - answer[i].back()) << endl;
	}

	return 0;
}