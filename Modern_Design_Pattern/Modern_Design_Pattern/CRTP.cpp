#include <iostream>
using namespace std;

/*
* CRTP: Curiously Recurring Template Pattern
* 이상한 재귀 템플릿 패턴
* - 자기 자신을 부모클래스의 템플릿으로 상속 받는다.
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