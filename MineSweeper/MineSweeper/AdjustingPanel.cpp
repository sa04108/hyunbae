#include "AdjustingPanel.h"

AdjustingPanel::AdjustingPanel(Position lefttop, int width, int height, GridPanel* grid) : panel(lefttop, Position(lefttop.getPosX() + width, lefttop.getPosY() + height)),
                                grid(grid), scene(Scene::getInstance()) {}

void AdjustingPanel::draw() {
    int x = panel.getLeftTop().getPosX();
    int y = panel.getLeftTop().getPosY();

    Position::gotoxy(x, y);
    cout << "Press 'R' Button to reset the game.";
    Position::gotoxy(x, y + 1);
    cout << "Press ←, →, ↑, ↓, to adjust the game screen.";
    Position::gotoxy(x, y + 2);
    cout << setw(2) << grid->getGridWidth() << " * " << setw(2) << grid->getGridHeight() << " (change will begin next game.)    ";
}

void AdjustingPanel::adjustGridSize()
{
    int gWidth = grid->getGridWidth();
    int gHeight = grid->getGridHeight();

    if (InputManager::keyinput == 37 && gWidth > 5)
        grid->setGridWidth(gWidth - 1);
    else if (InputManager::keyinput == 39)
        grid->setGridWidth(gWidth + 1);
    else if (InputManager::keyinput == 38 && gHeight > 5)
        grid->setGridHeight(gHeight - 1);
    else if (InputManager::keyinput == 40)
        grid->setGridHeight(gHeight + 1);
}

void AdjustingPanel::adjustGridReset()
{
    if (InputManager::keyinput == 'R')
    {
        grid->reset();
        panel.draw();
    }
}

void AdjustingPanel::start() {
}

void AdjustingPanel::update() {
    draw();
    adjustGridSize();
    adjustGridReset();
}