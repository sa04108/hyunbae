/*
* Mix-in 패턴
* 일반적으로 기본클래스의 상속을 받은 파생클래스는 기본클래스의 모든 public, protected 멤버변수와 멤버함수를 상속받는다.
* 이 경우 불필요한 변수 또는 함수들을 상속받을 수 있는데
* Mix-in 패턴을 쓰면 사용하고 싶은 메소드들만 골라서 사용할 수 있도록 할 수 있으며,
* 이는 다중 상속의 문제를 발생시키지 않으면서(다이아몬드 문제)
* 상속의 장점을 가져갈 수 있는 패턴이다.
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

 //모던 C++에서는 typedef 대신 using 을 쓴다고 한다.
 //typedef 의 선언은
 //typedef <기존타입명> <재정의된 타입명>
 //using 의 선언은
 //using <재정의된 타입명> = <기존타입명>
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