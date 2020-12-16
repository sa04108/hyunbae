#include <iostream>
using namespace std;

int x = 10;
void y() { cout << 20 << endl; }

class A {
public:
	void func() { f(); }
	virtual void f() { cout << "A::f() called" << endl; }
	void y() { cout << 2 << endl; }
	void run() { y(); ::y(); }
};

class B : public A {
public:
	void f() { cout << "B::f() called" << endl; } // virtual Ű���� ��ӹ���.
	void onlyB() { cout << "this fuction belongs to B" << endl; }
};

class C : public B {
public:
	void f() { cout << "C::f() called" << endl; } // B �� ��ӹ��� virtual �� �Ȱ��� ��ӹ���.
	void onlyC() { cout << "this function belongs to C" << endl; }
};

int main()
{
	A* pa;
	A a;
	pa = &a;
	pa->func(); // A Ÿ�� �����Ͱ� A ��ü�� ����Ű�Ƿ� virtual ������� A�� ��� ȣ��
	pa->f();
	cout << endl;

	C c;
	pa = &c; // ��ĳ����
	pa->func();
	pa->f();
	pa->A::func();
	pa->A::f(); // �������������ڸ� ���� �⺻Ŭ���� �����Լ� ȣ��
	cout << endl;

	C* pc;
	pc = (C*)&a; // �ٿ�ĳ����, ����� ����ȯ �ʿ�
	pc->func();
	pc->f(); // ������ ������ ��ü ���� ���������� �ʰ� �θ� ��ü�� ���� ����Ű�Ƿ� virtual ������� �θ� ��ü ���� ����.
	cout << endl;

	B* pb;
	pb = &c; // ��ĳ����
	pb->func();
	cout << endl;

	a = c;
	a.func(); // �����Ͱ� �ƴ� ���, �� �� ġȯ�� �Ǵ� ��� virtual �� �ǹ� ����.

	// +�ǳ��� / �������������ڷ� ���� �� ���� ����, �Լ� ȣ���ϱ�
	int x = 1;

	cout << x << endl;
	cout << ::x << endl;
	a.run();
}