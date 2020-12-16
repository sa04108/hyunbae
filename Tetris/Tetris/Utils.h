#ifndef UTILS_H_
#define UTILS_H_

#include <Windows.h>

class Position {
public:
	int x;
	int y;
	Position(int x = 0, int y = 0) : x(x), y(y) {}
	void setPos(int x, int y) {
		this->x = x;
		this->y = y;
	}
	Position operator+(Position pos2)
	{
		Position temp;
		temp.x = x + pos2.x;
		temp.y = y + pos2.y;
		return temp;
	}
	Position operator-(Position pos2)
	{
		Position temp;
		temp.x = x - pos2.x;
		temp.y = y - pos2.y;
		return temp;
	}
};

class Borland {

public:
	static void initialize()
	{
		CONSOLE_CURSOR_INFO cci;
		cci.dwSize = 25;
		cci.bVisible = FALSE;
		SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
		SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT);
	}

	static int wherex()
	{
		CONSOLE_SCREEN_BUFFER_INFO  csbiInfo;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiInfo);
		return csbiInfo.dwCursorPosition.X;
	}
	static int wherey()
	{
		CONSOLE_SCREEN_BUFFER_INFO  csbiInfo;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiInfo);
		return csbiInfo.dwCursorPosition.Y;
	}
	static void gotoxy(int x, int y)
	{
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), _COORD{ (SHORT)x, (SHORT)y });
	}
	static void gotoxyX2(int x, int y)
	{
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), _COORD{ (SHORT)x * 2, (SHORT)y });
	}
	static void gotoxy(const Position* pos)
	{
		if (!pos) return;
		gotoxy( (*pos).x, (*pos).y);
	}
	static void gotoxy(const Position& pos)
	{
		gotoxy( pos.x, pos.y);
	}
	static void gotoxyX2(Position pos)
	{
		gotoxyX2(pos.x, pos.y);
	}
};

#endif 
