#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template <class T>
void fill(vector<int>& v, T done) {
	int i = 0;
	// done �� bool �� �Լ��� ��� done() ���� ���ش�.
	while (!done())
		v.push_back(i++);
}

int main()
{
	int i = 5;

	// Statement �� ������ ���
	[]() {cout << "Hello Lambda!\n"; }();

	// Statement�� Parameter ����, �׸��� �ӽ� ��ü�� Closure ��ü�� i ��� Argument �� ������ ��
	[](int& v) {cout << v << " * 5 = " << v * 5 << endl; }(i);
	cout << "i�� �� = " << i << endl;

	int j = 10;
	// Statement, Parameter, �׸��� Introducer �� Return Type ���� ����� ���
	cout << [i](int v) -> int {return v + i; }(j) << endl;

	// Introducer(������)�� �ܺ��� �������� ���� ���ο� �����ϵ��� �ϴ� ������ �Ѵ�. �̸� Capture ��� �Ѵ�.
	int total_elements = 1;
	vector<int> cardinal;

	cardinal.push_back(1);
	cardinal.push_back(2);
	cardinal.push_back(4);
	cardinal.push_back(8);

	//for_each ���� STL �� algorithm ����� ������ for_each(a, b, c) �� �Ķ���� a�� ������, b�� ������, c�� �� �������� ������ �Լ��̴�.
	//�� �Ķ���ʹ� algorithm ���� ���ø� ���·� �Ǿ��ִ�.
	for_each(cardinal.begin(), cardinal.end(), [&](int i) { total_elements *= i; });
	// ������ [&]�� �ܺ��� ��� ������ Call by Reference�� �Լ� ���ο� �����´ٴ� ���� ���Ѵ�.
	// �� for_each���� ��� ���� �Լ��� Parameter�� i�� cardinal ������ ���� �������� ���� �� �� �ִ�.
	// ���� �Լ������� total_elements�� �������������� ���� ���·� ������ �����Ա� ������ �ܺ��� total_elements�� ���� �ٲ�ä �����ȴ�.
	cout << "total_elements : " << total_elements << endl;


	vector<int> stuff;
	fill(stuff, [&]() -> bool {return stuff.size() >= 8; });
	for_each(stuff.begin(), stuff.end(), [](int i) {cout << i << " "; });
}