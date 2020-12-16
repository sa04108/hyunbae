#pragma once
#include <Windows.h>

class Keynmouse {
    HANDLE hStdin;
    DWORD fdwSaveOldMode, cNumRead, fdwMode;
    INPUT_RECORD irInBuf[128];

public:
    static int mouseinput;
    static int keyinput;
    static short x, y;

    Keynmouse();
    void rcInput();
    void scMode();

    VOID ErrorExit(const char*);
    VOID KeyEventProc(KEY_EVENT_RECORD, short y);
    VOID MouseEventProc(MOUSE_EVENT_RECORD);
    VOID ResizeEventProc(WINDOW_BUFFER_SIZE_RECORD);
};