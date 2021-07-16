#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

enum Coord
{
	X,
	Y
};

int main()
{
	int n, tmp;
	vector<int> answer;

	cin >> n; cout << endl;

	vector<vector<int>> a(n);
	vector<vector<int>> b(n);
	vector<vector<int>> f(n);

	// input
	for (int i = 0; i < n; i++)
	{
		cin >> tmp; a[i].push_back(tmp);
		cin >> tmp; a[i].push_back(tmp);

		cin >> tmp; b[i].push_back(tmp);
		cin >> tmp; b[i].push_back(tmp);

		cin >> tmp; f[i].push_back(tmp);
		cin >> tmp; f[i].push_back(tmp);
		cout << endl;
	}

	// solution
	for (int i = 0; i < n; i++)
	{
		int len = abs(a[i][X] - b[i][X]) + abs(a[i][Y] - b[i][Y]);

		if ((a[i][X] == b[i][X] && a[i][X] == f[i][X]) || (a[i][Y] == b[i][Y] && a[i][Y] == f[i][Y]))
		{
			if ((f[i][X] < max(a[i][X], b[i][X]) && f[i][X] > min(a[i][X], b[i][X])) ||
				(f[i][Y] < max(a[i][Y], b[i][Y]) && f[i][Y] > min(a[i][Y], b[i][Y])))
				answer.push_back(len + 2);
			else
				answer.push_back(len);
		}
		else
			answer.push_back(len);
	}

	// output
	for (auto num : answer)
		cout << num << endl;

	return 0;
}