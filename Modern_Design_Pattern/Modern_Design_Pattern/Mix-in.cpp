/*
* Mix-in ����
* �Ϲ������� �⺻Ŭ������ ����� ���� �Ļ�Ŭ������ �⺻Ŭ������ ��� public, protected ��������� ����Լ��� ��ӹ޴´�.
* �� ��� ���ʿ��� ���� �Ǵ� �Լ����� ��ӹ��� �� �ִµ�
* Mix-in ������ ���� ����ϰ� ���� �޼ҵ�鸸 ��� ����� �� �ֵ��� �� �� ������,
* �̴� ���� ����� ������ �߻���Ű�� �����鼭(���̾Ƹ�� ����)
* ����� ������ ������ �� �ִ� �����̴�.
*/

#include <iostream>
using namespace std;

class Window {
public:
	void Draw() { cout << "Draw" << endl; };
};

template<class Base>
class Animated : public Base
{
public:
	void Play() { cout << "Play" << endl; };
};

template<class Base1>
class Scrollable : public Base1
{
public:
	void ScrollUp() { cout << "Scroll Up" << endl; };
	void ScrollDown() { cout << "Scroll Down" << endl; };
};

template<class Base2>
class Dockable : public Base2
{
public:
	void Dock() { cout << "Dock" << endl; };
	void Undock() { cout << "Undock" << endl; };
};

 //��� C++������ typedef ��� using �� ���ٰ� �Ѵ�.
 //typedef �� ������
 //typedef <����Ÿ�Ը�> <�����ǵ� Ÿ�Ը�>
 //using �� ������
 //using <�����ǵ� Ÿ�Ը�> = <����Ÿ�Ը�>
using AnimatedWindow = Animated<Window>;
using ScrollableWindow = Scrollable<Window>;
using PerfectWindow = Dockable<Scrollable<Animated<Window>>>;

int main()
{
	AnimatedWindow aw;
	aw.Play();
	aw.Draw();
	
	PerfectWindow pw;
	pw.Dock();
	pw.ScrollUp();
	pw.Play();
}