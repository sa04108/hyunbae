#pragma once
#include <Windows.h>

class GetPosition {
public:
	static void gotoxy(short x, short y)
	{
		COORD pos = { x, y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	}
};