// https://www.acmicpc.net/problem/15997
#include <iostream>
#include <string>
#include <algorithm>
#include <numeric>

using namespace std;

/*
	���� ���� ��Ȳ������ ���� ���� ���� ����� ��

	1. 4�� ���� -> Ȯ�� 1/2
	2. 3�� ����
		1. ���� 3�� ���� -> ���� 3���� ���� ��� Ȯ�� 2/3
		2. ���� 3�� ���� -> ���� 3���� ���� ��� Ȯ�� 1/3
	3. 2�� �� 1�� ������ �������.

*/

double match[6][5] = { {0, 1, 0.7, 0.0, 0.3},
						{0, 2, 0.4, 0.1, 0.5},
						{0, 3, 0.2, 0.5, 0.3},
						{1, 2, 0.1, 0.2, 0.7},
						{1, 3, 0.0, 0.5, 0.5},
						{2, 3, 0.0, 1.0, 0.0} };

// �� ���� ���� ���忡 ������ Ȯ��(��� ���༼�迡���� Ȯ�� ����)
double goProb[4] = { 0, 0, 0, 0 };

void cal(int order, int* score, double accruedProb)
{
	if (order == 6)
	{
		pair<int*, int*> minmaxPair = minmax_element(score, score + 4);
		int sumOfScore = accumulate(score, score + 4, 0);

		// ��� ���� ������ ���� ���
		if (score[0] == score[1] == score[2] == score[3])
			for (int i = 0; i < 4; i++)
				goProb[i] += accruedProb * 0.5;

		// ���� 3���� ������ ���� ���
		else if (*minmaxPair.second * 3 + *minmaxPair.first == sumOfScore)
			for (int i = 0; i < 4; i++)
				if (score[i] == *minmaxPair.second)
					goProb[i] += accruedProb * ((double)2 / (double)3);

		// ���� 3���� ������ ���� ���
				else if (*minmaxPair.first * 3 + *minmaxPair.second == sumOfScore)
					for (int i = 0; i < 4; i++)
						if (score[i] == *minmaxPair.first)
							goProb[i] += accruedProb * ((double)1 / (double)3);

		// �ƹ� ���ܿ��� �ش����� �ʴ� ��� ���� ���� 2���� ���� ���� ����
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