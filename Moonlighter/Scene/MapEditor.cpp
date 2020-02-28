#include "stdafx.h"
#include "MapEditor.h"
#include "./Object/MouseObject.h"
#include "./Object/Unit/Player.h"
#include "./Object/StaticObjectBase.h"
#include "./Object/Unit/Slime.h"

#include "./Object/Unit/MiniBoss.h"
#include "./Object/Unit/Golem.h"
#include "./Object/BackGround.h"
#include "./Object/BackGround.h"

#include "ObjectLoader.h"

MapEditor::MapEditor()
{
	items.push_back("MiniBoss");
	items.push_back("Golem");
	items.push_back("Slime");
	items.push_back("Light");

	items.push_back("StaticObjectBase");
	current_item = -1;
	animator = "";
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
	GameObject* object = _ObjectPool->CreateObject<Player>("Player", D3DXVECTOR2(200,200), D3DXVECTOR2(15, 15));
	object->SetRenderSize(D3DXVECTOR2(70, 70), Pivot::CENTER);
	object->LoadAnimator(L"");

	backGround = _ObjectPool->CreateObject<BackGround>("BackGround", D3DXVECTOR2(0, 0), D3DXVECTOR2(WinSizeX, WinSizeY));

	_ObjectPool->SetUpdate(false);
	CAMERA->ModeFreeCamera();

}

void MapEditor::Update(float tick)
{
	mouse->Update(tick);
	SceneBase::Update(tick);
	
	if (KeyCode->Press(VK_CONTROL))
	{
		current_item = -1;

	}
	if (KeyCode->Down('1'))
	{

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



	if (Mouse::Get()->Down(0) && -1 != current_item)
	{
		ObjectLoader load;
		load.LoadObject(items[current_item], CAMERA->GetMousePos(), D3DXVECTOR2(),D3DXVECTOR2(), String::StringToWString(animator), D3DXVECTOR2(0,0), true);
	}
}

void MapEditor::ImguiRender()
{
	SceneBase::ImguiRender();

	static bool bOpen = true;
	ImGui::Begin("ObjectProp", &bOpen);
	

	ImGuiInputTextFlags input_flag = ImGuiInputTextFlags_EnterReturnsTrue;

	for (int i = 0;i < (int)items.size();i++)
	{
		if (ImGui::Selectable(items[i].c_str(), current_item == i))
			current_item = i;
	}

	static char buff[256] = "";
	if (ImGui::InputText("Anim", buff, 256, input_flag))
	{
		animator = buff;
	}


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
		FloatRect colArea = picked->GetColliderArea();
		D3DXVECTOR2 colPos = { (colArea.right + colArea.left)*0.5f, (colArea.top + colArea.bottom)*0.5f };
		D3DXVECTOR2 renPos = { (renderSize.right + renderSize.left)*0.5f, (renderSize.top + renderSize.bottom)*0.5f };
		D3DXVECTOR2 offset = renPos - colPos;

		if (ImGui::InputFloat2("Render Offset", (float*)&offset.x, "%.1f", input_flag))
		{
			picked->SetRenderSize(render, Pivot::CENTER, offset);
		}




		if (picked->Name() == "StaticObjectBase")
		{
			if (ImGui::Button("Set Animator", ImVec2(100, 20)))
			{
				Path::OpenFileDialog(L"", Path::AnimationFilter, ResourcePath + L"Animator", [&](wstring file) {
					picked->LoadAnimator(file);
				});
			}

		}


	}


	if (ImGui::Button("Set BackGround", ImVec2(130, 30)))
	{
		Path::OpenFileDialog(L"", Path::AnimationFilter, ResourcePath + L"Animator", [&](wstring file) {
			backGround->LoadAnimator(file);
		});
	}
	FloatRect renderSize = backGround->GetRenderArea();
	D3DXVECTOR2 render = { renderSize.right - renderSize.left,renderSize.bottom - renderSize.top };

	if (ImGui::InputFloat2("BackGround Size", (float*)&render.x, "%.1f", input_flag)) 
	{
		backGround->SetRenderSize(render, Pivot::LEFT_TOP);
	}

	if (ImGui::Button("Save", ImVec2(60, 30)))
	{
	
		Path::SaveFileDialog(L"", L"", ResourcePath + L"Stage/", [&](wstring file) {
			ObjectSave s;
			s.Save(file);
		});
	}ImGui::SameLine();
	if (ImGui::Button("Load", ImVec2(60, 30)))
	{

		Path::OpenFileDialog(L"", L"", ResourcePath + L"Stage/", [&](wstring file) {
			ObjectLoader load;
			load.LoadMap(file);
		});
	}


	ImGui::End();



}

