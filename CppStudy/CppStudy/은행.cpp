#include <stdio.h> // c 참조 헤더
#include <iostream>
using namespace std; // c++ 참조 헤더

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

	printf("금액을 입력하십시오: ");

	scanf_s("%d", &money);

	MoneyCalculator(money);

	printf("오만원 권: %d 개, 만원 권: %d 개, 오천원 권: %d 개, 천원 권: %d 개, 오백원: %d 개, 백원: %d 개, 오십원: %d 개, 십원: %d 개 \n빼낼 수 없는 금액은 %d 원 입니다.", noman, nilman, nochun, nilchun, nobek, nbek, nosip, nsip, MoneyCalculator(money));

	return 0;
}