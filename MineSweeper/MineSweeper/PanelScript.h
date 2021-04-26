#pragma once
#include "Scene.h"
#include "Position.h"

#include <iostream>
using namespace std;

class PanelScript
{
	Scene& scene;
	Position lefttop;
	Position rightbottom;
public:
	PanelScript(Position lefttop, Position rightbottom);
	Position getLeftTop() { return lefttop; }
	Position getRightBottom() { return rightbottom; }
	void setLeftTop(Position lefttop) { this->lefttop = lefttop; }
	void setRightBottom(Position rightbottom) { this->rightbottom = rightbottom; }

	void draw();
};

