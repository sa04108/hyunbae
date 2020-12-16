#include "Keynmouse.h"
#include "ScreenSize.h"
#include "GetPosition.h"

int Keynmouse::mouseinput = 0;
int Keynmouse::keyinput = 0;
short Keynmouse::x = 0;
short Keynmouse::y = 0;

Keynmouse::Keynmouse() {
    cNumRead = 0;
    memset(irInBuf, NULL, sizeof(irInBuf));
    // Get the standard input handle. 

    hStdin = GetStdHandle(STD_INPUT_HANDLE);
    if (hStdin == INVALID_HANDLE_VALUE)
        ErrorExit("GetStdHandle         ");

    // Save the current input mode, to be restored on exit. 

    if (!GetConsoleMode(hStdin, &fdwSaveOldMode))
        ErrorExit("GetConsoleMode           ");

    // Enable the window and mouse input events. 

    fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
    if (!SetConsoleMode(hStdin, fdwMode))
        ErrorExit("SetConsoleMode           ");
}

void Keynmouse::rcInput() {
    // Wait for the events. 
    if (!ReadConsoleInput(
        hStdin,      // input buffer handle 
        irInBuf,     // buffer to read into 
        128,         // size of read buffer 
        &cNumRead)) // number of records read 
        ErrorExit("ReadConsoleInput         ");

    // Dispatch the events to the appropriate handler. 
    for (int i = 0; i < cNumRead; i++)
    {
        GetPosition::gotoxy(0, ScreenSize::height + 1);
        switch (irInBuf[i].EventType)
        {
        case KEY_EVENT: // keyboard input 
            KeyEventProc(irInBuf[i].Event.KeyEvent, ScreenSize::height + 1);
            break;

        case MOUSE_EVENT: // mouse input 
            MouseEventProc(irInBuf[i].Event.MouseEvent);
            break;

        case WINDOW_BUFFER_SIZE_EVENT: // scrn buf. resizing 
            ResizeEventProc(irInBuf[i].Event.WindowBufferSizeEvent);
            break;

        case FOCUS_EVENT:  // disregard focus events 

        case MENU_EVENT:   // disregard menu events 
            break;

        default:
            ErrorExit("Unknown event type   ");
            break;
        }
    }
}

void Keynmouse::scMode() {
    // Restore input mode on exit.

    SetConsoleMode(hStdin, fdwSaveOldMode);
}

VOID Keynmouse::ErrorExit(const char* msg)
{
    cout << msg;

    // Restore input mode on exit.

    SetConsoleMode(hStdin, fdwSaveOldMode);

    ExitProcess(0);
}

VOID Keynmouse::KeyEventProc(KEY_EVENT_RECORD ker, short y)
{
    GetPosition::gotoxy(0, y + 2);
    cout << "Key event: ";

    if (ker.bKeyDown)
    {
        cout << (char)ker.wVirtualKeyCode << " key pressed            ";
        keyinput = ker.wVirtualKeyCode;
    }
    else
    {
        cout << (char)ker.wVirtualKeyCode << " key released           ";
        keyinput = 0;
    }
}

VOID Keynmouse::MouseEventProc(MOUSE_EVENT_RECORD mer)
{
#ifndef MOUSE_HWHEELED
#define MOUSE_HWHEELED 0x0008
#endif
    this->x = mer.dwMousePosition.X;
    this->y = mer.dwMousePosition.Y;
    cout << "Mouse Pointer: (" << x << ", " << y << ")  \n";
    cout << "Mouse event: ";

    switch (mer.dwEventFlags)
    {
    case 0:

        if (mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
        {
            cout << "left button press      ";
            mouseinput = 1;
        }
        else if (mer.dwButtonState == RIGHTMOST_BUTTON_PRESSED)
        {
            cout << "right button press     ";
            mouseinput = 2;
        }
        else
        {
            cout << "button press           ";
            mouseinput = 3;
        }
        break;
    case DOUBLE_CLICK:
        cout << "double click           ";
        mouseinput = 4;
        Sleep(100);
        break;
    case MOUSE_HWHEELED:
        cout << "horizontal mouse wheel     ";
        mouseinput = 5;
        break;
    case MOUSE_MOVED:
        cout << "mouse moved            ";
        mouseinput = 0;
        break;
    case MOUSE_WHEELED:
        cout << "vertical mouse wheel       ";
        mouseinput = 5;
        break;
    default:
        cout << "unknown                ";
        mouseinput = 0;
        break;
    }
}

VOID Keynmouse::ResizeEventProc(WINDOW_BUFFER_SIZE_RECORD wbsr)
{
    cout << "Resize event               \n";
    cout << "Console screen buffer is " << wbsr.dwSize.X << "columns by " << wbsr.dwSize.Y << "rows.\n";
}