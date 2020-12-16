#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <conio.h>
using namespace std;

template<typename T>
string insertComma(T num) {
	try {
		string typeOfNum = typeid(num).name();
		if (!(typeOfNum == "int" || typeOfNum == "double"))
			throw "��int Ȥ�� double ���� ���ڸ� ','�� ������ �� �ֽ��ϴ�.";

		string str = to_string(num);
		int i = str.find('.');
		str.erase(i);

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

		return str;
	}
	catch (const char* s) {
		cout << s;
		return "";
	}
}

void print(double low, double high, unsigned int num, unsigned int money) {
	double div = (high - low) / ((double)num - 1);
	double div_money = money / (double)num;

	for (unsigned int i = 0; i < num; i++)
	{
		cout << "��" << i + 1 << "�� �ż� ���� >> " << insertComma(low + i * div) << "��";
		cout << "\t\t�߸ż� �ݾ� >> " << insertComma(div_money) << "��";
		cout << "\t\t�߸ż� ���� >> " << fixed << setprecision(3) << div_money / (low + i * div) << "��\n";
	}
	cout << "*****************************************************" << endl << endl;
}

void init(ifstream& fin, double& low, double& high, unsigned int& num, unsigned int& money) {
	fin.seekg(0, ios::end);
	int filesize = fin.tellg();
	int size = 0;
	int c = 0;
	int flag = 0;
	int offset = 0;
	string d;

	while (true)
	{
		if (filesize - offset <= 0) break;
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
		try {
			if (d.empty())
				throw "�׺ҷ��� ���� ���ΰ� ���� ���°� �ƴմϴ�. �����͸� ���� �Է��մϴ�.\n\n";
			switch (flag)
			{
			case 0:
				money = stoi(d);
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

int main() {
	double low, high;
	unsigned int money, num;

	string file = "c:\\buyonscale.txt";
	bool isFileNone = false;
	ifstream fin(file);
	ofstream fout(file, ios::app);

	try {
		if (!fin)
			throw " ���� �ҷ����⿡ �����߽��ϴ�.\n\n";
		if (!fout)
			throw " ���� �ҷ����⿡ �����߽��ϴ�. �� ���α׷��� �����ʹ� ����� �� �����ϴ�.\n\n";
	}
	catch (const char* s) {
		cout << "��" << file << s;
		isFileNone = true;
	}

	if (!isFileNone)
	{
		init(fin, low, high, num, money);

		if (!(low < 0 || high < 0 || num < 0 || money < 0)) {

			cout << "### ����� �� ��� ###\n";
			cout << "���� : " << low << "\t�� : " << high << "\t���� �ܰ� �� : " << num << "\t�� �ż� �ݾ� : " << fixed << money << endl;
			print(low, high, num, money);
		}
	}

	cout << "�׾ƹ� Ű �Է� (rŰ : ��� �缳�� / escŰ : ������)\n\n";

	int ch = _getch();
	if (ch == 'r') {
		cout << "�׵����͸� ������ ������ ��θ� �缳���մϴ�.\n";
		cout << "�װ�θ� ������ ���ÿ� ���� ��Ȯ�ϰ� �Է��Ͻʽÿ�. �齽���ø� �� ���� �Է��ؾ� �մϴ�.\n";
		cout << "c:\\Users\\User\\Desktop\\data.txt\n\n";
		cin >> file;

		fout.seekp(0, ios::beg);
		fout.write(file.c_str(), file.size());

		cout << "��" << file << " �� ��η� �������Ǿ����ϴ�.\n�ش� ��ο� �ش� ������ �־�� ���� ���α׷� ���� �� ������ �ҷ��� �� �ֽ��ϴ�.\n\n";
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
				throw "��� ���ڴ� 0���� ū ���� �Է��ؾ� �մϴ�.";
			if (high - low <= 0)
				throw "���� ������ �Է��� �߸��Ǿ����ϴ�.";
			if (num > 100) {
				num = 100;
				cout << "���� �ܰ� ���� �ִ� 100�Դϴ�. 100���� �����մϴ�.\n";
			}
		}
		catch (const char* s) {
			cout << s << endl << "-----------------------------------------" << endl;
			continue;
		}

		if (!isFileNone)
			fout << endl << low << endl << high << endl << num << endl << fixed << money << endl;
		print(low, high, num, money);

		cout << "�����Ḧ ���Ͻø� esc�� �����ʽÿ�. ��� �Ϸ��� ������ Ű�� �����ʽÿ�.\n";
		ch = _getch();
	}

	fin.close();
	fout.close();
}