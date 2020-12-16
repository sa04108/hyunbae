#include "Tetris.h"

#include <iostream>
using namespace std;

InputManager* InputManager::instance = nullptr;

int main()
{
	Tetris* t = new Tetris;
	t->rendering();
	delete t;
}