#pragma once
#include "Scene.h"
#include <iostream>
using namespace std;

class GameObject
{
public:
	GameObject() {}
	virtual void start() {}
	virtual void update() {}
};