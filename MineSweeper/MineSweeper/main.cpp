#include "MineSweeper.h"
#include "Keynmouse.h"

int ScreenSize::w_stored = 11;
int ScreenSize::h_stored = 10;
int ScreenSize::width_plus1 = 11;
int ScreenSize::height = 10;

int main()
{
    MineSweeper* ms = new MineSweeper;
    Keynmouse km;

    while (1)
    {
        km.rcInput();
        if (!ms->gameOver)
            ms->check();
        if (Keynmouse::keyinput == 'R')
        {
            delete ms;
            ms = new MineSweeper;
        }
        ms->setScreen();
    }

    km.scMode();
}