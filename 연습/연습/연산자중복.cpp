#include <iostream>
#include <string>
using namespace std;

class Sample {
	int num;
	string str;
public:
	Sample(int num = 0, string str = "기본값")
	{
		this->num = num;
		this->str = str;
	}
	Sample operator += (Sample b)
	{
		this->num = num + b.num;
		this->str = str + b.str;
		return *this;
	}
	int getNum() { return num; }
	string getStr() { return str; }
};

int main()
{
	Sample a(5, "알록달록");
	Sample b(10, " 무지개");
	Sample c;

	c = (a += b); // 치환 연산 + '+='을 재정의한 연산

	cout << c.getNum() << '\n' << c.getStr() << '\n';
}