#include "PanelScript.h"

PanelScript::PanelScript(Position lefttop, Position rightbottom) : lefttop(lefttop), rightbottom(rightbottom)
, scene(Scene::getInstance())
{
	draw();
}

void PanelScript::draw() {
	scene.drawPanelLine(lefttop, rightbottom);
}