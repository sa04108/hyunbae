#include <iostream>
using namespace std;

class Game
{
public:
	Game(int _n, int** _a, int _r);
	~Game();

	void GetLeft(); // 좌로 밀착
	void GetDown(); // 하로 밀착
	void GetRight(); // 우로 밀착
	void GetUp(); // 상으로 밀착

	void prtGame(); // 게임판 출력
	void forMax(int _r);
	int rtrnMax(); // n번 밀착 후 가능한 게임판 내 최대값 반환

private:
	int n;
	int** a;
	int** b;
	int*** temp;
	int r;

	int max;

	void PushLeft(); // 밀착 (기본: 좌방향)
	void turnLeft(); // 게임판 좌회전
	void turnRight(); // 게임판 우회전
	void turnHalf(); // 게임판 반바퀴회전
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
			temp[i][j] = new int[n];
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


// 밀착 (기본: 좌방향)
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

// 좌회전
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

// 우회전
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

// 180도 회전
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



// 좌로 밀착
void Game::GetLeft()
{
	PushLeft();
}

// 하로 밀착
void Game::GetDown()
{
	turnRight();
	PushLeft();
	turnLeft();
}

// 우로 밀착
void Game::GetRight()
{
	turnHalf();
	PushLeft();
	turnHalf();
}

// 상으로 밀착
void Game::GetUp()
{
	turnLeft();
	PushLeft();
	turnRight();
}

// 게임판 출력
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

// n번 밀착 후 가능한 게임판 내 최대값 반환
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

int main()
{
	int n;
	cin >> n;

	int** a = new int* [n];
	for (int i = 0; i < n; i++)
	{
		a[i] = new int[n];
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> a[i][j];
		}
	}

	Game g(n, a, 5);
	g.forMax(5);

	cout << g.rtrnMax();

	return 0;
}