#pragma once
#include <Windows.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <io.h>
#include <fcntl.h>

#include "GetPosition.h"
#include "Mine.h"

using namespace std;

class MineSweeper : public Mine {
	wchar_t* buffer; // char와 다르게 2바이트를 저장할 수 있으며, 유니코드 문자 저장 가능
	wchar_t* hide_buffer;

	int dropby_num;
	int dscvd_num;
	bool isNum;
	int moveTime;
	wchar_t block;

	bool compare(int arr[], int curr);
	bool compare_dby(int* dropby);

	void getEmpty(int index, int* dropby);
	void hitMine();
	void complete();

public:
	bool gameOver;

	MineSweeper();
	~MineSweeper() { delete[] buffer; delete[] hide_buffer; delete[] mine_index; }
	void reset();
	void check();
	void draw();
	void setScreen();

	void clear();
	void boardText();
	void boardRefresh();
};