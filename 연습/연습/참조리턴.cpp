#include <iostream>
using namespace std;

char c = 'a';

char& find() // ���� ���� �Լ�, ��ȯ���� char �������̴�. ��, find() �� c �� ����.
{
	return c;
}

int main()
{
	char& a = find(); // c�� ������ ���� �������̹Ƿ� a, find(), c �� ��� ���� ������ �����Ѵ�.
	a = 'b';
	cout << c << '\n'; // 'b'�� ��µȴ�.

	find() = 'c';
	cout << c << '\n'; // 'c'�� ��µȴ�.

	char b = find(); // c�� ������ find()�� 'c'�� ������ �ִ�. ���� b�� c�� ���� 'c'�� ������.
	cout << b << '\n';
}