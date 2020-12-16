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
	B b(20); // b 객체가 만들어질 때 A 클래스 생성자 선언 후 B 클래스 생성자 선언
	B* pb;

	pa->update();
	delete pa;

	pa = &b; // 업캐스팅
	pa->update(); // b 객체에는 A 클래스 정보가 포함되어있다. A 클래스의 update 함수가 virtual 이 아니므로
	// A 클래스의 num 정보와 update 함수에만 접근할 수 있다.
	
	pb = (B*)pa; // 다운캐스팅
	pb->update(); // pb 는 B 클래스형이므로 B 클래스의 메소드에 접근할 수 있다.
	pb->child();

	// dynamic_cast는 컴파일이 아닌 프로그램 실행 도중 캐스팅하는 것을 말한다. 이름 그대로 동적캐스팅
	C* pc = dynamic_cast<C*>(new D(40));
	pc->update();
	pb = dynamic_cast<B*>(pc);
	// C 클래스는 B 클래스의 자식이 아니지만 pc 가 가리키고 있는 객체는 B 의 상속을 받는 D 이므로 정상적으로 업캐스팅 된다.
	pb->update();

	delete pb;

	// 어떤 포인터든 강제로 형변환 시켜버리는 reinterpret_cast는 강제성을 가진 만큼 위험성을 내포하고 있다.
	pb = reinterpret_cast<B*>(new C(30));
	// B와 C는 서로 상속관계도 아닌 배다른 관계지만 강제 형변환을 통해 B가 C정보에 접근할 수 있도록 하였다.
	pb->update();

	return 0;
}