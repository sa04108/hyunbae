#include <iostream>
using namespace std;

void hanoi(int n, char from, char tmp, char to)
{
	if (n == 1)
		cout << "원판 1을 " << from << "에서 " << to << "로 옮긴다." << '\n';
	else {
		hanoi(n - 1, from, to, tmp); // 시작점에서 중간점으로 옮긴다.
		cout << "원판 " << n << "을 " << from << "에서 " << to << "로 옮긴다." << '\n';
		hanoi(n - 1, tmp, from, to); // 중간점에서 도착점으로 옮긴다.
	}
}

int main()
{
	hanoi(4, 'A', 'B', 'C');
}