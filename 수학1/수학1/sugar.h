#pragma once
#include <iostream>
using namespace std;

class Sugar
{
public:
	Sugar(int _kg);
	void prt();

private:
	int kg;
	int nresult = 0;
	int result = 0;
};

Sugar::Sugar(int _kg):kg(_kg)
{
}

void Sugar::prt()
{
	result = kg;

	for (int q5 = 0; 5 * q5 <= kg; q5++)
	{
		for (int q3 = 0; 3 * q3 <= kg; q3++)
		{
			if (5 * q5 + 3 * q3 == kg)
			{
				nresult = q5 + q3;
				if (result > nresult)
					result = nresult;
			}
		}
	}

	if (!nresult)
		result = -1;
	cout << result;
}