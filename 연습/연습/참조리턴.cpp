#include <iostream>
using namespace std;

char c = 'a';

char& find() // 참조 리턴 함수, 반환형은 char 참조형이다. 즉, find() 는 c 의 참조.
{
	return c;
}

int main()
{
	char& a = find(); // c의 참조에 대한 참조자이므로 a, find(), c 는 모두 같은 공간을 공유한다.
	a = 'b';
	cout << c << '\n'; // 'b'가 출력된다.

	find() = 'c';
	cout << c << '\n'; // 'c'가 출력된다.

	char b = find(); // c의 참조인 find()는 'c'를 가지고 있다. 따라서 b는 c의 값인 'c'를 가진다.
	cout << b << '\n';
}