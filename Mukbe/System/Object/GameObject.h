#pragma once
#include "../Message/MessageComponent.h"

class Matrix2D;
class GameObject : public MessageComponent
{
	using VertexType = VertexColor;
public:
	explicit GameObject(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	virtual~GameObject();

	//�ʱ�ȭ
	virtual void Init();
	//�޸� ����
	virtual void Release();
	//���� ��ƾ
	virtual void Update(float tick);

	virtual void Render();
	//imgui debugUI render
	virtual void ImguiRender() {}
	



	const string& Name() { return name; }
	Matrix2D& Transform() { return transform; }

	const bool& IsActive() { return bActive; }
	void SetActive(const bool& b) { bActive = b; }
	

	void SetAlpha(const float& a)
	{
		a > 0.f ? (a > 1.f ? alpha = 1.f : alpha = a) : alpha = 0.f;
	}
	const float& GetAlpha() { return alpha; }

	//��ġ���� �޾ƿ�
	FloatRect GetCollider();

	virtual int GetLayer() { return RenderLayer::Layer_None; }
protected:
	string name;
	Matrix2D transform;
	FloatRect rc;
	D3DXVECTOR2 size;

	bool bActive;
	float alpha;
	float lifeTiem;

protected:
	string shaderKey;
	WorldBuffer* worldBuffer;

};

