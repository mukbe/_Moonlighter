#pragma once

class MapEditor : public SceneBase
{

public:
	MapEditor();
	~MapEditor();

	virtual void Init();
	virtual void OnceInit();
	virtual void Update(float tick);
	virtual void ImguiRender();


private:
	class MouseObject* mouse;
	class BackGround* backGround;
	int current_item;
	D3DXVECTOR2 oldPickPos;
	vector<string> items;
	string animator;
};

