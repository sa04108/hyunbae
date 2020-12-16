#include <iostream>
#include <fcntl.h>
#include <io.h>
using namespace std;

int main()
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	wchar_t a[] = { L'█', L'Ç', L'ü', L'é', L'â', '\0' };
	wcout << a;
	wmemset(a, L'█', 5);
	wcout << a << '\n';
	wcout << "C++ 배우자 123 !@#$" << '\n';
	_setmode(_fileno(stdout), _O_TEXT);
	cout << "C++ 배우자 123 !@#$";
}