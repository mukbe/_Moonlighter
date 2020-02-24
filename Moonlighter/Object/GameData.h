#pragma once

class GameData : public GameObject
{
	ClassInherited(GameObject)
	RequestRender(Layer_Imgui)
	friend class ObjectManager;

public:
	virtual void ImguiRender();

private:
	GameData(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	virtual~GameData();

};

