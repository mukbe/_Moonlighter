#pragma once

class Player;
class SceneMapTool : public SceneBase
{
public:
	SceneMapTool();
	virtual~SceneMapTool();
	
	virtual void Init();
	virtual void OnceInit();
	void Load();

	virtual void ImguiRender();
private:
	Player* player;
};

