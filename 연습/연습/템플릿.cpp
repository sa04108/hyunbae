#include <iostream>
using namespace std;

template <class T>
class MyStack {
	int tos;
	T data[100];
public:
	MyStack();
	void push(T element);
	T pop();
};

template <class T>
MyStack<T>::MyStack() {
	tos = -1;
	memset(data, 0, 100);
}

template <class T>
void MyStack<T>::push(T element) {
	if (tos >= 99) {
		cout << "Can't push data on stack.\n";
		return;
	}
	data[++tos] = element;
}

template <class T>
T MyStack<T>::pop() {
	if (tos <= -1) {
		cout << "The stack is empty.";
		return 0;
	}
	return data[tos--];
}

int main() {
	MyStack<int> s;
	s.push(3);
	s.push(5);
	cout << s.pop() << endl << s.pop() << endl;

	return 0;
}