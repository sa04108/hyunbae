#pragma once
#include <iostream>
#include <Windows.h>
#include <deque>

#include "Utils.h"

using namespace std;

class InputManager {

	INPUT_RECORD irInBuf[128];

	HANDLE hStdin;
	DWORD fdwSaveOldMode;

	deque<INPUT_RECORD> events;

	InputManager();

	VOID ErrorExit(const char* lpszMessage);
	VOID KeyEventProc(KEY_EVENT_RECORD ker);
	VOID MouseEventProc(MOUSE_EVENT_RECORD mer);

	static InputManager* instance;

public:
	static InputManager* getInstance() {
		if (instance == nullptr) {
			instance = new InputManager;
		}
		return instance;
	}

	bool GetKeyDown(WORD ch); // return true or false, according to whether front data of deque equals 'ch'
	bool bufferIsEmpty(); // return true or false, according to whether input buffer is empty
	void readInputs(); // wait for input, inputted data would be pushed back of deque input buffer
	void consumeEvent(); // pop a data from front of deque
	void consumeAllEvent(); // pop all data from deque
};