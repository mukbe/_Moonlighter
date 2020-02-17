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

	void SetVertical(DWORD upKey, DWORD downKey);
	void SetHorizon(DWORD leftKey, DWORD rightKey);
	void SetAxisAmount(float amount) { delta = amount; }
	D3DXVECTOR2 GetData() { return absValue; }
private:
	void UpdateAxisData();

	BYTE keyState[MAX_INPUT_KEY];
	BYTE keyOldState[MAX_INPUT_KEY];
	BYTE keyMap[MAX_INPUT_KEY];
	
	//x => left,right
	//y => up,down
	D3DXVECTOR2 value;
	DWORD vertical[2];
	DWORD horizon[2];
	D3DXVECTOR2 absValue;
	float delta;

	enum
	{
		KEY_INPUT_STATUS_NONE = 0,
		KEY_INPUT_STATUS_DOWN,
		KEY_INPUT_STATUS_UP,
		KEY_INPUT_STATUS_PRESS,
	};
};