#include "stdafx.h"
#include "MouseObject.h"
#include "JustRenderObject.h"

MouseObject::MouseObject(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:GameObject(name,pos,size)
{
	pivot = Pivot::CENTER;
	rc = FloatRect(D3DXVECTOR2(0, 0), size, pivot);
	renderRect = FloatRect(D3DXVECTOR2(0, 0), size, pivot);
	picked = nullptr;
}


MouseObject::~MouseObject()
{
}

void MouseObject::Init()
{
	Super::Init();
}

void MouseObject::Release()
{
	Super::Release();
}

void MouseObject::Update(float tick)
{
	Super::Update(tick);
	transform.SetPos(CAMERA->GetMousePos());

	if (KeyCode->Down(VK_ESCAPE))
		picked = nullptr;


	if (KeyCode->Press(VK_CONTROL) && Mouse::Get()->Down(0))
	{
		if (picked != nullptr) return;
		vector<GameObject*> vec = _ObjectPool->GetObjectAsName("JustRenderObject");
		for (int i = 0; i < (int)vec.size(); i++)
		{
			if (Math::IsAABBInAABB(vec[i]->GetCollider(), this->GetCollider()))
			{
				picked = vec[i];
				break;
			}
		}

	}
}

void MouseObject::Render()
{
	Super::Render();
}

void MouseObject::OnCollisionEnter(GameObject * other)
{
}

void MouseObject::OnCollisionStay(GameObject * other)
{
	if (other->Name() == "BackGround")return;
	if (KeyCode->Press(VK_CONTROL) && Mouse::Get()->Down(0))
	{
		picked = other;
	}
}

void MouseObject::OnCollisionExit(GameObject * other)
{
}
