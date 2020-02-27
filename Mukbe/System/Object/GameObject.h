#pragma once
#include "../Message/MessageComponent.h"

class Matrix2D;
class GameObject : public MessageComponent
{
	using VertexType = VertexColor;
public:
	explicit GameObject(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	virtual~GameObject();

	//초기화
	virtual void Init();
	//메모리 해제
	virtual void Release();
	//메인 루틴
	virtual void Update(float tick);

	virtual void Render();
	//imgui debugUI render
	virtual void ImguiRender() {}

	virtual void OnCollisionEnter(GameObject* other) { }
	virtual void OnCollisionStay(GameObject* other) { }
	virtual void OnCollisionExit(GameObject* other) { }

	virtual void PlayerInteractions() {}


	const string& Name() { return name; }
	Matrix2D& Transform() { return transform; }

	const bool& IsActive() { return bActive; }
	void SetActive(const bool& b) { bActive = b; }
	

	void SetAlpha(const float& a)
	{
		a > 0.f ? (a > 1.f ? alpha = 1.f : alpha = a) : alpha = 0.f;
	}
	const float& GetAlpha() { return alpha; }

	//위치까지 받아옴
	FloatRect GetCollider();
	FloatRect GetRenderArea() { return renderRect; }
	void SetRenderSize( D3DXVECTOR2 size, Pivot p, D3DXVECTOR2 pos = D3DXVECTOR2(0.f,0.f) );
	void SetCollisionSize(D3DXVECTOR2 size);


	virtual int GetLayer() { return RenderLayer::Layer_None; }
	virtual CollisionType GetCollisionType() { return CollisionType::CollisionType_None; }
	IFFEnum GetIFF() { return iff; }

protected:
	string name;
	Matrix2D transform;
	FloatRect rc;
	FloatRect renderRect;
	D3DXVECTOR2 size;
	Pivot pivot;


	bool bActive;
	float alpha;
	float lifeTime;

	IFFEnum iff;
protected:
	string shaderKey;
	WorldBuffer* worldBuffer;

};

