#pragma once
#include <iostream>
using namespace std;

class Breakeven
{
public:
	Breakeven(int s, int d, int p);
	~Breakeven();
	int notebookSales();
	void prt();

private:
	int staticcost;
	int notebookcost;
	int notebookprice;
};

Breakeven::Breakeven(int s, int c, int p):staticcost(s), notebookcost(c), notebookprice(p)
{
}

Breakeven::~Breakeven()
{
	cout << "���ͺб��� ���α׷� ����" << '\n';
}

int Breakeven::notebookSales()
{
	if (notebookprice <= notebookcost)
		return -1;
	else
		return staticcost / (notebookprice - notebookcost) + 1;
}

void Breakeven::prt()
{
	cout << "������� : " << staticcost << '\n' << "��Ʈ�� 1��� ��� : " << notebookcost << '\n' << "��Ʈ�� 1��� ���� : " << notebookprice << '\n' << "���ͺб��� �Ǹŷ� : " << notebookSales() << '\n';
}