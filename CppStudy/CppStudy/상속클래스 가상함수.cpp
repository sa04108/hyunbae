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
	void f() { cout << "B::f() called" << endl; } // virtual 키워드 상속받음.
	void onlyB() { cout << "this fuction belongs to B" << endl; }
};

class C : public B {
public:
	void f() { cout << "C::f() called" << endl; } // B 가 상속받은 virtual 을 똑같이 상속받음.
	void onlyC() { cout << "this function belongs to C" << endl; }
};

int main()
{
	A* pa;
	A a;
	pa = &a;
	pa->func(); // A 타입 포인터가 A 객체를 가리키므로 virtual 상관없이 A의 멤버 호출
	pa->f();
	cout << endl;

	C c;
	pa = &c; // 업캐스팅
	pa->func();
	pa->f();
	pa->A::func();
	pa->A::f(); // 범위지정연산자를 통해 기본클래스 가상함수 호출
	cout << endl;

	C* pc;
	pc = (C*)&a; // 다운캐스팅, 명시적 형변환 필요
	pc->func();
	pc->f(); // 포인터 변수는 자체 값이 정해져있지 않고 부모 객체의 값을 가리키므로 virtual 상관없이 부모 객체 값만 가짐.
	cout << endl;

	B* pb;
	pb = &c; // 업캐스팅
	pb->func();
	cout << endl;

	a = c;
	a.func(); // 포인터가 아닌 경우, 즉 값 치환만 되는 경우 virtual 이 의미 없음.

	// +뽀나스 / 범위지정연산자로 지역 및 전역 변수, 함수 호출하기
	int x = 1;

	cout << x << endl;
	cout << ::x << endl;
	a.run();
}