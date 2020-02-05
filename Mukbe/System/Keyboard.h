#pragma once

#define MAX_INPUT_KEY 255
#define MAX_INPUT_MOUSE 8

class Keyboard
{
	SingletonHeader(Keyboard)
public:
	void Update();

	bool Down(DWORD key) 
	{
		return keyMap[key] == KEY_INPUT_STATUS_DOWN;
	}
	bool Up(DWORD key) 
	{
		return keyMap[key] == KEY_INPUT_STATUS_UP; 
	}
	bool Press(DWORD key)
	{ 
		return keyMap[key] == KEY_INPUT_STATUS_PRESS; 
	}

private:
	BYTE keyState[MAX_INPUT_KEY];
	BYTE keyOldState[MAX_INPUT_KEY];
	BYTE keyMap[MAX_INPUT_KEY];

	enum
	{
		KEY_INPUT_STATUS_NONE = 0,
		KEY_INPUT_STATUS_DOWN,
		KEY_INPUT_STATUS_UP,
		KEY_INPUT_STATUS_PRESS,
	};
};