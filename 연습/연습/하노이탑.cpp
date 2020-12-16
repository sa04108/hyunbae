#include <iostream>
using namespace std;

void hanoi(int n, char from, char tmp, char to)
{
	if (n == 1)
		cout << "���� 1�� " << from << "���� " << to << "�� �ű��." << '\n';
	else {
		hanoi(n - 1, from, to, tmp); // ���������� �߰������� �ű��.
		cout << "���� " << n << "�� " << from << "���� " << to << "�� �ű��." << '\n';
		hanoi(n - 1, tmp, from, to); // �߰������� ���������� �ű��.
	}
}

int main()
{
	hanoi(4, 'A', 'B', 'C');
}