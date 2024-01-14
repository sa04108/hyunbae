#include <iostream>
using namespace std;

class MyClass
{
	int arr[10];

public:
	MyClass() {
		for (int i = 0; i < 10; i++)
		{
			arr[i] = i + 1;
		}
	}
	~MyClass() { delete[] arr; }
	void plusArr() { arr++; }
	void getArr() { cout << *arr << '\n'; }
};

int main()
{
	MyClass a;
	
	a.getArr();
	a.plusArr();
	a.getArr();
}