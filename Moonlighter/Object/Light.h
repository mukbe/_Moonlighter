#pragma once


class LightingSystem;
class Light : public GameObject
{
	ClassInherited(GameObject)
	friend class LightingSystem;
public:
	Light(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	virtual~Light();

	//초기화
	virtual void Init();
	//메모리 해제
	virtual void Release();
	//메인 루틴
	virtual void Update(float tick);

	virtual void Render();
	//imgui debugUI render
	virtual void ImguiRender();

	void SetRange(float val);
private:
	float range;
	D3DXCOLOR color;

	LightingSystem* lightingSystem;

	int id_Light;
	LightSystemBuffer* lightSystemBuffer;
	D3DXVECTOR2 velocity;

};

