#include <stdio.h> // c ���� ���
#include <iostream>
using namespace std; // c++ ���� ���

int noman, nilman, nochun, nilchun, nobek, nbek, nosip, nsip = 0;

int MoneyCalculator(int mc) {
	
	noman = mc / 50000;
	nilman = mc % 50000 / 10000;
	nochun = mc % 50000 % 10000 / 5000;
	nilchun = mc % 50000 % 10000 % 5000 / 1000;
	nobek = mc % 50000 % 10000 % 5000 % 1000 / 500;
	nbek = mc % 50000 % 10000 % 5000 % 1000 % 500 / 100;
	nosip = mc % 50000 % 10000 % 5000 % 1000 % 500 % 100 / 50;
	nsip = mc % 50000 % 10000 % 5000 % 1000 % 500 % 100 % 50 / 10;
	
	return mc % 10;
}

int main() {
	int money = 0;

	printf("�ݾ��� �Է��Ͻʽÿ�: ");

	scanf_s("%d", &money);

	MoneyCalculator(money);

	printf("������ ��: %d ��, ���� ��: %d ��, ��õ�� ��: %d ��, õ�� ��: %d ��, �����: %d ��, ���: %d ��, ���ʿ�: %d ��, �ʿ�: %d �� \n���� �� ���� �ݾ��� %d �� �Դϴ�.", noman, nilman, nochun, nilchun, nobek, nbek, nosip, nsip, MoneyCalculator(money));

	return 0;
}