#pragma once

class Player;
class SceneMapTool : public SceneBase
{
public:
	SceneMapTool();
	virtual~SceneMapTool();
	
	virtual void Init();
	virtual void ImguiRender();
	virtual void Update(float tick);
private:
	Player* player;
};

