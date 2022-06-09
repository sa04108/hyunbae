#include <iostream>
#include <string>
#include <conio.h>

using namespace std;

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define ESC 27

int main()
{
	string s;
	int n;
	cin >> n;

	for (int i = 0; i < n; i++)
	{
		s.push_back('A');
	}

	string::iterator it = s.begin();
	s.insert(it, '_');

	system("cls");
	cout << s;

	char c;

	while (true)
	{
		c = _getch();
		if (c == ESC) exit(1);
		else if (c == -32)
		{
			c = _getch();
			system("cls");
			switch (c)
			{
			case UP:
				if (*(it + 1) == 'Z')
					*(it + 1) = 'A';
				else
					*(it + 1) += 1;
				cout << s;
				break;
			case DOWN:
				if (*(it + 1) == 'A')
					*(it + 1) = 'Z';
				else
					*(it + 1) -= 1;
				cout << s;
				break;
			case LEFT:
				if (it == s.begin())
				{
					s.erase(it);
					it = s.insert(s.end() - 1, '_');
				}
				else
				{
					it = s.erase(it);
					it = s.insert(it - 1, '_');
				}
				cout << s;
				break;
			case RIGHT:
				if (it == s.end() - 2)
				{
					s.erase(it);
					it = s.insert(s.begin(), '_');
				}
				else
				{
					it = s.erase(it);
					it = s.insert(it + 1, '_');
				}
				cout << s;
				break;
			default:
				cout << c << endl;
				break;
			}
		}
	}
}