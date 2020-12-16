#include <iostream>
using namespace std;

class Point {
	int x, y;
public:
	Point(int x = 0, int y = 0) : x(x), y(y) { cout << "Point Class 생성\n"; }
	~Point() { cout << "Point Class 소멸\n"; }
	friend istream& operator>>(istream& stream, Point& a);
	friend ostream& operator<<(ostream& stream, const Point& a);
};

istream& operator>>(istream& stream, Point& a) {
	cout << "x좌표: ";
	stream >> a.x;
	cout << "y좌표: ";
	stream >> a.y;
	return stream;
}

ostream& operator<<(ostream& stream, const Point& a) {
	return stream << "(" << a.x << ", " << a.y << ")";
}

int main() {
	Point p(2, 3);
	Point p1;
	Point p2;

	cin >> p1 >> p2; // 값 입력 후 엔터 누르면 엔터 전까지의 값을 p1에 저장하고 cin 리턴되어 cin >> p2 수행.

	cout << p << p1 << p2;
}