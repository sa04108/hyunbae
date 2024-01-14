#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void showStreamState(ios& stream) {
	cout << "eof()\t" << stream.eof() << endl;
	cout << "fail()\t" << stream.fail() << endl;
	cout << "bad()\t" << stream.bad() << endl;
	cout << "good()\t" << stream.good() << endl;
}

int main() {
	/*
	ofstream fout("c:\\text.txt");

	if (!fout) {
		cout << "file output stream error: Failed To Open Text File\n";
	}


	char name[] = "Kriss", dept[] = "Physics";
	int sid = 536718;

	fout << name << '\n';
	fout << sid << endl;
	fout << dept << endl;

	fout.close();

	ifstream fin;

	fin.open("c:\\text.txt");
	if (!fin) {
		cout << "file input stream error: Failed To Open Text File\n";
		return 0;
	}

	char* name_ = new char[strlen(name + 1)];
	char* dept_ = new char[strlen(dept + 1)];
	int sid_;

	fin >> name_;
	fin >> sid_;
	fin >> dept_;

	cout << name_ << '\n' << dept_ << '\n' << sid_ << '\n';
	fin.close();


	char* file = "c:\\windows\\system.ini";

	fin.open(file);
	if (!fin) {
		cout << "file input stream error: Failed To Open Text File\n";
		return 0;
	}

	int count = 0;
	int c;
	while ((c = fin.get()) != EOF)
	{
		cout << (char)c;
		count++;
	}
	cout << "읽은 바이트 수: " << count;
	fin.close();
	*/

	/*
	char* firstFile = "c:\\text.txt";
	char* secondFile = "c:\\windows\\system.ini";

	fstream fout(firstFile, ios::out | ios::app); // ios::out 을 디폴트로 할려면 ifstream 형으로 선언
	if (!fout) {
		cout << firstFile << " 열기 오류";
		return 0;
	}

	fstream fin(secondFile, ios::in); // ios::in 을 디폴트로 할려면 ofstream 형으로 선언
	if (!fin) {
		cout << secondFile << " 열기 오류";
		return 0;
	}

	int c;
	while ((c = fin.get()) != EOF)
	{
		fout.put(c);
	}

	fin.close();
	fin.open(secondFile, ios::in);

	string line;
	while (true)
	{
		getline(fin, line);
		if (fin.eof()) break;
		cout << line << endl;
	}

	fin.close();
	fout.close();
	*/

	/*
	ifstream fin;
	fin.open("c:\\nike.jpg", ios::binary);
	if (!fin) {
		cout << "fin 이미지 열기 오류";
		return 0;
	}

	ofstream fout;
	fout.open("c:\\object.jpg", ios::binary);
	if (!fout) {
		cout << "fout 이미지 열기 오류";
		return 0;
	}

	int c;
	while ((c = fin.get()) != EOF)
	{
		fout.put(c);
	}

	fin.close();
	fout.close();
	*/

	/*
	ifstream fin;
	fin.open("c:\\windows\\system.ini", ios::binary);
	if (!fin) {
		cout << "파일 불러오기 실패";
		return 0;
	}

	char s[32];
	int count = 0;

	while (!fin.eof())
	{
		fin.read(s, 32); // fin(읽기 지정된 파일)으로부터 처음 32바이트를 s에 저장
		int n = fin.gcount(); // 만약 불러온 파일이 32바이트보다 작은 경우 read()는 바로 리턴되어 정확히 몇 바이트를 가져왔는지 알 수 없다. 때문에 gcount로 실제 몇 바이트를 가져왔는지 볼 수 있다.
		cout.write(s, n);
		count += n;
	}
	
	cout << count << endl;
	fin.close();
	*/

	/*
	char* srcFile = "c:\\nike.jpg";
	char* destFile = "c:\\object.jpg";

	ifstream fsrc(srcFile, ios::binary);
	if (!fsrc) {
		cout << srcFile << " 열기 오류" << endl;
		return 0;
	}

	ofstream fdest(destFile, ios::binary);
	if (!fdest) {
		cout << destFile << " 열기 오류" << endl;
		return 0;
	}

	char buf[1024];
	while (!fsrc.eof()) {
		fsrc.read(buf, 1024);
		int n = fsrc.gcount();
		fdest.write(buf, n);
	}

	cout << fsrc.gcount();

	fsrc.close();
	fdest.close();
	*/

	char* noExistFile = "c:\\noexist.txt";
	char* existFile = "c:\\text.txt";

	ifstream fin(noExistFile);
	if (!fin) {
		cout << noExistFile << " 열기 오류" << endl;
		showStreamState(fin);

		cout << existFile << " 파일 열기" << endl;
		fin.open(existFile);
		showStreamState(fin);
	}

	int c;
	while ((c = fin.get()) != EOF)
		cout.put((char)c);

	cout << endl;
	showStreamState(fin);
	fin.close();
}