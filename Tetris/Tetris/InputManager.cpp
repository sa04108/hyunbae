#include "InputManager.h"

using namespace std;

InputManager::InputManager() : hStdin(GetStdHandle(STD_INPUT_HANDLE)), irInBuf{ {0} }
{
	if (hStdin == INVALID_HANDLE_VALUE) return;
	FlushConsoleInputBuffer(hStdin);
	if (!GetConsoleMode(hStdin, &fdwSaveOldMode)) return;
	if (!SetConsoleMode(hStdin, ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT)) return;
	events.clear();
}

VOID InputManager::ErrorExit(const char* lpszMessage)
{
	Borland::gotoxy(0, 21);
	printf("%80d\r", ' ');
	printf("%s\n", lpszMessage);

	// Restore input mode on exit.

	SetConsoleMode(hStdin, fdwSaveOldMode);

	ExitProcess(0);
}

VOID InputManager::KeyEventProc(KEY_EVENT_RECORD ker)
{
	Borland::gotoxy(0, 21);
	if (ker.bKeyDown)
		wcout << ker.wVirtualKeyCode << " key pressed       ";
	else
		wcout << ker.wVirtualKeyCode << " key released      ";
}

VOID InputManager::MouseEventProc(MOUSE_EVENT_RECORD mer)
{
#ifndef MOUSE_HWHEELED
#define MOUSE_HWHEELED 0x0008
#endif
	Borland::gotoxy(0, 22);
	printf("%80d\r", ' ');

	printf("Mouse event: %d %d      ", mer.dwMousePosition.X, mer.dwMousePosition.Y);

	switch (mer.dwEventFlags)
	{
	case 0:

		if (mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			printf("left button press \n");
		}
		else if (mer.dwButtonState == RIGHTMOST_BUTTON_PRESSED)
		{
			printf("right button press \n");
		}
		else
		{
			printf("button press\n");
		}
		break;
	case DOUBLE_CLICK:
		printf("double click\n");
		break;
	case MOUSE_HWHEELED:
		printf("horizontal mouse wheel\n");
		break;
	case MOUSE_MOVED:
		printf("mouse moved\n");
		break;
	case MOUSE_WHEELED:
		printf("vertical mouse wheel\n");
		break;
	default:
		printf("unknown\n");
		break;
	}
}

bool InputManager::GetKeyDown(WORD ch)
{
	if (events.empty() == true) return false;
	const INPUT_RECORD& in = events.front();
	if (in.EventType != KEY_EVENT) return false;
	if (in.Event.KeyEvent.bKeyDown == TRUE) {
		return in.Event.KeyEvent.wVirtualKeyCode == ch;
	}
	return false;
}

bool InputManager::bufferIsEmpty()
{
	if (events.empty() == true) return true;
	else return false;
}

void InputManager::readInputs()
{
	DWORD cNumRead;
	DWORD nEvents;

	if (!GetNumberOfConsoleInputEvents(hStdin, &nEvents)) return;
	if (nEvents == 0) return;

	nEvents = min(nEvents, 128);
	ReadConsoleInput(
		hStdin,      // input buffer handle 
		irInBuf,     // buffer to read into 
		nEvents,         // size of read buffer 
		&cNumRead); // number of records read

	for (int i = 0; i < (int)cNumRead; i++)
	{
		if (irInBuf[i].EventType == KEY_EVENT)
		{
			if (irInBuf[i].Event.KeyEvent.bKeyDown)
				events.push_back(irInBuf[i]); // 임시로 키 입력을 받을 때에만, 누른 상태일때만 입력 버퍼에 저장하도록함.
		}
	}
}

void InputManager::consumeEvent()
{
	if (bufferIsEmpty()) return;
	events.pop_front();
}

void InputManager::consumeAllEvent()
{
	if (bufferIsEmpty()) return;
	events.clear();
}