#pragma once
#include <Windows.h>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "ScreenSize.h"

using namespace std;

class Mine : public ScreenSize {
protected:
	int* mine_index;
	int mine_num;
	wchar_t mine;
	
	Mine();
};