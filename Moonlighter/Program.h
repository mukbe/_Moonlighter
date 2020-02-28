#pragma once


class TestScene;
class Program
{
public:
	Program();
	~Program();

	void PreUpdate();
	void Update(float tick);
	void PostUpdate();

	void Render();

	void PostRender();
	void ImguiRender();
	void GameUIRender();

	void ResizeScreen();

	void LoadTexture();
	//void TestFunc();
private:
	bool bGrid;
	D3DXCOLOR gridColor;

	void MakeGrid();
};