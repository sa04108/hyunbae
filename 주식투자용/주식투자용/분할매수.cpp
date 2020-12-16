#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <conio.h>
using namespace std;

string insertComma(bool isDollar, double num) {
		string str = to_string(num);
		int i = str.find('.');
		isDollar ? str.erase(i + 3) : str.erase(i);

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

void print(double low, double high, unsigned int num, unsigned int won) {
	double div = (high - low) / ((double)num - 1);
	double div_won = won / (double)num;

	for (unsigned int i = 0; i < num; i++)
	{
		cout << "◆" << i + 1 << "차 매수 지점 >> " << insertComma(false, low + i * div) << "원";
		cout << "\t\t◆매수 금액 >> " << insertComma(false, div_won) << "원";
		cout << "\t\t◆매수 수량 >> " << fixed << setprecision(3) << div_won / (low + i * div) << "개\n";
	}
	cout << "*****************************************************" << endl << endl;
}

void print(double low, double high, unsigned int num, double dollar) {
	double div = (high - low) / ((double)num - 1);
	double div_dollar = dollar / (double)num;

	for (unsigned int i = 0; i < num; i++)
	{
		cout << "◆" << i + 1 << "차 매수 지점 >> " << insertComma(true, low + i * div) << "달러";
		cout << "\t\t◆매수 금액 >> " << insertComma(true, div_dollar) << "달러";
		cout << "\t\t◆매수 수량 >> " << fixed << setprecision(2) << div_dollar / (low + i * div) << "개\n";
	}
	cout << "*****************************************************" << endl << endl;
}

template<typename T>
void init(ifstream& fin, double& low, double& high, unsigned int& num, T& money) {
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
			string typeOfNum = typeid(money).name();
			if (!(typeOfNum == "unsigned int" || typeOfNum == "double"))
				throw "§unsigned int 혹은 double 형의 숫자만 매개변수로 올 수 있습니다.\n";
		}
		catch (const char* s) {
			cout << s;
			return;
		}
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
				throw "§불러온 파일 내부가 정상 상태가 아닙니다. 데이터를 새로 입력합니다.\n\n";
			switch (flag)
			{
			case 0:
				money = typeid(money).name() == "unsigned int" ? stoi(d) : stod(d);
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

void setFileRoute(ofstream& fout, string& file) {
	cout << "§데이터를 저장할 파일의 경로를 재설정합니다.\n";
	cout << "§경로를 다음의 예시와 같이 정확하게 입력하십시오. 백슬래시를 두 번씩 입력해야 합니다.\n";
	cout << "c:\\Users\\User\\Desktop\\data.txt\n\n";
	cin >> file;

	fout.seekp(0, ios::beg);
	fout.write(file.c_str(), file.size());

	cout << "§" << file << " 의 경로로 재지정되었습니다.\n해당 경로에 해당 파일이 있어야 다음 프로그램 실행 시 파일을 불러올 수 있습니다.\n\n";
}

int main() {
	double low, high, dollar;
	unsigned int won, num;
	bool isDollar = false;

	string file = "c:\\buyonscale.txt";
	bool isFileNone = false;
	ifstream fin(file);
	ofstream fout(file, ios::app);

	try {
		if (!fin)
			throw " 파일 불러오기에 실패했습니다.\n\n";
		if (!fout)
			throw " 파일 불러오기에 실패했습니다. 이 프로그램의 데이터는 저장될 수 없습니다.\n\n";
	}
	catch (const char* s) {
		cout << "§" << file << s;
		isFileNone = true;
	}

	if (!isFileNone)
	{
		init(fin, low, high, num, won);

		if (!(low < 0 || high < 0 || num < 0 || won < 0)) {

			cout << "### 저장된 값 목록 ###\n";
			cout << "저가 : " << low << "\t고가 : " << high << "\t분할 단계 수 : " << num << "\t총 매수 금액 : " << fixed << won << endl;
			print(low, high, num, won);
		}
	}

	cout << "§아무 키 입력 (c키 : 달러 모드 / r키 : 경로 재설정 / esc키 : 나가기)\n";

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
			isDollar ? cin >> dollar : cin >> won;
			cout << endl;

			if (low <= 0 || high <= 0 || num <= 0 || won <= 0 || dollar <= 0)
				throw "모든 인자는 0보다 큰 값을 입력해야 합니다.";
			if (high - low <= 0)
				throw "고가와 저가의 입력이 잘못되었습니다.";
			if (num > 100) {
				num = 100;
				cout << "분할 단계 수는 최대 100입니다. 100으로 고정합니다.\n";
			}
		}
		catch (const char* s) {
			cout << s << endl << "-----------------------------------------" << endl;
			continue;
		}

		if (!isFileNone)
			fout << endl << low << endl << high << endl << num << endl << fixed << setprecision(3) << (isDollar ? dollar : won) << endl;
		print(low, high, num, (isDollar ? dollar : won));

		cout << "§종료를 원하시면 esc를 누르십시오. 계속 하려면 나머지 키를 누르십시오.\n";
		ch = _getch();
	}

	fin.close();
	fout.close();
}