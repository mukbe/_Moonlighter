#pragma once

class Program;
class Window
{
public:
	Window();
	~Window();

	WPARAM Run();
	static bool bUseImguiUI;
private:
	static LRESULT CALLBACK WndProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);

	static Program* program;

	void CreateManagers();
	void DeletaManagers();
};