/*
* RAII (Resource Acquisition Is Initialization) ����
* C++������ ������ �÷���
* �޸� ���� Ȥ�� �߸��� �޸� ������ ���ϱ� ���� ��ġ�� �ִ´�.
* unique_ptr ��� �ϴ�, ��ü�� ���� ������ �������� ���� �����͸� ���� '�� �� ����', '�ݵ��' �޸𸮸� �����ϵ��� �Ѵ�.
* unique_ptr �� memory ����� std �̸������� �����Ѵ�.
* unique_ptr �� ��������ڰ� ����. ���� �������������� ���� �����͸� �Ѱ��ִ� ��� "������ �Լ��� �����Ϸ��� �մϴ�" ������ ������ �߻��Ѵ�.
* ������ vector ���� ��ü�� �����ؼ� ����ִ� ����� �����̳ʸ� �� �� move() �Լ��� ����Ͽ� '������ ����' ����� �����ϵ��� �Ѵ�.
* vector �����̳ʿ� �ִ� emplace_back() �� move() �� ���������� ��ü�� �Ϻ��� �̵����ѹ����� ������ ��� �� �������. ��ü�� �������� ���� ���ο� �����ϰ� �ȴ�.
* '������ ����'�� ����� ������ �ִ� move() �Լ� �ܿ�, �ӽ÷� �������� ���� ����ϱ� ���ؼ��� unique_ptr.get() �� ����
* unique_ptr �� ����Ű�� ��ü�� �ּҸ� ���� �Ѱ��ָ� �ȴ�.
*/

#include <iostream>
#include <vector>
#include <memory> // unique_ptr �� move(), make_unique() �� ����ϱ� ���� ���

using namespace std;

class A {
	int a;

public:
	A(int num) : a(num) { cout << a << " ����\n"; } // �ʱ�ȭ ����Ʈ ���
	A() : a(0) { cout << a << " ����\n"; } // �ʱ�ȭ ����Ʈ ���
	~A() { cout << a << " �Ҹ�\n"; }

	void print() { cout << a << " ���\n"; }
};

void func(unique_ptr<A>& p)
{
	cout << "<func ����>\n";
	p->print();
	cout << "<--------->\n";
}

void func(A* p)
{
	cout << "<func ����>\n";
	p->print();
	cout << "<--------->\n";
}


int main()
{
	unique_ptr<A> pa(new A(1)); // delete �� �ʿ���� ���α׷� ���� ���� �ڵ����� ��ü�� �Ҵ�� �޸𸮸� �������ش�.
	pa->print();

	vector<unique_ptr<A>> pv;
	// pv.push_back(pa); // ����, unique_ptr ���� ��������ڰ� ������ �� ��ü�� ������ ������ �߸��� ����̹Ƿ� ��Ģ�� ��߳���.
	// pv.push_back(new A(2)); // ����, ����������.

	pv.push_back(move(pa)); // move �Լ��� �̿��� ������ ����
	// pa->print(); // ����, �������� �̹� �����Ǿ����Ƿ� ��ü ���� �Ұ�
	pv.emplace_back(new A(2)); // emplace_back �Լ��� �̿��Ͽ� ������ ��ü �̵��� ���� ������ ����

	unique_ptr<A> ppa(new A(3));
	// func(ppa); // �۵��ϱ�� �ϳ�, �� ��� �Լ� ������ �Ǵٽ� �������� ȹ���ϰ� �ǹǷ� ��Ģ�� ��߳���.
	func(ppa.get()); // ��� get() �Լ��� ���� unique_ptr �� ���� ���� ��ü�� �ּҸ� �Ѱ��ִ� ���� ���ȴ�.

	pv.emplace_back(make_unique<A>(4)); // make_unique() �Լ��� unique_ptr �� ������ �����ϰ� �� �� �ִ�.

	cout << "==Vector ���==\n";
	for (unique_ptr<A>& a : pv)
		a->print();
	cout << "===============\n";

	return 0;
}