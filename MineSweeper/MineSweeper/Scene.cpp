#include "Scene.h"

Scene::Scene() : scene_width(80), scene_height(26) {
	scene_buffer = new char[(scene_width + 1) * scene_height];
	clearScene();
}

int Scene::getSceneWidth() {
	return scene_width;
}

int Scene::getSceneHeight() {
	return scene_height;
}

void Scene::play() {
	for (auto object : objects)
	{
		object->start();
		object->update();
	}
}

void Scene::add(GameObject* object) {
	objects.push_back(object);
}

void Scene::clearScene() {
	memset(scene_buffer, ' ', (scene_width + 1) * scene_height);
	for (int i = 0; i < scene_height; i++)
	{
		scene_buffer[i * (scene_width + 1) + (scene_width + 1) - 1] = '\n';
	}
	scene_buffer[(scene_width + 1) * scene_height - 1] = '\0';

	Position::gotoxy(0, 0);
	cout << scene_buffer;
}

void Scene::drawScene(char* buffer, Position lefttop, Position rightbottom) {
	int width = rightbottom.getPosX() - lefttop.getPosX();
	int height = rightbottom.getPosY() - lefttop.getPosY();

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			scene_buffer[lefttop.getPosX() + x + (scene_width + 1) * (y + lefttop.getPosY())] = buffer[x + y * (width + 1)];
		}
	}

	Position::gotoxy(0, 0);
	cout << scene_buffer;
}

void Scene::drawPanelLine(Position lefttop, Position rightbottom) {
	int width = rightbottom.getPosX() - lefttop.getPosX();
	int height = rightbottom.getPosY() - lefttop.getPosY();

	int y = lefttop.getPosY() - 1;
	if (y > 0) {
		scene_buffer[lefttop.getPosX() - 1 + (scene_width + 1) * y] = 1;
		scene_buffer[rightbottom.getPosX() + (scene_width + 1) * y] = 2;
		for (int x = 0; x < width; x++)
			scene_buffer[lefttop.getPosX() + x + (scene_width + 1) * y] = 6;
	}
	y = rightbottom.getPosY();
	if (y < scene_height) {
		scene_buffer[lefttop.getPosX() - 1 + (scene_width + 1) * y] = 3;
		scene_buffer[rightbottom.getPosX() + (scene_width + 1) * y] = 4;
		for (int x = 0; x < width; x++)
			scene_buffer[lefttop.getPosX() + x + (scene_width + 1) * y] = 6;
	}

	int x = lefttop.getPosX() - 1;
	if (x > 0) {
		for (int y = 0; y < height; y++)
			scene_buffer[x + (scene_width + 1) * (y + lefttop.getPosY())] = 5;
	}
	x = rightbottom.getPosX();
	if (x < scene_width) {
		for (int y = 0; y < height; y++)
			scene_buffer[x + (scene_width + 1) * (y + lefttop.getPosY())] = 5;
	}

	Position::gotoxy(0, 0);
	cout << scene_buffer;
}