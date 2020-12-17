#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <conio.h>
using namespace std;

string insertComma(double num, bool isDollar = false, bool isCurrency = false) {
		string str = to_string(num);
		int i = str.find('.');
		isDollar ? str.erase(i + 3) : str.erase(i); // �Ҽ��� ���� ����

		int third = 0;
		for (int j = i - 1; j > 0; j--)
		{
			third++;
			if (third == 3)
			{
				str.insert(j, 1, ',');
				third = 0;
			}
		}
		if (isCurrency)
			isDollar ? str.append("�޷�") : str.append("��");

		return str;
}

void print(double low, double high, unsigned int num, double money, bool isDollar = false) {
	double div = (high - low) / ((double)num - 1);
	double div_money = money / (double)num;

	for (unsigned int i = 0; i < num; i++)
	{
		cout << "��" << i + 1 << "�� �ż� ���� >> " << insertComma(low + i * div, isDollar, true);
		cout << "\t\t�߸ż� �ݾ� >> " << insertComma(div_money, isDollar, true);
		cout << "\t\t�߸ż� ���� >> " << fixed << setprecision(2) << div_money / (low + i * div) << "��\n";
	}
	cout << "*****************************************************" << endl << endl;
}

void init(ifstream& fin, double& low, double& high, unsigned int& num, double& money) {
	fin.seekg(0, ios::end);
	int filesize = fin.tellg();
	int size = 0;
	int c = 0;
	int flag = 0;
	int offset = 0;
	string d;

	while (true)
	{
		try {
		if (filesize - offset <= 0) {
			throw "�׺ҷ��� ������ �� �����̹Ƿ� ���� �Է��մϴ�.\n\n";
		};
		d.clear();
		for (int i = offset; i < filesize; i++)
		{
			fin.seekg(filesize - 1 - i, ios::beg);
			c = fin.get();
			if (size > 0 && c == (int)'\n') break;
			if (c >= 48 && c <= 57)
				size++;
			else
				offset++;
		}
		for (int i = 0; i < size; i++)
		{
			c = fin.get();
			d.append(1, (char)c);
		}

		offset += size + 2;
		size = 0;

		if (d.empty())
			throw " ... �ҷ��� ���� ���ΰ� ���� ���°� �ƴմϴ�. �����͸� ���� �Է��մϴ�.\n\n";
		switch (flag)
		{
		case 0:
			money = stod(d);
			break;
		case 1:
			num = stoi(d);
			break;
		case 2:
			high = stod(d);
			break;
		case 3:
			low = stod(d);
			break;
		}
		flag++;

		if (flag > 3) break;
		}
		catch (const char* s) {
			cout << s;
			return;
		}
	}
}

string loadFileRoute(ifstream& fin) {
	int c, i = 0;
	string route;

	while ((c = fin.get()) != EOF)
	{
		route.append(1, (char)c);
	}

	return route;
}

void setFileRoute(ofstream& fout, string file) {
	string route;

	fout.close();
	fout.open(file);

	cout << "�׵����͸� ������ ������ ��θ� �缳���մϴ�.\n";
	cout << "\t�ܰ�θ� ������ ���ÿ� ���� ��Ȯ�ϰ� �Է��Ͻʽÿ�. \\�� �� ���� �Է��ؾ� �մϴ�.\n";
	cout << "\tc:\\\\Users\\\\User\\\\Desktop\\\\data.txt\n\n";
	cin >> route;

	fout.seekp(0, ios::beg);
	for (int i = 0; i < route.length(); i++)
	{
		fout.put(route[i]);
	}

	fout.close(); // close �ؾ� ���Ͽ� ���� �ԷµǾ� ����ȴ�.
	fout.open(route, ios::app);
	if (!fout)
		cout << " ... ��ΰ� �߸��ưų�" << route << " �� ��ο� �� ������ ������ ���߰ų� ���� �Է��� �Ұ����� �����Դϴ�.\n\n";
	else
	{
		cout << "��" << route << " �� ��η� �������Ǿ����ϴ�.\n\t���ش� ��ο� �� ������ �ڵ����� �����մϴ�..\n\n";
		cout << "��" << route << " �� ��ο��� ������ �ҷ��Խ��ϴ�. �����Ͱ� �� ���� ����˴ϴ�.\n\n";
	}
}

int main() {
	double low, high, money;
	unsigned int num;
	bool isDollar = false;

	string file = "c:\\Users\\User\\Desktop\\data.txt";
	bool isFileNone = false;
	ifstream fin(file);
	string route;

	if (!fin)
		cout << " ... " << file << " ���� �ε� ����.\n\n";
	else {
		cout << "��" << file << " ���Ϸκ��� ������ ������ ��θ� Ž���մϴ�.\n";
		route = loadFileRoute(fin);
		fin.close();
		fin.open(route);

		if (!fin) {
			fin.close();
			fin.open(file);
			if (!fin)
				cout << " ... ��� Ž�� ����, " << file << " ���� �ε� ����.\n\n";
			else
				cout << " ... ��� Ž�� ����, " << file << " ���Ϸκ��� �����͸� �ҷ��ɴϴ�.\n\n";
		}
		else
			cout << "�װ�� Ž���� �����Ͽ����ϴ�. " << route << " ���Ϸκ��� �����͸� �ҷ��ɴϴ�.\n\n";
	}

	ofstream fout(route, ios::app);
	route = loadFileRoute(fin);
	if (!fout)
		cout << " ... " << route << "��ΰ� �߸��ưų� ������ �����ϴ�. ��ΰ� �´� ��� ���� ������ �����Ͽ� �����͸� �Է��մϴ�.\n\n";
	else
		cout << "��" << route << "���Ͽ� �����͸� �Է��մϴ�.\n\n";

	if (!isFileNone)
	{
		init(fin, low, high, num, money);

		if (!(low < 0 || high < 0 || num < 0 || money < 0)) {

			cout << "### ����� �� ��� ###\n";
			cout << "���� : " << insertComma(low) << "\t�� : " << insertComma(high)
				<< "\t���� �ܰ� �� : " << insertComma(num) << "\t�� �ż� �ݾ� : " << insertComma(money) << endl;
			print(low, high, num, money);
		}
	}

	cout << "�׾ƹ� Ű �Է� (cŰ : �޷� ��� / rŰ : ��� �缳�� / escŰ : ������ / ������ : ����)\n";
	cout << "\t�ܹݵ�� ���� �����ؾ� ���Ͽ� �����Ͱ� ����˴ϴ�. �ݱ� ��ư�� ���� �� �����Ͱ� ������� ���� �� �ֽ��ϴ�.\n";

	int ch = _getch();
	if (ch == 'r') {
		setFileRoute(fout, file);
	}
	else if (ch == 'c') {
		isDollar = true;
		cout << "�״޷� ��� ������\n\n";
	}
	
	while (ch != 27)
	{
		try {
			cout << "1. ���� ���� : ";
			cin >> low;
			cout << "2. �� ���� : ";
			cin >> high;
			cout << "3. �� ���� �ܰ� �� : ";
			cin >> num;
			cout << "4. �� �ż� �ݾ� : ";
			cin >> money;
			cout << endl;

			if (low <= 0 || high <= 0 || num <= 0 || money <= 0)
				throw " ... ��� ���ڴ� 0���� ū ���� �Է��ؾ� �մϴ�.";
			if (high - low <= 0)
				throw " ... ���� ������ �Է��� �߸��Ǿ����ϴ�.";
			if (num > 100) {
				num = 100;
				cout << " ... ���� �ܰ� ���� �ִ� 100�Դϴ�. 100���� �����մϴ�.\n";
			}
		}
		catch (const char* s) {
			cout << s << endl << "-----------------------------------------" << endl;
			continue;
		}

		if (!isFileNone)
			fout << endl << low << endl << high << endl << num << endl << fixed << setprecision(3) << money << endl;
		print(low, high, num, money, isDollar);

		cout << "�����Ḧ ���Ͻø� esc�� �����ʽÿ�. �޷�/��ȭ��� ��ȯ�� cŰ, ��� �Ϸ��� ������ Ű�� �����ʽÿ�.\n";
		ch = _getch();
		if (ch == 'c') {
			isDollar = !isDollar;
			isDollar ? cout << "�״޷� ��� ������\n\n" : cout << "�׿�ȭ ��� ������\n\n";
		}
	}

	fin.close();
	fout.close();
}