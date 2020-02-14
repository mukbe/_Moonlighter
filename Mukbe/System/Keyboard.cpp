#include "Mukbe.h"
#include "Keyboard.h"

SingletonCpp(Keyboard)

void Keyboard::Update()
{
	memcpy(keyOldState, keyState, sizeof(keyOldState));

	ZeroMemory(keyState, sizeof(keyState));
	ZeroMemory(keyMap, sizeof(keyMap));


	GetKeyboardState(keyState);

	for (DWORD i = 0; i < MAX_INPUT_KEY; i++)
	{
		BYTE key = keyState[i] & 0x80;
		keyState[i] = key ? 1 : 0;

		int oldState = keyOldState[i];
		int state = keyState[i];

		if (oldState == 0 && state == 1)
			keyMap[i] = KEY_INPUT_STATUS_DOWN; //이전 0, 현재 1 - KeyDown
		else if (oldState == 1 && state == 0)
			keyMap[i] = KEY_INPUT_STATUS_UP; //이전 1, 현재 0 - KeyUp
		else if (oldState == 1 && state == 1)
			keyMap[i] = KEY_INPUT_STATUS_PRESS; //이전 1, 현재 1 - KeyPress
		else
			keyMap[i] = KEY_INPUT_STATUS_NONE;
	}
	
	UpdateAxisData();
}

Keyboard::Keyboard()
{
	ZeroMemory(keyState, sizeof(keyState));
	ZeroMemory(keyOldState, sizeof(keyOldState));
	ZeroMemory(keyMap, sizeof(keyMap));
	ZeroMemory(&value, sizeof(value));

	vertical[0] = VK_UP;
	vertical[1] = VK_DOWN;
	horizon[0] = VK_LEFT;
	horizon[1] = VK_RIGHT;
}

Keyboard::~Keyboard()
{

}

void Keyboard::UpdateAxisData()
{
	delta = 0.01f;

	float sign = 1.f;
	float valueSign = 1.f;
	if (keyMap[vertical[0]] == KEY_INPUT_STATUS_PRESS)
	{
		sign = -1.f;
		absValue.y > 0 ? valueSign : valueSign = -1.f;
		absValue.y = Math::Abs(absValue.y);
		valueSign * sign < 0.f ? absValue.y -= delta : absValue.y += delta;
		absValue.y *= valueSign;
		absValue.y < -1.f ? absValue.y = -1.f : absValue.y;
	}
	else if (keyMap[vertical[1]] == KEY_INPUT_STATUS_PRESS)
	{
		sign = 1.f;
		absValue.y > 0 ? valueSign : valueSign = -1.f;
		absValue.y = Math::Abs(absValue.y);
		valueSign * sign < 0.f ? absValue.y -= delta : absValue.y += delta;
		absValue.y *= valueSign;
		absValue.y > 1.f ? absValue.y = 1.f : absValue.y;
	}
	else if (keyMap[vertical[0]] == KEY_INPUT_STATUS_NONE &&
		keyMap[vertical[1]] == KEY_INPUT_STATUS_NONE)
	{
		absValue.y > 0 ? valueSign : valueSign = -1.f;
		absValue.y = Math::Abs(absValue.y);
		absValue.y -= delta;
		absValue.y < 0.f ? absValue.y = 0.f : absValue.y;
		absValue.y *= valueSign;

	}


}
