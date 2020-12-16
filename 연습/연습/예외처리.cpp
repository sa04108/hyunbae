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
		cout << "합 입력: ";
		cin >> sum;

		cout << "인원 수 입력: ";
		cin >> n;

		try { // 예외 발생 가능성 있는 구간
			if (n <= 0)
				throw n; // 예외 처리를 위해 값을 전달함
			else
				average = sum / n;
		}
		catch (int x) { // throw 로 부터 전달받은 값의 유형과 매개변수 유형이 일치할 경우 실행
			cout << "예외 발생) " << x << "으로 나눌 수 없음\n";
			average = 0;
			continue;
		}
		cout << "\n평균 = " << average << "\n\n";
	}
	*/

	int x, y;
	try {
		cout << "나눗셈을 합니다. 두 개의 양의 정수를 입력하시오.\n";
		cin >> x >> y;
		if (x < 0 || y < 0)
			throw InvalidInputException(33, "main()", "음수 입력 예외 발생");
		if (y == 0)
			throw DivideByZeroExcption(35, "main()", "0으로 나누는 예외 발생");
		cout << (double)x / (double)y;
	}
	catch (DivideByZeroExcption& e) { // &를 추가하여 객체의 복사 대신 객체에 대한 접근으로 방식을 바꾸어 연산속도 증가
		e.print();
	}
	catch (InvalidInputException& e) {
		e.print();
	}
}