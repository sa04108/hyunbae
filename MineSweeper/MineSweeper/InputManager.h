#pragma once
#include <Windows.h>
#include <iostream>
#include "Scene.h"
#include "Position.h"
using namespace std;

class InputManager {
    HANDLE hStdin;
    DWORD fdwSaveOldMode, cNumRead, fdwMode;
    INPUT_RECORD irInBuf[128];
    Scene scene;

public:
    static int mouseinput;
    static int keyinput;
    static short x, y;

    InputManager();
    void readInputs();

    VOID ErrorExit(const char*);
    VOID KeyEventProc(KEY_EVENT_RECORD);
    VOID MouseEventProc(MOUSE_EVENT_RECORD);
    VOID ResizeEventProc(WINDOW_BUFFER_SIZE_RECORD);
};