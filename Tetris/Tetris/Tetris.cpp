#include "Tetris.h"

#include <iomanip>
#include <ctime>
#define DELAY_TIME 500
#define BLOCK_OBJECTS 7
#define ROTATE_TIMES 4
#define SIZE_OF_BLOCK 4
#define DEFAULT_ROTATE_MODE 0

enum blockNum
{
	BLOCK_LINE,
	BLOCK_RIGHT_STAIR,
	BLOCK_LEFT_STAIR,
	BLOCK_L,
	BLOCK_BACK_L,
	BLOCK_ARROW,
	BLOCK_SQUARE
};

Tetris::Tetris(int width, int height) : score(0), wall{ L'▩' }, block { L'■' }, space{ L'\u3000' },
	buffer{ new wchar_t[getScreenSize()] }, inputManager(*InputManager::getInstance()),
	choose_block(-1), adjust_block_check(false), delay_complete(false), falling_down(false), rotate_mode(DEFAULT_ROTATE_MODE)
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	Borland::initialize();

	this->width = width;
	this->height = height;

	srand((unsigned int)time(NULL));
	next_block = rand() % BLOCK_OBJECTS;
	block_pos = new Position ** [BLOCK_OBJECTS];

	for (int i = 0; i < BLOCK_OBJECTS; i++)
	{
		block_pos[i] = new Position * [ROTATE_TIMES];
		for (int j = 0; j < ROTATE_TIMES; j++)
		{
			block_pos[i][j] = new Position[SIZE_OF_BLOCK];
		}
	}

	resetBuffer();
	initializeBlockPos();
}

Tetris::~Tetris()
{
	delete[] buffer;
	for (int i = 0; i < BLOCK_OBJECTS; i++)
	{
		delete[] block_pos[i];
		for (int j = 0; j < ROTATE_TIMES; j++)
		{
			delete[] block_pos[i][j];
		}
	}
	delete[] block_pos;
}

void Tetris::initializeBlockPos()
{
	for (choose_block = 0; choose_block < BLOCK_OBJECTS - 1; choose_block++)
	{
		for (rotate_mode = 0; rotate_mode < ROTATE_TIMES; rotate_mode++)
		{
			resetBlockPos();
		}
	}
	choose_block = BLOCK_SQUARE;
	rotate_mode = 0;
	resetBlockPos();
}

void Tetris::resetBuffer()
{
	wmemset(buffer, space, getScreenSize()); // \u3000 은 2바이트 크기의 넓은 빈칸.
	for (int i = 0; i <= getScreenWidth() - 2; i++)
	{
		buffer[i] = wall;
		buffer[getScreenWidth() * (getScreenHeight() - 1) + i] = wall;
	}
	for (int i = 1; i <= getScreenHeight() - 2; i++)
	{
		buffer[getScreenWidth() * i] = wall;
		buffer[getScreenWidth() * (i + 1) - 2] = wall;
		buffer[getScreenWidth() * (i + 1) - 1] = '\n';
	}
	buffer[getScreenWidth() - 1] = '\n';
	buffer[getScreenSize() - 1] = '\0';

	Borland::gotoxy(0, 0);
	wcout << buffer;
}

void Tetris::resetBlockPos()
{
	switch (choose_block)
	{
	case BLOCK_LINE:
		switch (rotate_mode)
		{
		case 0:
			block_pos[BLOCK_LINE][rotate_mode][0].setPos(x, y);
			block_pos[BLOCK_LINE][rotate_mode][1].setPos(x, y + 1);
			block_pos[BLOCK_LINE][rotate_mode][2].setPos(x, y + 2);
			block_pos[BLOCK_LINE][rotate_mode][3].setPos(x, y + 3);
			break;
		case 1:
			block_pos[BLOCK_LINE][rotate_mode][0].setPos(x, y);
			block_pos[BLOCK_LINE][rotate_mode][1].setPos(x - 1, y);
			block_pos[BLOCK_LINE][rotate_mode][2].setPos(x - 2, y);
			block_pos[BLOCK_LINE][rotate_mode][3].setPos(x - 3, y);
			break;
		case 2:
			block_pos[BLOCK_LINE][rotate_mode][0].setPos(x, y);
			block_pos[BLOCK_LINE][rotate_mode][1].setPos(x, y - 1);
			block_pos[BLOCK_LINE][rotate_mode][2].setPos(x, y - 2);
			block_pos[BLOCK_LINE][rotate_mode][3].setPos(x, y - 3);
			break;
		case 3:
			block_pos[BLOCK_LINE][rotate_mode][0].setPos(x, y);
			block_pos[BLOCK_LINE][rotate_mode][1].setPos(x + 1, y);
			block_pos[BLOCK_LINE][rotate_mode][2].setPos(x + 2, y);
			block_pos[BLOCK_LINE][rotate_mode][3].setPos(x + 3, y);
		}
		break;
	case BLOCK_RIGHT_STAIR:
		switch (rotate_mode)
		{
		case 0:
			block_pos[BLOCK_RIGHT_STAIR][rotate_mode][0].setPos(x, y);
			block_pos[BLOCK_RIGHT_STAIR][rotate_mode][1].setPos(x + 1, y);
			block_pos[BLOCK_RIGHT_STAIR][rotate_mode][2].setPos(x, y + 1);
			block_pos[BLOCK_RIGHT_STAIR][rotate_mode][3].setPos(x - 1, y + 1);
			break;
		case 1:
			block_pos[BLOCK_RIGHT_STAIR][rotate_mode][0].setPos(x, y);
			block_pos[BLOCK_RIGHT_STAIR][rotate_mode][1].setPos(x, y + 1);
			block_pos[BLOCK_RIGHT_STAIR][rotate_mode][2].setPos(x - 1, y);
			block_pos[BLOCK_RIGHT_STAIR][rotate_mode][3].setPos(x - 1, y - 1);
			break;
		case 2:
			block_pos[BLOCK_RIGHT_STAIR][rotate_mode][0].setPos(x, y);
			block_pos[BLOCK_RIGHT_STAIR][rotate_mode][1].setPos(x - 1, y);
			block_pos[BLOCK_RIGHT_STAIR][rotate_mode][2].setPos(x, y - 1);
			block_pos[BLOCK_RIGHT_STAIR][rotate_mode][3].setPos(x + 1, y - 1);
			break;
		case 3:
			block_pos[BLOCK_RIGHT_STAIR][rotate_mode][0].setPos(x, y);
			block_pos[BLOCK_RIGHT_STAIR][rotate_mode][1].setPos(x, y - 1);
			block_pos[BLOCK_RIGHT_STAIR][rotate_mode][2].setPos(x + 1, y);
			block_pos[BLOCK_RIGHT_STAIR][rotate_mode][3].setPos(x + 1, y + 1);
		}
		break;
	case BLOCK_LEFT_STAIR:
		switch (rotate_mode)
		{
		case 0:
			block_pos[BLOCK_LEFT_STAIR][rotate_mode][0].setPos(x, y);
			block_pos[BLOCK_LEFT_STAIR][rotate_mode][1].setPos(x - 1, y);
			block_pos[BLOCK_LEFT_STAIR][rotate_mode][2].setPos(x, y + 1);
			block_pos[BLOCK_LEFT_STAIR][rotate_mode][3].setPos(x + 1, y + 1);
			break;
		case 1:
			block_pos[BLOCK_LEFT_STAIR][rotate_mode][0].setPos(x, y);
			block_pos[BLOCK_LEFT_STAIR][rotate_mode][1].setPos(x, y - 1);
			block_pos[BLOCK_LEFT_STAIR][rotate_mode][2].setPos(x - 1, y);
			block_pos[BLOCK_LEFT_STAIR][rotate_mode][3].setPos(x - 1, y + 1);
			break;
		case 2:
			block_pos[BLOCK_LEFT_STAIR][rotate_mode][0].setPos(x, y);
			block_pos[BLOCK_LEFT_STAIR][rotate_mode][1].setPos(x + 1, y);
			block_pos[BLOCK_LEFT_STAIR][rotate_mode][2].setPos(x, y - 1);
			block_pos[BLOCK_LEFT_STAIR][rotate_mode][3].setPos(x - 1, y - 1);
			break;
		case 3:
			block_pos[BLOCK_LEFT_STAIR][rotate_mode][0].setPos(x, y);
			block_pos[BLOCK_LEFT_STAIR][rotate_mode][1].setPos(x, y + 1);
			block_pos[BLOCK_LEFT_STAIR][rotate_mode][2].setPos(x + 1, y);
			block_pos[BLOCK_LEFT_STAIR][rotate_mode][3].setPos(x + 1, y - 1);
		}
		break;
	case BLOCK_L:
		switch (rotate_mode)
		{
		case 0:
			block_pos[BLOCK_L][rotate_mode][0].setPos(x, y);
			block_pos[BLOCK_L][rotate_mode][1].setPos(x, y + 1);
			block_pos[BLOCK_L][rotate_mode][2].setPos(x, y + 2);
			block_pos[BLOCK_L][rotate_mode][3].setPos(x + 1, y + 2);
			break;
		case 1:
			block_pos[BLOCK_L][rotate_mode][0].setPos(x, y);
			block_pos[BLOCK_L][rotate_mode][1].setPos(x - 1, y);
			block_pos[BLOCK_L][rotate_mode][2].setPos(x - 2, y);
			block_pos[BLOCK_L][rotate_mode][3].setPos(x - 2, y + 1);
			break;
		case 2:
			block_pos[BLOCK_L][rotate_mode][0].setPos(x, y);
			block_pos[BLOCK_L][rotate_mode][1].setPos(x, y - 1);
			block_pos[BLOCK_L][rotate_mode][2].setPos(x, y - 2);
			block_pos[BLOCK_L][rotate_mode][3].setPos(x - 1, y - 2);
			break;
		case 3:
			block_pos[BLOCK_L][rotate_mode][0].setPos(x, y);
			block_pos[BLOCK_L][rotate_mode][1].setPos(x + 1, y);
			block_pos[BLOCK_L][rotate_mode][2].setPos(x + 2, y);
			block_pos[BLOCK_L][rotate_mode][3].setPos(x + 2, y - 1);
		}
		break;
	case BLOCK_BACK_L:
		switch (rotate_mode)
		{
		case 0:
			block_pos[BLOCK_BACK_L][rotate_mode][0].setPos(x, y);
			block_pos[BLOCK_BACK_L][rotate_mode][1].setPos(x, y + 1);
			block_pos[BLOCK_BACK_L][rotate_mode][2].setPos(x, y + 2);
			block_pos[BLOCK_BACK_L][rotate_mode][3].setPos(x - 1, y + 2);
			break;
		case 1:
			block_pos[BLOCK_BACK_L][rotate_mode][0].setPos(x, y);
			block_pos[BLOCK_BACK_L][rotate_mode][1].setPos(x - 1, y);
			block_pos[BLOCK_BACK_L][rotate_mode][2].setPos(x - 2, y);
			block_pos[BLOCK_BACK_L][rotate_mode][3].setPos(x - 2, y - 1);
			break;
		case 2:
			block_pos[BLOCK_BACK_L][rotate_mode][0].setPos(x, y);
			block_pos[BLOCK_BACK_L][rotate_mode][1].setPos(x, y - 1);
			block_pos[BLOCK_BACK_L][rotate_mode][2].setPos(x, y - 2);
			block_pos[BLOCK_BACK_L][rotate_mode][3].setPos(x + 1, y - 2);
			break;
		case 3:
			block_pos[BLOCK_BACK_L][rotate_mode][0].setPos(x, y);
			block_pos[BLOCK_BACK_L][rotate_mode][1].setPos(x + 1, y);
			block_pos[BLOCK_BACK_L][rotate_mode][2].setPos(x + 2, y);
			block_pos[BLOCK_BACK_L][rotate_mode][3].setPos(x + 2, y + 1);
		}
		break;
	case BLOCK_ARROW:
		switch (rotate_mode)
		{
		case 0:
			block_pos[BLOCK_ARROW][rotate_mode][0].setPos(x, y);
			block_pos[BLOCK_ARROW][rotate_mode][1].setPos(x - 1, y + 1);
			block_pos[BLOCK_ARROW][rotate_mode][2].setPos(x, y + 1);
			block_pos[BLOCK_ARROW][rotate_mode][3].setPos(x + 1, y + 1);
			break;
		case 1:
			block_pos[BLOCK_ARROW][rotate_mode][0].setPos(x, y);
			block_pos[BLOCK_ARROW][rotate_mode][1].setPos(x - 1, y - 1);
			block_pos[BLOCK_ARROW][rotate_mode][2].setPos(x - 1, y);
			block_pos[BLOCK_ARROW][rotate_mode][3].setPos(x - 1, y + 1);
			break;
		case 2:
			block_pos[BLOCK_ARROW][rotate_mode][0].setPos(x, y);
			block_pos[BLOCK_ARROW][rotate_mode][1].setPos(x - 1, y - 1);
			block_pos[BLOCK_ARROW][rotate_mode][2].setPos(x, y - 1);
			block_pos[BLOCK_ARROW][rotate_mode][3].setPos(x + 1, y - 1);
			break;
		case 3:
			block_pos[BLOCK_ARROW][rotate_mode][0].setPos(x, y);
			block_pos[BLOCK_ARROW][rotate_mode][1].setPos(x + 1, y - 1);
			block_pos[BLOCK_ARROW][rotate_mode][2].setPos(x + 1, y);
			block_pos[BLOCK_ARROW][rotate_mode][3].setPos(x + 1, y + 1);
		}
		break;
	case BLOCK_SQUARE:
		block_pos[BLOCK_SQUARE][rotate_mode][0].setPos(x, y);
		block_pos[BLOCK_SQUARE][rotate_mode][1].setPos(x + 1, y);
		block_pos[BLOCK_SQUARE][rotate_mode][2].setPos(x, y + 1);
		block_pos[BLOCK_SQUARE][rotate_mode][3].setPos(x + 1, y + 1);
	}
}


// ##### OPERATION #####
void Tetris::rendering()
{
	readyForStart();
	while (true)
	{
		scoreBoard();
		createRandomBlock();
		gameoverCheck();
	}
}

void Tetris::clear()
{
	Borland::gotoxy(0, 0);
	wcout << buffer;
}

void Tetris::drawCurrentPos()
{
	draw(curr_pos.x, curr_pos.y);
}

void Tetris::draw(int x, int y)
{
	Borland::gotoxyX2(x, y);
	wcout << block;
}

void Tetris::draw(Position pos)
{
	resetBlockPos();
	Borland::gotoxyX2(pos);
	wcout << block;
}

void Tetris::draw(Position*** pos)
{
	resetBlockPos();
	for (int i = 0; i < SIZE_OF_BLOCK; i++)
	{
		Borland::gotoxyX2(pos[choose_block][rotate_mode][i]);
		wcout << block;
	}
}

void Tetris::nextBlock()
{
	srand((unsigned int)time(NULL));
	next_block = rand() % BLOCK_OBJECTS;

	for (int i = 0; i <= 7; i++)
	{
		Borland::gotoxyX2(getScreenWidth(), i);
		wcout << "                    ";
	}

	Borland::gotoxyX2(getScreenWidth() + 2, 2);
	wcout << "NEXT BLOCK";

	curr_pos.setPos(getScreenWidth() + 3, 4);
	draw(curr_pos);

	for (int i = 0; i < 3; i++)
	{
		curr_pos.setPos(curr_pos.x + (block_pos[next_block][0][i + 1].x - block_pos[next_block][0][i].x), curr_pos.y + (block_pos[next_block][0][i + 1].y - block_pos[next_block][0][i].y));
		draw(curr_pos);

		/*
		Borland::gotoxyX2(getScreenWidth() + i * 2 + 1, 0);
		wcout << setw(2) << (block_pos[next_block][0][i + 1].x - block_pos[next_block][0][i].x) << setw(2) << (block_pos[next_block][0][i + 1].y - block_pos[next_block][0][i].y);*/
	}
}

void Tetris::readyForStart()
{
	while (true)
	{
		inputManager.readInputs();
		Borland::gotoxyX2(1, getScreenHeight() / 2);
		wcout << " PRESS 'INSERT' ";
		Borland::gotoxyX2(3, getScreenHeight() / 2 + 1);
		wcout << "TO START";

		Sleep(100);

		if (inputManager.GetKeyDown(VK_INSERT))
		{
			inputManager.consumeAllEvent();
			clear();
			break;
		}
		else
			inputManager.consumeAllEvent();
	}
}

void Tetris::scoreBoard()
{
	Borland::gotoxyX2(getScreenWidth() + 2, getScreenHeight() / 2);
	wcout << "SCORE: " << score;
}

void Tetris::gameoverCheck()
{
	for (int i = 0; i < getScreenWidth(); i++)
	{
		if (buffer[i] == block)
		{
			Borland::gotoxyX2(getScreenWidth() + 2, getScreenHeight() / 2 + 2);
			wcout << "### GAME OVER!! ###";
			Borland::gotoxyX2(0, getScreenHeight() + 3);
			exit(1);
		}
	}
}

// ##### CREATE BLOCK OBJECTS #####

void Tetris::createRandomBlock()
{
	bool collision = false;
	choose_block = next_block;

	nextBlock();

	for (y = initial_pos.y; !collision; y++)
	{
		blockRendering(collision);
		delayMoveClear(collision); // 처음 블럭이 등장 후 보고 유저가 컨트롤하므로 블럭 표시보다 뒤에 위치
		if (adjust_block_check) { y--; adjust_block_check = false; }
	}
	x = initial_pos.x;
	falling_down = false;
	rotate_mode = DEFAULT_ROTATE_MODE;
}

bool Tetris::moveLeftOrRight()
{
	if (inputManager.GetKeyDown(VK_LEFT) || inputManager.GetKeyDown(VK_RIGHT))
		return true;
	return false;
}

void Tetris::delay()
{
	MSG msg;
	DWORD dwStart = GetTickCount64(); // GetTickCount64()는 시간이 지나면서 1초당 1000씩 증가한 값을 반환한다.

	while (GetTickCount64() - dwStart < DELAY_TIME && !(moveLeftOrRight() || inputManager.GetKeyDown(VK_SPACE)
		|| inputManager.GetKeyDown(VK_DOWN) || inputManager.GetKeyDown(VK_UP)))  // 1000 = 1초
	{
		inputManager.readInputs(); // 입력 대기. 키 입력이 발생하면 deque 구조의 인풋 버퍼에 push_back으로 키 값이 추가된다. InputManager.cpp 참조
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	if (GetTickCount64() - dwStart >= DELAY_TIME)
		delay_complete = true;
}

void Tetris::fastenBlock()
{
	if (inputManager.GetKeyDown(VK_DOWN))
		delay_complete = true;
}

void Tetris::fallBlock()
{
	if (inputManager.GetKeyDown(VK_SPACE))
	{
		delay_complete = true;
		falling_down = true;
	}
}

void Tetris::rotateBlock()
{
	if (inputManager.GetKeyDown(VK_UP))
	{
		adjust_block_check = true;
		switch (choose_block)
		{
		case BLOCK_LINE:
			rotateBlockLine();
			break;
		case BLOCK_RIGHT_STAIR:
			rotateBlockRightStair();
			break;
		case BLOCK_LEFT_STAIR:
			rotateBlockLeftStair();
			break;
		case BLOCK_L:
			rotateBlockL();
			break;
		case BLOCK_BACK_L:
			rotateBlockBackL();
			break;
		case BLOCK_ARROW:
			rotateBlockArrow();
		}
	}
}

void Tetris::moveBlock()
{
	if (moveLeftOrRight())
	{
		delay_complete = false;
		adjust_block_check = true;
		if (inputManager.GetKeyDown(VK_LEFT))
			x--;
		else if (inputManager.GetKeyDown(VK_RIGHT))
			x++;
	}
}

void Tetris::delayMoveClear(bool& collision)
{
	if (!(falling_down || collision))
	{
		inputManager.consumeAllEvent(); // 인풋 버퍼에 있는 모든 데이터를 pop 한다.
		delay();
		fastenBlock();
		fallBlock();
		rotateBlock();
		moveBlock();
	}
	clear();
}

bool Tetris::bufferObstacleCheck(Position*** pos)
{
	resetBlockPos();
	int count = 0;
	for (int i = 0; i < SIZE_OF_BLOCK; i++)
	{
		if (buffer[pos[choose_block][rotate_mode][i].x + pos[choose_block][rotate_mode][i].y * getScreenWidth()] == space)
			count++;
	}
	if (count == 4)
		return false;
	else return true;
}

void Tetris::setBufferBlock(Position*** pos)
{
	resetBlockPos();
	for (int i = 0; i < SIZE_OF_BLOCK; i++)
	{
		buffer[pos[choose_block][rotate_mode][i].x + (pos[choose_block][rotate_mode][i].y - 1) * getScreenWidth()] = block;
	}
}


// ##### BLOCK OBJECTS RENDERING #####
void Tetris::blockRendering(bool& collision)
{
	if (bufferObstacleCheck(block_pos))
	{
		if (inputManager.GetKeyDown(VK_LEFT))
			x++;
		else if (inputManager.GetKeyDown(VK_RIGHT))
			x--;
		if (delay_complete)
		{
			collision = true;

			setBufferBlock(block_pos);

			clear();
			lineBingoCheck();

			return;
		}
	}

	draw(block_pos);
}

void Tetris::lineBingoCheck()
{
	int count = 0;

	for (int i = getScreenSize() - 2; i > getScreenWidth(); i--)
	{
		if (buffer[i] == block)
			count++;
		else count = 0;
		if (count == getScreenWidth() - 3)
		{
			for (int j = i; buffer[j] == block; j++)
			{
				Borland::gotoxyX2(j % getScreenWidth(), j / getScreenWidth());
				wcout << L'※';
				Sleep(100);
			}
			lineBingo(i);
			clear();
			score += 100;
			i = i + getScreenWidth() * 1;
		}
	}
}

void Tetris::lineBingo(int index)
{
	for (int i = index; buffer[i] == block || buffer[i] == space; i++)
	{
		buffer[i] = buffer[i - getScreenWidth()];
	}
	if (index > getScreenWidth() * 3)
		lineBingo(index - getScreenWidth());
}

// ##### Rotate Blocks #####
void Tetris::rotateBlockLine()
{
	int count = 0;
	switch (rotate_mode)
	{
	case 0: // 세로 -> 가로
		for (int j = y + 1; j < y + 3 && count < 4; j++)
		{
			count = 0;
			for (int i = x + 2; i > x - 3; i--)
			{
				if (buffer[i + j * getScreenWidth()] != space)
					count = 0;
				else count++;
				if (count == 4) // 연속해서 4칸이 빈공간일 경우 그 공간에 회전된 블럭 집어넣음.
				{
					rotate_mode = 1;
					x = i + 3;
					y = j;
					break;
				}
			}
		}
		break;
	case 1: // 가로 -> 세로
		for (int i = x - 1; i > x - 3 && count < 4; i--)
		{
			count = 0;
			for (int j = y + 2; j > y - 3; j--)
			{
				if (buffer[i + j * getScreenWidth()] != space)
					count = 0;
				else count++;
				if (count == 4) // 연속해서 4칸이 빈공간일 경우 그 공간에 회전된 블럭 집어넣음.
				{
					rotate_mode = 2;
					x = i;
					y = j + 3;
					break;
				}
			}
		}
		break;
	case 2: // 세로 -> 가로
		for (int j = y - 1; j > y - 3 && count < 4; j--)
		{
			count = 0;
			for (int i = x - 2; i < x + 3; i++)
			{
				if (buffer[i + j * getScreenWidth()] != space)
					count = 0;
				else count++;
				if (count == 4) // 연속해서 4칸이 빈공간일 경우 그 공간에 회전된 블럭 집어넣음.
				{
					rotate_mode = 3;
					x = i - 3;
					y = j;
					break;
				}
			}
		}
		break;
	case 3: // 가로 -> 세로
		for (int i = x + 1; i < x + 3 && count < 4; i++)
		{
			count = 0;
			for (int j = y - 2; j < y + 3; j++)
			{
				if (buffer[i + j * getScreenWidth()] != space)
					count = 0;
				else count++;
				if (count == 4) // 연속해서 4칸이 빈공간일 경우 그 공간에 회전된 블럭 집어넣음.
				{
					rotate_mode = 0;
					x = i;
					y = j - 3;
					break;
				}
			}
		}
		break;
	}
}

void Tetris::rotateBlockRightStair()
{
	switch (rotate_mode)
	{
	case 0: // 가로 계단 -> 세로 계단
		for (int j = y + 1; j > y - 1; j--)
		{
			for (int i = x + 1; i > x - 1; i--)
			{
				if (buffer[i + j * getScreenWidth()] == space
					&& buffer[i + (j + 1) * getScreenWidth()] == space
					&& buffer[(i - 1) + j * getScreenWidth()] == space
					&& buffer[(i - 1) + (j - 1) * getScreenWidth()] == space)
				{
					rotate_mode = 1;
					x = i;
					y = j;
					return;
				}
			}
		}
		break;
	case 1: // 세로 계단 -> 가로 계단
		for (int i = x - 1; i < x + 1; i++)
		{
			for (int j = y + 1; j > y - 1; j--)
			{
				if (buffer[i + j * getScreenWidth()] == space
					&& buffer[(i - 1) + j * getScreenWidth()] == space
					&& buffer[i + (j - 1) * getScreenWidth()] == space
					&& buffer[(i + 1) + (j - 1) * getScreenWidth()] == space)
				{
					rotate_mode = 2;
					x = i;
					y = j;
					return;
				}
			}
		}
		break;
	case 2: // 가로 계단 -> 세로 계단
		for (int j = y - 1; j < y + 1; j++)
		{
			for (int i = x - 1; i < x + 1; i++)
			{
				if (buffer[i + j * getScreenWidth()] == space
					&& buffer[i + (j - 1) * getScreenWidth()] == space
					&& buffer[(i + 1) + j * getScreenWidth()] == space
					&& buffer[(i + 1) + (j + 1) * getScreenWidth()] == space)
				{
					rotate_mode = 3;
					x = i;
					y = j;
					return;
				}
			}
		}
		break;
	case 3: // 세로 계단 -> 가로 계단
		for (int i = x + 1; i > x - 1; i--)
		{
			for (int j = y - 1; j < y + 1; j++)
			{
				if (buffer[i + j * getScreenWidth()] == space
					&& buffer[(i + 1) + j * getScreenWidth()] == space
					&& buffer[i + (j + 1) * getScreenWidth()] == space
					&& buffer[(i - 1) + (j + 1) * getScreenWidth()] == space)
				{
					rotate_mode = 0;
					x = i;
					y = j;
					return;
				}
			}
		}
		break;
	}
}

void Tetris::rotateBlockLeftStair()
{
	switch (rotate_mode)
	{
	case 0: // 가로 계단 -> 세로 계단
		for (int j = y + 1; j > y - 1; j--)
		{
			for (int i = x + 1; i > x - 1; i--)
			{
				if (buffer[i + j * getScreenWidth()] == space
					&& buffer[i + (j - 1) * getScreenWidth()] == space
					&& buffer[(i - 1) + j * getScreenWidth()] == space
					&& buffer[(i - 1) + (j + 1) * getScreenWidth()] == space)
				{
					rotate_mode = 1;
					x = i;
					y = j;
					return;
				}
			}
		}
		break;
	case 1: // 세로 계단 -> 가로 계단
		for (int i = x - 1; i < x + 1; i++)
		{
			for (int j = y + 1; j > y - 1; j--)
			{
				if (buffer[i + j * getScreenWidth()] == space
					&& buffer[(i + 1) + j * getScreenWidth()] == space
					&& buffer[i + (j - 1) * getScreenWidth()] == space
					&& buffer[(i - 1) + (j - 1) * getScreenWidth()] == space)
				{
					rotate_mode = 2;
					x = i;
					y = j;
					return;
				}
			}
		}
		break;
	case 2: // 가로 계단 -> 세로 계단
		for (int j = y - 1; j < y + 1; j++)
		{
			for (int i = x - 1; i < x + 1; i++)
			{
				if (buffer[i + j * getScreenWidth()] == space
					&& buffer[i + (j + 1) * getScreenWidth()] == space
					&& buffer[(i + 1) + j * getScreenWidth()] == space
					&& buffer[(i + 1) + (j - 1) * getScreenWidth()] == space)
				{
					rotate_mode = 3;
					x = i;
					y = j;
					return;
				}
			}
		}
		break;
	case 3: // 세로 계단 -> 가로 계단
		for (int i = x + 1; i > x - 1; i--)
		{
			for (int j = y - 1; j < y + 1; j++)
			{
				if (buffer[i + j * getScreenWidth()] == space
					&& buffer[(i - 1) + j * getScreenWidth()] == space
					&& buffer[i + (j + 1) * getScreenWidth()] == space
					&& buffer[(i + 1) + (j + 1) * getScreenWidth()] == space)
				{
					rotate_mode = 0;
					x = i;
					y = j;
					return;
				}
			}
		}
		break;
	}
}

void Tetris::rotateBlockL()
{
	switch (rotate_mode)
	{
	case 0:
		for (int i = x + 1; i < x + 3; i++)
		{
			for (int j = y + 1; j > y - 1; j--)
			{
				if (buffer[i + j * getScreenWidth()] == space
					&& buffer[(i - 1) + j * getScreenWidth()] == space
					&& buffer[(i - 2) + j * getScreenWidth()] == space
					&& buffer[(i - 2) + (j + 1) * getScreenWidth()] == space)
				{
					rotate_mode = 1;
					x = i;
					y = j;
					return;
				}
			}
		}
		break;
	case 1:
		for (int j = y + 1; j < y + 3; j++)
		{
			for (int i = x - 1; i < x + 1; i++)
			{
				if (buffer[i + j * getScreenWidth()] == space
					&& buffer[i + (j - 1) * getScreenWidth()] == space
					&& buffer[i + (j - 2) * getScreenWidth()] == space
					&& buffer[(i - 1) + (j - 2) * getScreenWidth()] == space)
				{
					rotate_mode = 2;
					x = i;
					y = j;
					return;
				}
			}
		}
		break;
	case 2:
		for (int i = x - 1; i > x - 3; i--)
		{
			for (int j = y - 1; j < y + 1; j++)
			{
				if (buffer[i + j * getScreenWidth()] == space
					&& buffer[(i + 1) + j * getScreenWidth()] == space
					&& buffer[(i + 2) + j * getScreenWidth()] == space
					&& buffer[(i + 2) + (j - 1) * getScreenWidth()] == space)
				{
					rotate_mode = 3;
					x = i;
					y = j;
					return;
				}
			}
		}
		break;
	case 3:
		for (int j = y - 1; j > y - 3; j--)
		{
			for (int i = x + 1; i > x - 1; i--)
			{
				if (buffer[i + j * getScreenWidth()] == space
					&& buffer[i + (j + 1) * getScreenWidth()] == space
					&& buffer[i + (j + 2) * getScreenWidth()] == space
					&& buffer[(i + 1) + (j + 2) * getScreenWidth()] == space)
				{
					rotate_mode = 0;
					x = i;
					y = j;
					return;
				}
			}
		}
	}
}

void Tetris::rotateBlockBackL()
{
	switch (rotate_mode)
	{
	case 0:
		for (int i = x + 1; i < x + 3; i++)
		{
			for (int j = y + 1; j < y + 3; j++)
			{
				if (buffer[i + j * getScreenWidth()] == space
					&& buffer[(i - 1) + j * getScreenWidth()] == space
					&& buffer[(i - 2) + j * getScreenWidth()] == space
					&& buffer[(i - 2) + (j - 1) * getScreenWidth()] == space)
				{
					rotate_mode = 1;
					x = i;
					y = j;
					return;
				}
			}
		}
		break;
	case 1:
		for (int j = y + 1; j < y + 3; j++)
		{
			for (int i = x - 1; i > x - 3; i--)
			{
				if (buffer[i + j * getScreenWidth()] == space
					&& buffer[i + (j - 1) * getScreenWidth()] == space
					&& buffer[i + (j - 2) * getScreenWidth()] == space
					&& buffer[(i + 1) + (j - 2) * getScreenWidth()] == space)
				{
					rotate_mode = 2;
					x = i;
					y = j;
					return;
				}
			}
		}
		break;
	case 2:
		for (int i = x - 1; i > x - 3; i--)
		{
			for (int j = y - 1; j > y - 3; j--)
			{
				if (buffer[i + j * getScreenWidth()] == space
					&& buffer[(i + 1) + j * getScreenWidth()] == space
					&& buffer[(i + 2) + j * getScreenWidth()] == space
					&& buffer[(i + 2) + (j + 1) * getScreenWidth()] == space)
				{
					rotate_mode = 3;
					x = i;
					y = j;
					return;
				}
			}
		}
		break;
	case 3:
		for (int j = y - 1; j > y - 3; j--)
		{
			for (int i = x + 1; i < x + 3; i++)
			{
				if (buffer[i + j * getScreenWidth()] == space
					&& buffer[i + (j + 1) * getScreenWidth()] == space
					&& buffer[i + (j + 2) * getScreenWidth()] == space
					&& buffer[(i - 1) + (j + 2) * getScreenWidth()] == space)
				{
					rotate_mode = 0;
					x = i;
					y = j;
					return;
				}
			}
		}
	}
}

void Tetris::rotateBlockArrow()
{
	switch (rotate_mode)
	{
	case 0:
		for (int j = y + 1; j > y - 1; j--)
		{
			for (int i = x + 1; i > x - 1; i--)
			{
				if (buffer[i + j * getScreenWidth()] == space
					&& buffer[(i - 1) + (j - 1) * getScreenWidth()] == space
					&& buffer[(i - 1) + j * getScreenWidth()] == space
					&& buffer[(i - 1) + (j + 1) * getScreenWidth()] == space)
				{
					rotate_mode = 1;
					x = i;
					y = j;
					return;
				}
			}
		}
		break;
	case 1:
		for (int i = x - 1; i < x + 1; i++)
		{
			for (int j = y + 1; j > y - 1; j--)
			{
				if (buffer[i + j * getScreenWidth()] == space
					&& buffer[(i - 1) + (j - 1) * getScreenWidth()] == space
					&& buffer[i + (j - 1) * getScreenWidth()] == space
					&& buffer[(i + 1) + (j - 1) * getScreenWidth()] == space)
				{
					rotate_mode = 2;
					x = i;
					y = j;
					return;
				}
			}
		}
		break;
	case 2:
		for (int j = y - 1; j < y + 1; j++)
		{
			for (int i = x - 1; i < x + 1; i++)
			{
				if (buffer[i + j * getScreenWidth()] == space
					&& buffer[(i + 1) + (j - 1) * getScreenWidth()] == space
					&& buffer[(i + 1) + j * getScreenWidth()] == space
					&& buffer[(i + 1) + (j + 1) * getScreenWidth()] == space)
				{
					rotate_mode = 3;
					x = i;
					y = j;
					return;
				}
			}
		}
		break;
	case 3:
		for (int i = x + 1; i > x - 1; i--)
		{
			for (int j = y - 1; j < y + 1; j++)
			{
				if (buffer[i + j * getScreenWidth()] == space
					&& buffer[(i - 1) + (j + 1) * getScreenWidth()] == space
					&& buffer[i + (j + 1) * getScreenWidth()] == space
					&& buffer[(i + 1) + (j + 1) * getScreenWidth()] == space)
				{
					rotate_mode = 0;
					x = i;
					y = j;
					return;
				}
			}
		}
	}
}