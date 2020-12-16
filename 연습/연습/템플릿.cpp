#include <iostream>
#include <vector>
using namespace std;

class Circle {
	int radius;
public:
	Circle(int radius = 1) { this->radius = radius; }
	int getRadius() { return radius; }
};

template <class T>
void myswap(T& a, T& b) {
	T tmp;
	tmp = a;
	a = b;
	b = tmp;
}

template <typename A, typename B>
void myswap(A& a, B& b) {
	A tmp;
	tmp = a;
	a = b;
	b = tmp;
}

class B {
	char ch;
public:
	B(char ch) : ch(ch) {}
	char getChar() { return ch; }
};

class A {
protected:
	int num;
public:
	A(int num = 0) : num(num) {}

	friend class B;
	vector<B*> vec;
	int setNum(int num) { this->num = num; }
	int getNum() { return num; }

	template <typename T>
	void add();

	void print() {
		for (auto b : vec) {
			cout << b->getChar() << endl;
		}
	}
};

template <typename T>
void A::add() {
	auto t = new T(this);
	if (dynamic_cast<B*>(t) == nullptr) {
		delete t;
		return;
	}
	vec.push_back(t);
}

int main() {
	int a = 4, b = 5;
	myswap(a, b);
	cout << "a= " << a << ", b= " << b << endl;

	double c = 0.3, d = 12.5;
	myswap(c, d);
	cout << "c= " << c << ", d= " << d << endl;

	Circle donut(5), pizza(20);
	myswap(donut, pizza);
	cout << "donut 반지름: " << donut.getRadius() << ", ";
	cout << "pizza 반지름: " << pizza.getRadius() << endl;

	myswap<int, double>(a, c);
	cout << a << " " << c;


	A* pa = new A(3);
	B* pb = new B('k');

	pa->add<B>();
	pa->print();
}