#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main()
{
	string str;
	vector<string> v;
	vector<string>::iterator it;
	
	for (int i = 0; i < 3; i++)
	{
		getline(cin, str);
		v.push_back(str);
	}

	for (it = v.begin(); it != v.end(); it++)
	{
		cout << *it;
	}

	vector<string> v2;
	v2 = v; // = �����ڴ� vector Ŭ�������� ������ ġȯ�� �ǹ��ϵ��� �����ǵ�.

	for (it = v2.begin(); it != v2.end(); it++)
	{
		cout << *it;
	}

	it = v.begin();
	it = v.erase(it); // erase�� it�� ����Ű�� �ε����� ����� ���� �ε��� ������ �����Ѵ�. ���� begin()�� ������Ƿ� �� ���� ������ it�� �����ؾ��Ѵ�.
	
	for (it = v.begin(); it != v.end(); it++)
	{
		cout << *it;
	}
}