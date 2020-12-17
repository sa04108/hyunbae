#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <conio.h>
using namespace std;

string insertComma(double num, bool isDollar = false, bool isCurrency = false) {
		string str = to_string(num);
		int i = str.find('.');
		isDollar ? str.erase(i + 3) : str.erase(i); // 소수점 이후 정리

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
			isDollar ? str.append("달러") : str.append("원");

		return str;
}

void print(double low, double high, unsigned int num, double money, bool isDollar = false) {
	double div = (high - low) / ((double)num - 1);
	double div_money = money / (double)num;

	for (unsigned int i = 0; i < num; i++)
	{
		cout << "◆" << i + 1 << "차 매수 지점 >> " << insertComma(low + i * div, isDollar, true);
		cout << "\t\t◆매수 금액 >> " << insertComma(div_money, isDollar, true);
		cout << "\t\t◆매수 수량 >> " << fixed << setprecision(2) << div_money / (low + i * div) << "개\n";
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
			throw "§불러온 파일이 빈 파일이므로 새로 입력합니다.\n\n";
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
			throw " ... 불러온 파일 내부가 정상 상태가 아닙니다. 데이터를 새로 입력합니다.\n\n";
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

	cout << "§데이터를 저장할 파일의 경로를 재설정합니다.\n";
	cout << "\t●경로를 다음의 예시와 같이 정확하게 입력하십시오. \\를 두 번씩 입력해야 합니다.\n";
	cout << "\tc:\\\\Users\\\\User\\\\Desktop\\\\data.txt\n\n";
	cin >> route;

	fout.seekp(0, ios::beg);
	for (int i = 0; i < route.length(); i++)
	{
		fout.put(route[i]);
	}

	fout.close(); // close 해야 파일에 값이 입력되어 저장된다.
	fout.open(route, ios::app);
	if (!fout)
		cout << " ... 경로가 잘못됐거나" << route << " 의 경로에 새 파일을 만들지 못했거나 파일 입력이 불가능한 상태입니다.\n\n";
	else
	{
		cout << "§" << route << " 의 경로로 재지정되었습니다.\n\t●해당 경로에 새 파일을 자동으로 생성합니다..\n\n";
		cout << "§" << route << " 의 경로에서 파일을 불러왔습니다. 데이터가 이 곳에 저장됩니다.\n\n";
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
		cout << " ... " << file << " 파일 로드 실패.\n\n";
	else {
		cout << "§" << file << " 파일로부터 데이터 파일의 경로를 탐색합니다.\n";
		route = loadFileRoute(fin);
		fin.close();
		fin.open(route);

		if (!fin) {
			fin.close();
			fin.open(file);
			if (!fin)
				cout << " ... 경로 탐색 실패, " << file << " 파일 로드 실패.\n\n";
			else
				cout << " ... 경로 탐색 실패, " << file << " 파일로부터 데이터를 불러옵니다.\n\n";
		}
		else
			cout << "§경로 탐색에 성공하였습니다. " << route << " 파일로부터 데이터를 불러옵니다.\n\n";
	}

	ofstream fout(route, ios::app);
	route = loadFileRoute(fin);
	if (!fout)
		cout << " ... " << route << "경로가 잘못됐거나 파일이 없습니다. 경로가 맞는 경우 새로 파일을 생성하여 데이터를 입력합니다.\n\n";
	else
		cout << "§" << route << "파일에 데이터를 입력합니다.\n\n";

	if (!isFileNone)
	{
		init(fin, low, high, num, money);

		if (!(low < 0 || high < 0 || num < 0 || money < 0)) {

			cout << "### 저장된 값 목록 ###\n";
			cout << "저가 : " << insertComma(low) << "\t고가 : " << insertComma(high)
				<< "\t분할 단계 수 : " << insertComma(num) << "\t총 매수 금액 : " << insertComma(money) << endl;
			print(low, high, num, money);
		}
	}

	cout << "§아무 키 입력 (c키 : 달러 모드 / r키 : 경로 재설정 / esc키 : 나가기 / 나머지 : 진행)\n";
	cout << "\t●반드시 정상 종료해야 파일에 데이터가 저장됩니다. 닫기 버튼을 누를 시 데이터가 저장되지 않을 수 있습니다.\n";

	int ch = _getch();
	if (ch == 'r') {
		setFileRoute(fout, file);
	}
	else if (ch == 'c') {
		isDollar = true;
		cout << "§달러 모드 설정됨\n\n";
	}
	
	while (ch != 27)
	{
		try {
			cout << "1. 저가 설정 : ";
			cin >> low;
			cout << "2. 고가 설정 : ";
			cin >> high;
			cout << "3. 총 분할 단계 수 : ";
			cin >> num;
			cout << "4. 총 매수 금액 : ";
			cin >> money;
			cout << endl;

			if (low <= 0 || high <= 0 || num <= 0 || money <= 0)
				throw " ... 모든 인자는 0보다 큰 값을 입력해야 합니다.";
			if (high - low <= 0)
				throw " ... 고가와 저가의 입력이 잘못되었습니다.";
			if (num > 100) {
				num = 100;
				cout << " ... 분할 단계 수는 최대 100입니다. 100으로 고정합니다.\n";
			}
		}
		catch (const char* s) {
			cout << s << endl << "-----------------------------------------" << endl;
			continue;
		}

		if (!isFileNone)
			fout << endl << low << endl << high << endl << num << endl << fixed << setprecision(3) << money << endl;
		print(low, high, num, money, isDollar);

		cout << "§종료를 원하시면 esc를 누르십시오. 달러/원화모드 전환은 c키, 계속 하려면 나머지 키를 누르십시오.\n";
		ch = _getch();
		if (ch == 'c') {
			isDollar = !isDollar;
			isDollar ? cout << "§달러 모드 설정됨\n\n" : cout << "§원화 모드 설정됨\n\n";
		}
	}

	fin.close();
	fout.close();
}