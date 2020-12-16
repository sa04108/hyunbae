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
	v2 = v; // = 연산자는 vector 클래스에서 벡터의 치환을 의미하도록 재정의됨.

	for (it = v2.begin(); it != v2.end(); it++)
	{
		cout << *it;
	}

	it = v.begin();
	it = v.erase(it); // erase는 it가 가리키는 인덱스를 지우고 다음 인덱스 참조를 리턴한다. 기존 begin()은 사라지므로 새 참조 정보를 it에 전달해야한다.
	
	for (it = v.begin(); it != v.end(); it++)
	{
		cout << *it;
	}
}