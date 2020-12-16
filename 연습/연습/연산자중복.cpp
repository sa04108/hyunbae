#include <iostream>
#include <string>
using namespace std;

class Sample {
	int num;
	string str;
public:
	Sample(int num = 0, string str = "�⺻��")
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
	Sample a(5, "�˷ϴ޷�");
	Sample b(10, " ������");
	Sample c;

	c = (a += b); // ġȯ ���� + '+='�� �������� ����

	cout << c.getNum() << '\n' << c.getStr() << '\n';
}