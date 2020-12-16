#include <iostream>
using namespace std;

class A {
	int num;
public:
	A(int num = 0) : num(num) {}
	void update() { cout << "Update A, num =" << num << endl; }
};

class B :public A {
	int num;
public:
	B(int num = 0) : num(num) {}
	virtual void update() { cout << "Update B, num =" << num << endl; }
	virtual void child() { cout << "child can implement this\n"; }
};

class C {
	int num;
public:
	C(int num = 0) : num(num) {}
	virtual void update() { cout << "Update C, num =" << num << endl; }
};

class D : public B, public C {
	int num;
public:
	D(int num = 0) : num(num) {}
	virtual void update() { cout << "Update D, num =" << num << endl; }
};

int main() {
	A* pa = new A(10);
	B b(20); // b ��ü�� ������� �� A Ŭ���� ������ ���� �� B Ŭ���� ������ ����
	B* pb;

	pa->update();
	delete pa;

	pa = &b; // ��ĳ����
	pa->update(); // b ��ü���� A Ŭ���� ������ ���ԵǾ��ִ�. A Ŭ������ update �Լ��� virtual �� �ƴϹǷ�
	// A Ŭ������ num ������ update �Լ����� ������ �� �ִ�.
	
	pb = (B*)pa; // �ٿ�ĳ����
	pb->update(); // pb �� B Ŭ�������̹Ƿ� B Ŭ������ �޼ҵ忡 ������ �� �ִ�.
	pb->child();

	// dynamic_cast�� �������� �ƴ� ���α׷� ���� ���� ĳ�����ϴ� ���� ���Ѵ�. �̸� �״�� ����ĳ����
	C* pc = dynamic_cast<C*>(new D(40));
	pc->update();
	pb = dynamic_cast<B*>(pc);
	// C Ŭ������ B Ŭ������ �ڽ��� �ƴ����� pc �� ����Ű�� �ִ� ��ü�� B �� ����� �޴� D �̹Ƿ� ���������� ��ĳ���� �ȴ�.
	pb->update();

	delete pb;

	// � �����͵� ������ ����ȯ ���ѹ����� reinterpret_cast�� �������� ���� ��ŭ ���輺�� �����ϰ� �ִ�.
	pb = reinterpret_cast<B*>(new C(30));
	// B�� C�� ���� ��Ӱ��赵 �ƴ� ��ٸ� �������� ���� ����ȯ�� ���� B�� C������ ������ �� �ֵ��� �Ͽ���.
	pb->update();

	return 0;
}