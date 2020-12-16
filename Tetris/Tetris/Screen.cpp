#include "Screen.h"

Screen::Screen(int width, int height) : width(width), height(height)
{
	initial_pos.x = width / 2;
	initial_pos.y = 1;
	x = initial_pos.x;
	y = initial_pos.y;
}

int Screen::getScreenWidth()
{
	return width + 1;
}

int Screen::getScreenHeight()
{
	return height;
}

int Screen::getScreenSize()
{
	return getScreenWidth() * getScreenHeight();
}