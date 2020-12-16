#pragma once
#include <Windows.h>
#include <iostream>
#include <io.h>
#include <fcntl.h>

#include "Utils.h"
#include "InputManager.h"
#include "Screen.h"

using namespace std;

class Tetris : public Screen
{
public:
	Tetris(int width = 10, int height = 20);
	~Tetris();

	void rendering();

private:
	void nextBlock();
	void readyForStart();
	void scoreBoard();
	void gameoverCheck();

	void initializeBlockPos();
	void resetBuffer();
	void resetBlockPos();
	void clear();
	void drawCurrentPos();
	void draw(int x, int y);
	void draw(Position pos);
	void draw(Position*** pos);
	void createRandomBlock();

	bool moveLeftOrRight();
	void delay();
	void fastenBlock();
	void fallBlock();
	void rotateBlock();
	void moveBlock();
	void delayMoveClear(bool& collision);
	bool bufferObstacleCheck(Position*** pos);
	void setBufferBlock(Position*** pos);

	void blockRendering(bool& collision);
	void lineBingoCheck();
	void lineBingo(int index);

	void rotateBlockLine();
	void rotateBlockRightStair();
	void rotateBlockLeftStair();
	void rotateBlockL();
	void rotateBlockBackL();
	void rotateBlockArrow();

	InputManager& inputManager;

	Position *** block_pos;
	Position curr_pos;

	int score;
	wchar_t wall;
	wchar_t block;
	wchar_t space;
	wchar_t* buffer;
	int choose_block;
	int next_block;
	bool adjust_block_check;
	bool delay_complete;
	bool falling_down;
	int rotate_mode;
};