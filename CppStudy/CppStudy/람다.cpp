#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template <class T>
void fill(vector<int>& v, T done) {
	int i = 0;
	// done 이 bool 형 함수인 경우 done() 으로 해준다.
	while (!done())
		v.push_back(i++);
}

int main()
{
	int i = 5;

	// Statement 만 지정할 경우
	[]() {cout << "Hello Lambda!\n"; }();

	// Statement와 Parameter 지정, 그리고 임시 객체인 Closure 객체에 i 라는 Argument 를 전달할 때
	[](int& v) {cout << v << " * 5 = " << v * 5 << endl; }(i);
	cout << "i의 값 = " << i << endl;

	int j = 10;
	// Statement, Parameter, 그리고 Introducer 와 Return Type 까지 명시할 경우
	cout << [i](int v) -> int {return v + i; }(j) << endl;

	// Introducer(개시자)는 외부의 변수들이 람다 내부에 접근하도록 하는 역할을 한다. 이를 Capture 라고 한다.
	int total_elements = 1;
	vector<int> cardinal;

	cardinal.push_back(1);
	cardinal.push_back(2);
	cardinal.push_back(4);
	cardinal.push_back(8);

	//for_each 문은 STL 의 algorithm 헤더에 있으며 for_each(a, b, c) 의 파라미터 a는 시작점, b는 종료점, c는 각 지점마다 실행할 함수이다.
	//각 파라미터는 algorithm 에서 템플릿 형태로 되어있다.
	for_each(cardinal.begin(), cardinal.end(), [&](int i) { total_elements *= i; });
	// 개시자 [&]는 외부의 모든 변수를 Call by Reference로 함수 내부에 가져온다는 것을 뜻한다.
	// 위 for_each문의 경우 람다 함수의 Parameter인 i는 cardinal 내부의 값을 가져오는 것을 알 수 있다.
	// 람다 함수내부의 total_elements는 지역변수이지만 참조 형태로 변수를 가져왔기 때문에 외부의 total_elements의 값이 바뀐채 유지된다.
	cout << "total_elements : " << total_elements << endl;


	vector<int> stuff;
	fill(stuff, [&]() -> bool {return stuff.size() >= 8; });
	for_each(stuff.begin(), stuff.end(), [](int i) {cout << i << " "; });
}