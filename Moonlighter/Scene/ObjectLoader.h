#pragma once

class ObjectLoader
{
public:
	ObjectLoader();
	~ObjectLoader();

	void Setting();
	GameObject* LoadObject(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXVECTOR2 render, wstring animator, D3DXVECTOR2 offset = D3DXVECTOR2(0.f, 0.f), bool bDefault = true);
	void LoadMap(wstring file);
private:

	unordered_map<string, function<GameObject*(D3DXVECTOR2,D3DXVECTOR2, D3DXVECTOR2, wstring, D3DXVECTOR2, bool)>>	load;

	//임시로 객체의 위치를 저장할 무언가를 놓으면 될듯
};


class ObjectSave
{
public:
	ObjectSave() {}
	~ObjectSave() {}
	
	void Save(wstring file);
};