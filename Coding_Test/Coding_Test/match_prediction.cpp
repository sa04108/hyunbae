// https://www.acmicpc.net/problem/15997
#include <iostream>
#include <string>
#include <algorithm>
#include <numeric>

using namespace std;

/*
	승점 동점 상황에서의 다음 라운드 진출 경우의 수

	1. 4팀 동점 -> 확률 1/2
	2. 3팀 동점
		1. 상위 3팀 동점 -> 상위 3팀에 속한 경우 확률 2/3
		2. 하위 3팀 동점 -> 하위 3팀에 속한 경우 확률 1/3
	3. 2팀 및 1팀 동점은 상관없음.

*/

double match[6][5] = { {0, 1, 0.7, 0.0, 0.3},
						{0, 2, 0.4, 0.1, 0.5},
						{0, 3, 0.2, 0.5, 0.3},
						{1, 2, 0.1, 0.2, 0.7},
						{1, 3, 0.0, 0.5, 0.5},
						{2, 3, 0.0, 1.0, 0.0} };

// 각 팀이 다음 라운드에 진출할 확률(모든 평행세계에서의 확률 총합)
double goProb[4] = { 0, 0, 0, 0 };

void cal(int order, int* score, double accruedProb)
{
	if (order == 6)
	{
		pair<int*, int*> minmaxPair = minmax_element(score, score + 4);
		int sumOfScore = accumulate(score, score + 4, 0);

		// 모든 팀의 승점이 같은 경우
		if (score[0] == score[1] == score[2] == score[3])
			for (int i = 0; i < 4; i++)
				goProb[i] += accruedProb * 0.5;

		// 상위 3팀의 승점이 같은 경우
		else if (*minmaxPair.second * 3 + *minmaxPair.first == sumOfScore)
			for (int i = 0; i < 4; i++)
				if (score[i] == *minmaxPair.second)
					goProb[i] += accruedProb * ((double)2 / (double)3);

		// 하위 3팀의 승점이 같은 경우
				else if (*minmaxPair.first * 3 + *minmaxPair.second == sumOfScore)
					for (int i = 0; i < 4; i++)
						if (score[i] == *minmaxPair.first)
							goProb[i] += accruedProb * ((double)1 / (double)3);

		// 아무 예외에도 해당하지 않는 경우 승점 상위 2팀이 다음 라운드 진출
		int temp[4];
		for (int i = 0; i < 4; i++)
			temp[i] = score[i];
		sort(temp, temp + 4);
		
		int maxIndex = minmaxPair.first - score;
		goProb[maxIndex] += accruedProb;

		for (int i = 0; i < 4; i++)
		{
			if (score[i] == temp[1])
			{
				goProb[i] += accruedProb;
				break;
			}
		}
		return;
	}

	// win
	accruedProb *= match[order][2];
	score[(int)match[order][0]] += 3;
	cal(order + 1, score, accruedProb);

	// draw
	accruedProb *= match[order][3];
	score[(int)match[order][0]] += 1;
	score[(int)match[order][1]] += 1;
	cal(order + 1, score, accruedProb);

	// lose
	accruedProb *= match[order][4];
	score[(int)match[order][1]] += 3;
	cal(order + 1, score, accruedProb);
}

int main()
{
	int score[4] = { 0, 0, 0, 0 };
	cout.fixed;
	cout.precision(10);

	cal(0, score, 1);

	for (int i = 0; i < 4; i++)
	{
		cout << goProb[i] << endl;
	}
}

/*
	test#1

	<input>
	A B C D
	A B 0.7 0.0 0.3
	A C 0.4 0.1 0.5
	A D 0.2 0.5 0.3
	B C 0.1 0.2 0.7
	B D 0.0 0.5 0.5
	C D 0.0 1.0 0.0

	<output>
	0.5537000000
	0.1630000000
	0.6779666667
	0.6053333333
*/