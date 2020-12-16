#pragma once
#include <iostream>
#include "Utils.h"

using namespace std;

class Screen
{
public:
	Screen(int width = 10, int height = 20);
	int getScreenWidth();
	int getScreenHeight();
	int getScreenSize();

protected:
	int width;
	int height;
	Position initial_pos;
	int x;
	int y;
};