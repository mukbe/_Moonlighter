#include "stdafx.h"
#include "MapEditor.h"
#include "./Object/MouseObject.h"
#include "./Object/Unit/Player.h"
#include "./Object/StaticObjectBase.h"
#include "./Object/Unit/Slime.h"

#include "./Object/Unit/MiniBoss.h"
#include "./Object/Unit/Golem.h"
#include "./Object/BackGround.h"


MapEditor::MapEditor()
{

}


MapEditor::~MapEditor()
{
}

void MapEditor::Init()
{
	SceneBase::Init();
}

void MapEditor::OnceInit()
{
	mouse = _ObjectPool->CreateObject<MouseObject>("Mouse", CAMERA->GetMousePos(), D3DXVECTOR2(2, 2));
}

void MapEditor::Update(float tick)
{
	SceneBase::Update(tick);
	if (KeyCode->Press(VK_CONTROL))
	{
		current = Object_None;


	}
	if (KeyCode->Down('1'))
	{
		current = Object_StaticObjectBase;

	}

	GameObject* picked = mouse->GetPicked();
	if (picked != nullptr)
	{
		if (Mouse::Get()->Down(0))
		{
			oldPickPos = CAMERA->GetMousePos();
		}
		if (Mouse::Get()->Press(0))
		{
			D3DXVECTOR2 delta = CAMERA->GetMousePos() - oldPickPos;

			picked->Transform().SetPos(picked->Transform().GetPos() + delta);
			oldPickPos = CAMERA->GetMousePos();
		}
	}



	if (Mouse::Get()->Down(0) && Object_None != current)
	{
		CreateObject(current);
	}
}

void MapEditor::ImguiRender()
{
	SceneBase::ImguiRender();

	static bool bOpen = true;
	ImGui::Begin("ObjectProp", &bOpen);
	

	ImGuiInputTextFlags input_flag = ImGuiInputTextFlags_EnterReturnsTrue;


	GameObject* picked = mouse->GetPicked();
	if (picked != nullptr)
	{
		FloatRect rc = picked->GetCollider();
		D3DXVECTOR2 size = { rc.right - rc.left,rc.bottom - rc.top };
		if (ImGui::InputFloat2("Collision Size", (float*)&size.x, "%.1f", input_flag))
		{
			picked->SetCollisionSize(size);
		}
		FloatRect renderSize = picked->GetRenderArea();
		D3DXVECTOR2 render = { renderSize.right - renderSize.left,renderSize.bottom - renderSize.top };
		if (ImGui::InputFloat2("Render Size", (float*)&render.x, "%.1f", input_flag))
		{
			picked->SetRenderSize(render, Pivot::CENTER);
		}




	}


	ImGui::End();
}

void MapEditor::CreateObject(ObjectKind val)
{
	switch (current)
	{
	case MapEditor::Object_None:
		break;
	case MapEditor::Object_StaticObjectBase:
		_ObjectPool->CreateObject<StaticObjectBase>("StaticObjectBase", CAMERA->GetMousePos(), D3DXVECTOR2(30, 30));
		break;
	default:
		break;
	}
}
