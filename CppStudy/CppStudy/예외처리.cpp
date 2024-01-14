#include <iostream>
using namespace std;

class MyException {
	int lineNo;
	string func, msg;
public:
	MyException(int n, string f, string m) {
		lineNo = n; func = f; msg = m;
	}
	void print() { cout << func << ":" << lineNo << ", " << msg << endl; }
};

class DivideByZeroExcption : public MyException {
public:
		DivideByZeroExcption(int lineNo, string func, string msg) :
		MyException(lineNo, func, msg) {}
};

class InvalidInputException : public MyException {
public:
	InvalidInputException(int lineNo, string func, string msg) :
		MyException(lineNo, func, msg) {}
};

int main() {
	/*
	int n, sum, average;

	while (true)
	{
		cout << "�� �Է�: ";
		cin >> sum;

		cout << "�ο� �� �Է�: ";
		cin >> n;

		try { // ���� �߻� ���ɼ� �ִ� ����
			if (n <= 0)
				throw n; // ���� ó���� ���� ���� ������
			else
				average = sum / n;
		}
		catch (int x) { // throw �� ���� ���޹��� ���� ������ �Ű����� ������ ��ġ�� ��� ����
			cout << "���� �߻�) " << x << "���� ���� �� ����\n";
			average = 0;
			continue;
		}
		cout << "\n��� = " << average << "\n\n";
	}
	*/

	int x, y;
	try {
		cout << "�������� �մϴ�. �� ���� ���� ������ �Է��Ͻÿ�.\n";
		cin >> x >> y;
		if (x < 0 || y < 0)
			throw InvalidInputException(33, "main()", "���� �Է� ���� �߻�");
		if (y == 0)
			throw DivideByZeroExcption(35, "main()", "0���� ������ ���� �߻�");
		cout << (double)x / (double)y;
	}
	catch (DivideByZeroExcption& e) { // &�� �߰��Ͽ� ��ü�� ���� ��� ��ü�� ���� �������� ����� �ٲپ� ����ӵ� ����
		e.print();
	}
	catch (InvalidInputException& e) {
		e.print();
	}
}