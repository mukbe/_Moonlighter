﻿#include "stdafx.h"
#include "./Systems/Window.h"

#include <time.h>


int WINAPI WinMain(HINSTANCE instance, HINSTANCE prevInstance, LPSTR param, int command)
{
	
	D3DDesc desc;
	desc.AppName = L"Moonlighter";
	desc.Instance = instance;
	desc.bFullScreen = false;
	desc.bVsync = false;
	desc.Handle = NULL;
	desc.Width = WinSizeX;
	desc.Height = WinSizeY;
	DxRenderer::SetDesc(desc);

	srand((UINT)time(0));
	
	
	Window* window = new Window();
	WPARAM wParam = window->Run();
	SafeDelete(window);

	return wParam;
}