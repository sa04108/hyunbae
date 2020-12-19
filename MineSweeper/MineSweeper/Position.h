#pragma once
#include <Windows.h>

class Position {
	int x, y;
public:
	Position(int x = 0, int y = 0) : x(x), y(y) {}
	static void gotoxy(short x, short y)
	{
		COORD pos = { x, y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	}
	static void gotoxy(Position pos)
	{
		gotoxy(pos.x, pos.y);
	}

	void setPos(int x, int y) {
		this->x = x;
		this->y = y;
	}

	void setPos(Position pos) {
		*this = pos;
	}

	Position getPos() {
		return *this;
	}

	int getPosX() { return x; }
	int getPosY() { return y; }
};