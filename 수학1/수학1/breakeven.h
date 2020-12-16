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
	cout << "손익분기점 프로그램 종료" << '\n';
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
	cout << "고정비용 : " << staticcost << '\n' << "노트북 1대당 비용 : " << notebookcost << '\n' << "노트북 1대당 가격 : " << notebookprice << '\n' << "손익분기점 판매량 : " << notebookSales() << '\n';
}