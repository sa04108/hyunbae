#pragma once
#include "Position.h"
#include "GameObject.h"
#include <vector>
#include <iostream>
using namespace std;

class Scene {
	Scene();

	vector<GameObject*> objects;
	char* scene_buffer;
	int scene_width;
	int scene_height;
public:
	~Scene() { delete[] scene_buffer; }
	static Scene& getInstance() {
		static Scene instance;
		return instance;
	}

	void play();
	void add(GameObject* object);

	int getSceneWidth();
	int getSceneHeight();
	void clearScene();
	void drawScene(char* buffer, Position lefttop, Position rightbottom);
	void drawPanelLine(Position lefttop, Position rightbottom);
};