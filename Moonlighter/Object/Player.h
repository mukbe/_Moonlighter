#pragma once
#include "Unit.h"

class Player : public Unit
{
	ClassInherited(Unit)
	RequestRender(Layer_Object | Layer_Imgui)
public:
	Player(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	virtual ~Player();

	//초기화
	virtual void Init();
	//메모리 해제
	virtual void Release();
	//메인 루틴
	virtual void Update(float tick);

	virtual void Render();
	//imgui debugUI render
	virtual void ImguiRender();


	void CreateAnimation();

private:
};

