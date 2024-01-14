#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <conio.h>
using namespace std;

// *** �ʵ� ***
// ���� �ż� ���α׷�
// �ҽ� ������ �ִ� ������ �ִ� route.txt ������ �����Ͽ� ��θ� �ٲ�� �մϴ�.
// �⺻ ����) c:\\Users\\User\\Desktop\\data.txt
// �齽����(\)�� �� ���� �Է��Ͻʽÿ�.
void ShowStreamState(ios& stream) {
	cout << "eof()\t" << stream.eof() << endl;
	cout << "fail()\t" << stream.fail() << endl;
	cout << "bad()\t" << stream.bad() << endl;
	cout << "good()\t" << stream.good() << endl;
}

string InsertComma(double num, bool isDollar = false, bool isCurrency = false) {
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

void Print(double low, double high, unsigned int num, double money, bool isDollar = false) {
	double div = (high - low) / ((double)num - 1);
	double div_money = money / (double)num;

	for (unsigned int i = 0; i < num; i++)
	{
		cout << "��" << i + 1 << "�� �ż� ���� >> " << InsertComma(low + i * div, isDollar, true);
		cout << "\t\t�߸ż� �ݾ� >> " << InsertComma(div_money, isDollar, true);
		cout << "\t\t�߸ż� ���� >> " << fixed << setprecision(2) << div_money / (low + i * div) << "��\n";
	}
	cout << "*****************************************************" << endl << endl;
}

void Init(ifstream& fin, string& currency, double& low, double& high, unsigned int& num, double& money) {
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
				if ((c >= 48 && c <= 57) || c >= 97 && c <= 122 || c == '.')
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
			case 4:
				currency = d;
			}
			flag++;

			if (flag > 4) break;
		}
		catch (const char* s) {
			cout << s;
			return;
		}
	}
}

string LoadFileRoute(ifstream& fin) {
	int c, i = 0;
	string route;

	while ((c = fin.get()) != EOF)
	{
		route.append(1, (char)c);
	}
	fin.seekg(0); // ������ fin �� ������ ���� �ʵ��� ���� �����͸� �� ������ ��ġ��Ų��.

	return route;
}

void SetFileRoute(ofstream& fout, string routeFile) {
	string dataFile;

	if (fout)
		fout.close();

	fout.open(routeFile);
	if (!fout)
	{
		cout << " ... ��� ������ �ҷ����� ���߽��ϴ�.\n";
		return;
	}

	cout << "�׵����͸� ������ ������ ��θ� �缳���մϴ�. ��δ� " << routeFile << " �� ����˴ϴ�.\n";
	cout << "\t�ܰ�θ� ������ ���ÿ� ���� ��Ȯ�ϰ� �Է��Ͻʽÿ�. \\�� �� ���� �Է��ؾ� �մϴ�.\n";
	cout << "\tc:\\\\Users\\\\User\\\\Desktop\\\\data.txt\n\n";
	cin >> dataFile;

	fout.seekp(0, ios::beg);
	for (int i = 0; i < dataFile.length(); i++)
	{
		fout.put(dataFile[i]);
	}

	fout.close(); // close �ؾ� ���Ͽ� ���� �ԷµǾ� ����ȴ�.
	fout.open(dataFile, ios::app);
	if (!fout)
		cout << " ... ��ΰ� �߸��ưų�" << dataFile << " �� ��ο� �� ������ ������ ���߰ų� ���� �Է��� �Ұ����� �����Դϴ�.\n\n";
	else
	{
		cout << "��" << dataFile << " �� ��η� �������Ǿ����ϴ�.\n\t���ش� ��ο� �� ������ �ڵ����� �����մϴ�..\n\n";
		cout << "��" << dataFile << " ������ �ҷ��Խ��ϴ�. �����Ͱ� �� ���� ����˴ϴ�.\n\n";
	}
}

int main() {
	string currency;
	double low, high, money;
	unsigned int num;
	bool isDollar = false;

	string routeFile = "route.txt";
	bool isIfileNone = false;
	bool isOfileNone = false;

	ifstream fin(routeFile);
	ofstream fout;

	if (!fin)
	{
		isIfileNone = true;
		fout.open(routeFile); // �� ���� �ڵ� ����
		if (fout)
			fout.close();
		cout << " ... " << routeFile << " ���� �ε� ����. ������ ���� �Ұ�.\n\t�ܻ� ������ �����Ͽ����ϴ�.\n\n";
	}
	else {
		string dataFile = LoadFileRoute(fin);
		cout << "��" << routeFile << " ���Ϸκ��� ������ ������ ��θ� Ž���մϴ�.\n";

		fout.open(dataFile, ios::app); // �� ���� �ڵ� ����
		if (fout)
			fout.close();

		fin.close();
		fin.open(dataFile);

		if (!fin) {
			fin.close();
			fin.open(routeFile);
			if (!fin)
			{
				isIfileNone = true;
				cout << " ... ������ ���� Ž�� ����, " << routeFile << " ���� �ε� ����.\n\n";
			}
			else {
				cout << " ... ������ ���� Ž�� ����, " << routeFile << " ���Ϸκ��� �����͸� �ҷ��ɴϴ�. �ӽ÷� ���⿡ �����͸� �����մϴ�.\n";
				fout.open(routeFile, ios::app);
				if (!fout) {
					isOfileNone = true;
					cout << " ... ������ �Է� �Ұ�\n\n";
				}
				else
					cout << "��" << routeFile << " ���Ͽ� �����͸� �Է��մϴ�.\n\n";
			}
		}
		else
		{
			cout << "�׵����� ���� Ž���� �����Ͽ����ϴ�. " << dataFile << " ���Ϸκ��� �����͸� �ҷ��ɴϴ�.\n";
			fout.open(dataFile, ios::app);
			if (!fout) {
				isOfileNone = true;
				cout << " ... ������ �Է� �Ұ�\n\n";
			}
			else
				cout << "��" << dataFile << " ���Ͽ� �����͸� �Է��մϴ�.\n\n";
		}
	}


	if (!isIfileNone)
	{
		Init(fin, currency, low, high, num, money);
		bool isDollar_ = (currency == "dollar" ? true : false);

		if (!(low < 0 || high < 0 || num < 0 || money < 0)) {
			cout << "### ����� �� ��� ###\n";
			cout << "���� : " << InsertComma(low, isDollar_, true) << "\t�� : " << InsertComma(high, isDollar_, true)
				<< "\t���� �ܰ� �� : " << InsertComma(num) << "\t�� �ż� �ݾ� : " << InsertComma(money, isDollar_, true) << endl;
			Print(low, high, num, money, isDollar_);
		}
	}

	cout << "�׾ƹ� Ű �Է� (cŰ : �޷� ��� / rŰ : ��� �缳�� / escŰ : ������ / ������ : ����)\n";
	cout << "\t�ܹݵ�� ���� �����ؾ� ���Ͽ� �����Ͱ� ����˴ϴ�. �ݱ� ��ư�� ���� �� �����Ͱ� ������� ���� �� �ֽ��ϴ�.\n";

	int ch = _getch();
	if (ch == 'r') {
		SetFileRoute(fout, routeFile);
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

		if (!isOfileNone)
		{
			isDollar ? currency = "dollar" : currency = "won";
			fout << endl << currency << endl << low << endl << high << endl << num << endl << fixed << setprecision(3) << money << endl;
		}
		Print(low, high, num, money, isDollar);

		cout << "�����Ḧ ���Ͻø� esc�� �����ʽÿ�. �޷�/��ȭ��� ��ȯ�� cŰ, ��� �Ϸ��� ������ Ű�� �����ʽÿ�.\n";
		ch = _getch();
		if (ch == 'c') {
			isDollar = !isDollar;
			isDollar ? cout << "�״޷� ��� ������\n\n" : cout << "�׿�ȭ ��� ������\n\n";
		}
	}

	if (!isIfileNone)
		fin.close();
	if (!isOfileNone)
		fout.close();
}