#pragma once

#include "PanelScript.h"
#include "GridPanel.h"
#include <iomanip>

class AdjustingPanel :
    public GameObject
{
    Scene& scene;
    PanelScript panel;
    GridPanel* grid;
public:
    AdjustingPanel(Position lefttop, int width, int height, GridPanel* grid);
    void draw();
    void adjustGridSize();
    void adjustGridReset();
    void start() override;
    void update() override;
};