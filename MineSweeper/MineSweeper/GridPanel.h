#pragma once
#include <Windows.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <io.h>
#include <fcntl.h>

#include "InputManager.h"
#include "GameObject.h"
#include "Position.h"
#include "Scene.h"
#include "PanelScript.h"

using namespace std;

class GridPanel : public GameObject {
	Scene& scene;
	PanelScript panel;
	char* buffer; // char와 다르게 2바이트를 저장할 수 있으며, 유니코드 문자 저장 가능
	char* hide_buffer;

	int width;
	int height;
	int width_temp;
	int height_temp;

	int* mine_index;
	int mine_num;
	char mine;
	char block;

	int dropby_num;
	int dscvd_num;
	bool isNum;
	int moveTime;

	bool compare(int arr[], int curr);
	bool compare_dby(int* dropby);

	void getEmpty(int index, int* dropby);
	void hitMine();
	void complete();
	void draw();
	void boardText();
	void boardRefresh();

	void readyToInput();

public:
	bool gameOver;

	GridPanel(Position lefttop, int width, int height);
	~GridPanel() { delete[] buffer; delete[] hide_buffer; delete[] mine_index; }

	int getGridWidth() { return width_temp; }
	int getGridHeight() { return height_temp; }
	void setGridWidth(int width) { width_temp = width; }
	void setGridHeight(int height) { height_temp = height; }

	void reset();

	void start() override;
	void update() override;
};