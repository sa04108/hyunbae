#include <iostream>
#include <conio.h>
#include <random>
#include <cmath>
using namespace std;

enum Arrow { KEY_LEFT = 75, KEY_RIGHT = 77, KEY_UP = 72, KEY_DOWN = 80, KEY_SPACE = 32 };

class Game
{
public:
	Game(int _n, int** _a, int _r);
	~Game();

	void GetLeft(); // �·� ����
	void GetDown(); // �Ϸ� ����
	void GetRight(); // ��� ����
	void GetUp(); // ������ ����

	void prtGame(); // ������ ���
	void forMax(int _r);
	int rtrnMax(); // n�� ���� �� ������ ������ �� �ִ밪 ��ȯ
	void resetGame(); // ������ ����

private:
	int n;
	int** a;
	int** b;
	int*** temp;
	int r;

	int max;

	void PushLeft(); // ���� (�⺻: �¹���)
	void turnLeft(); // ������ ��ȸ��
	void turnRight(); // ������ ��ȸ��
	void turnHalf(); // ������ �ݹ���ȸ��
};

Game::Game(int _n, int** _a, int _r)
{
	n = _n;
	r = _r;
	max = 0;

	a = new int* [n];
	for (int i = 0; i < n; i++)
	{
		a[i] = new int[n];
	}

	for (int i = 0; i < n; i++)
	{
		a[i] = _a[i];
	}
	a = _a;

	b = new int* [n];
	for (int i = 0; i < n; i++)
	{
		b[i] = new int[n];
	}

	temp = new int** [r];
	for (int i = 0; i < r; i++)
	{
		temp[i] = new int* [n];
		for (int j = 0; j < n; j++)
		{
			temp[i][j] = new int [n];
		}
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			temp[r - 1][i][j] = a[i][j];
		}
	}
}

Game::~Game()
{
	for (int i = 0; i < n; i++)
	{
		delete[] a[i];
	}
	delete[] a;

	for (int i = 0; i < n; i++)
	{
		delete[] b[i];
	}
	delete[] b;

	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < n; j++)
		{
			delete[] temp[i][j];
		}
		delete[] temp[i];
	}
	delete[] temp;
}


// ���� (�⺻: �¹���)
void Game::PushLeft()
{
	bool q = false;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n - 1; j++)
		{
			for (int k = j; k < n && !q; k++)
			{
				if (a[i][k] != 0)
				{
					for (int l = j; l < n - (k - j); l++)
					{
						a[i][l] = a[i][l + (k - j)];
						if (k > j)
						{
							a[i][l + (k - j)] = 0;
						}
					}

					if (k > j)
					{
						if (a[i][j] == a[i][j - 1])
						{
							a[i][j - 1] *= 2;
							for (int k = j; k < n - 1; k++)
							{
								a[i][k] = a[i][k + 1];
							}
							a[i][n - 1] = 0;
						}
					}

					q = true;
				}
			}
			q = false;

			if (a[i][j] == a[i][j + 1])
			{
				a[i][j] *= 2;
				for (int k = j + 1; k < n - 1; k++)
				{
					a[i][k] = a[i][k + 1];
				}
				a[i][n - 1] = 0;
			}
		}
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			b[i][j] = a[i][j];
		}
	}
}

// ��ȸ��
void Game::turnLeft()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			b[i][j] = a[j][n - 1 - i];
		}
	}
	
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			a[i][j] = b[i][j];
		}
	}
}

// ��ȸ��
void Game::turnRight()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			b[i][j] = a[n - 1 - j][i];
		}
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			a[i][j] = b[i][j];
		}
	}
}

// 180�� ȸ��
void Game::turnHalf()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			b[i][j] = a[n - 1 - i][n - 1 - j];
		}
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			a[i][j] = b[i][j];
		}
	}
}



// �·� ����
void Game::GetLeft()
{
	PushLeft();
}

// �Ϸ� ����
void Game::GetDown()
{
	turnRight();
	PushLeft();
	turnLeft();
}

// ��� ����
void Game::GetRight()
{
	turnHalf();
	PushLeft();
	turnHalf();
}

// ������ ����
void Game::GetUp()
{
	turnLeft();
	PushLeft();
	turnRight();
}

// ������ ���
void Game::prtGame()
{
	cout << '\n';

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << a[i][j] << "	";
		}
		cout << '\n' << '\n';
	}
}

void Game::forMax(int _r)
{
	for (int i = 0; i < 4; i++)
	{
		switch (i)
		{
		case 0:
			GetLeft();
			break;
		case 1:
			GetDown();
			break;
		case 2:
			GetRight();
			break;
		case 3:
			GetUp();
			break;
		}

		if (_r <= 1)
		{
			rtrnMax();
			for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < n; j++)
				{
					a[i][j] = temp[_r - 1][i][j];
				}
			}
		}
		else
		{
			for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < n; j++)
				{
					temp[_r - 2][i][j] = a[i][j];
				}
			}
			forMax(_r - 1);
		}
	}

	for (int i = 0; i < n && _r < r; i++)
	{
		for (int j = 0; j < n; j++)
		{
			a[i][j] = temp[_r][i][j];
		}
	}
}

// n�� ���� �� ������ ������ �� �ִ밪 ��ȯ
int Game::rtrnMax()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (a[i][j] > max)
				max = a[i][j];
		}
	}

	return max;
}

void Game::resetGame()
{
	int st;

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(1, 20);

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			st = dis(gen);
			if (st < 11)
				a[i][j] = pow(2, st);
			else
				a[i][j] = 0;
		}
	}
}

int main()
{
	int n;

	cout << "1 ~ 20 ������ ���� �Է� (�Է°� n*n �� ũ�⸦ ������ ������ ����)" << '\n';
	cin >> n;


	int** a = new int* [n];
	for (int i = 0; i < n; i++)
	{
		a[i] = new int[n];
	}

	Game g(n, a, 5);
	g.resetGame();
	g.prtGame();

	cout << "����Ű�� ���� �̵�, �����̽���: ����" << '\n';

	while (true)
	{
		switch (_getch())
		{
		case KEY_LEFT:
			g.GetLeft();
			g.prtGame();
			break;
		case KEY_RIGHT:
			g.GetRight();
			g.prtGame();
			break;
		case KEY_UP:
			g.GetUp();
			g.prtGame();
			break;
		case KEY_DOWN:
			g.GetDown();
			g.prtGame();
			break;
		case KEY_SPACE:
			g.resetGame();
			g.forMax(5);
			cout << g.rtrnMax();
			g.prtGame();
			break;
		}
	}

	return 0;
}