/*
* RAII (Resource Acquisition Is Initialization) 패턴
* C++에서의 가비지 컬렉터
* 메모리 누수 혹은 잘못된 메모리 해제를 피하기 위한 장치를 넣는다.
* unique_ptr 라고 하는, 객체에 대한 유일한 소유권을 가진 포인터를 통해 '단 한 번만', '반드시' 메모리를 해제하도록 한다.
* unique_ptr 은 memory 헤더의 std 이름공간에 존재한다.
* unique_ptr 은 복사생성자가 없다. 만약 복사생성방식으로 직접 포인터를 넘겨주는 경우 "삭제된 함수를 참조하려고 합니다" 컴파일 에러가 발생한다.
* 때문에 vector 같은 객체를 복사해서 집어넣는 방식의 컨테이너를 쓸 때 move() 함수를 사용하여 '소유권 이전' 방식을 선택하도록 한다.
* vector 컨테이너에 있는 emplace_back() 은 move() 와 마찬가지로 객체를 완벽히 이동시켜버리기 때문에 사용 시 상관없다. 객체의 소유권은 벡터 내부에 존재하게 된다.
* '소유권 이전'의 기능을 가지고 있는 move() 함수 외에, 임시로 소유권을 같이 사용하기 위해서는 unique_ptr.get() 을 통해
* unique_ptr 이 가리키는 객체의 주소를 직접 넘겨주면 된다.
*/

#include <iostream>
#include <vector>
#include <memory> // unique_ptr 및 move(), make_unique() 를 사용하기 위한 헤더

using namespace std;

class A {
	int a;

public:
	A(int num) : a(num) { cout << a << " 생성\n"; } // 초기화 리스트 사용
	A() : a(0) { cout << a << " 생성\n"; } // 초기화 리스트 사용
	~A() { cout << a << " 소멸\n"; }

	void print() { cout << a << " 출력\n"; }
};

void func(unique_ptr<A>& p)
{
	cout << "<func 내부>\n";
	p->print();
	cout << "<--------->\n";
}

void func(A* p)
{
	cout << "<func 내부>\n";
	p->print();
	cout << "<--------->\n";
}


int main()
{
	unique_ptr<A> pa(new A(1)); // delete 도 필요없이 프로그램 실행 도중 자동으로 객체에 할당된 메모리를 해제해준다.
	pa->print();

	vector<unique_ptr<A>> pv;
	// pv.push_back(pa); // 에러, unique_ptr 에는 복사생성자가 없으며 이 자체도 소유권 이전의 잘못된 방법이므로 원칙에 어긋난다.
	// pv.push_back(new A(2)); // 에러, 마찬가지임.

	pv.push_back(move(pa)); // move 함수를 이용한 소유권 이전
	// pa->print(); // 오류, 소유권이 이미 이전되었으므로 객체 접근 불가
	pv.emplace_back(new A(2)); // emplace_back 함수를 이용하여 완전한 객체 이동을 통한 소유권 이전

	unique_ptr<A> ppa(new A(3));
	// func(ppa); // 작동하기는 하나, 이 경우 함수 내에서 또다시 소유권을 획득하게 되므로 원칙에 어긋난다.
	func(ppa.get()); // 대신 get() 함수를 통해 unique_ptr 가 참조 중인 객체의 주소를 넘겨주는 것은 허용된다.

	pv.emplace_back(make_unique<A>(4)); // make_unique() 함수로 unique_ptr 의 생성을 간편하게 할 수 있다.

	cout << "==Vector 출력==\n";
	for (unique_ptr<A>& a : pv)
		a->print();
	cout << "===============\n";

	return 0;
}