#include <iostream>
using namespace std;

int main(void)
{
	unsigned int t, d;
	unsigned int x = 0;
	unsigned int y = 1;
	int sum;
	int i = 0;

	cin >> t;
	int* result = new int[t];

	for (int j = 0; j < t; j++)
	{
		sum = 0;
		i = 0;

		cin >> x >> y;

		if (y > x)
		{
			d = y - x;

			while (d - sum * 2 >= i * 2 + 2)
			{
				sum += ++i;
			}

			if (d == 1)
				result[j] = 1;
			else if (d == sum * 2)
				result[j] = i * 2;
			else if (d - sum * 2 >= 1 && d - sum * 2 < i + 2)
				result[j] = i * 2 + 1;
			else
				result[j] = i * 2 + 2;
		}
		else
			result[j] = -1;
	}

	for (int k = 0; k < t; k++)
	{
		cout << result[k] << '\n';
	}

	delete[] result;

	return 0;
}