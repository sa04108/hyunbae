#include <iostream>
using namespace std;

class Point {
	int x, y;
public:
	Point(int x = 0, int y = 0) : x(x), y(y) { cout << "Point Class ����\n"; }
	~Point() { cout << "Point Class �Ҹ�\n"; }
	friend istream& operator>>(istream& stream, Point& a);
	friend ostream& operator<<(ostream& stream, const Point& a);
};

istream& operator>>(istream& stream, Point& a) {
	cout << "x��ǥ: ";
	stream >> a.x;
	cout << "y��ǥ: ";
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

	cin >> p1 >> p2; // �� �Է� �� ���� ������ ���� �������� ���� p1�� �����ϰ� cin ���ϵǾ� cin >> p2 ����.

	cout << p << p1 << p2;
}