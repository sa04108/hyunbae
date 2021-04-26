#pragma once
#include "InputManager.h"
#include "GridPanel.h"
#include "AdjustingPanel.h"

int main()
{
    GridPanel* grid = new GridPanel(Position(5, 2), 10, 10);
    AdjustingPanel* adjusting = new AdjustingPanel(Position(5, 15), 50, 3, grid);
    InputManager im;
    Scene& scene = Scene::getInstance();

    scene.add(grid);
    scene.add(adjusting);

    while (1)
    {
        im.readInputs();
        scene.play();
    }

    delete grid;
    delete adjusting;
}