#include <iostream>
using namespace std;

/*
* CRTP: Curiously Recurring Template Pattern
* �̻��� ��� ���ø� ����
* - �ڱ� �ڽ��� �θ�Ŭ������ ���ø����� ��� �޴´�.
*/

template <typename TYPE>
class Window {
public:
	void MsgLoop() {
		(static_cast<TYPE*>(this))->OnClick();
	}

	void OnClick() { cout << "Window OnClick" << endl; }
};

class MyWindow : public Window<MyWindow> {

public:
	void OnClick() { cout << "MyWindow OnClick" << endl; }

};

int main() {
	MyWindow w;
	w.MsgLoop();

	return 0;
}