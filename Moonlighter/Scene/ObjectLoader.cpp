#include "stdafx.h"
#include "ObjectLoader.h"

#include "./Object/Unit/Player.h"
#include "./Object/StaticObjectBase.h"
#include "./Object/Unit/Slime.h"

#include "./Object/Unit/MiniBoss.h"
#include "./Object/Unit/Golem.h"
#include "./Object/BackGround.h"
#include "./Object/JustRenderObject.h"



ObjectLoader::ObjectLoader()
{
	Setting();
}


ObjectLoader::~ObjectLoader()
{
}


GameObject * ObjectLoader::LoadObject(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXVECTOR2 render, wstring animator, D3DXVECTOR2 offset, bool bDefault)
{
	unordered_map<string, function< GameObject*(D3DXVECTOR2, D3DXVECTOR2, D3DXVECTOR2, wstring, D3DXVECTOR2,bool)>>::iterator Iter = load.find(name);
	if (Iter != load.end())
	{
		wstring path;
		if(animator != L"")
			path = ResourcePath + L"Animator/" + animator + L".anim";

		return Iter->second(pos, size, render, path, offset, bDefault);
	}

	return nullptr;
}

void ObjectLoader::LoadMap(wstring file)
{
	BinaryReader r;
	r.Open(file);
	{
		int count = r.Int();
		for (int i = 0;i < count; i++)
		{
			string name = r.String();
			D3DXVECTOR2 pos = r.Vector2();
			D3DXVECTOR2 size = r.Vector2();
			D3DXVECTOR2 render = r.Vector2();
			D3DXVECTOR2 offset = r.Vector2();
			string animator = r.String();

			GameObject* object = LoadObject(name, pos, size, render, String::StringToWString(animator), offset, false);


		}
		

	}
	r.Close();
}

void ObjectLoader::Setting()
{
	load.insert(make_pair("Player", [](D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXVECTOR2 render, wstring animator, D3DXVECTOR2 offset, bool bDefault)->GameObject* {
		GameObject* object = _ObjectPool->FindObject<Player>("Player");
		object->LoadAnimator(animator);
		if (bDefault == false)
		{
			object->Transform().SetPos(pos);
			object->SetRenderSize(render, Pivot::CENTER, offset);
			object->SetCollisionSize(size);
		}
		return object;
	}));

	load.insert(make_pair("StaticObjectBase", [](D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXVECTOR2 render, wstring animator, D3DXVECTOR2 offset, bool bDefault)->GameObject* {
		GameObject* object = _ObjectPool->CreateObject<StaticObjectBase>("StaticObjectBase", pos, D3DXVECTOR2(15, 15));
		object->SetRenderSize(D3DXVECTOR2(70, 70), Pivot::CENTER, offset);
		object->LoadAnimator(animator);
		if (bDefault == false)
		{
			object->SetRenderSize(render, Pivot::CENTER, offset);
			object->SetCollisionSize(size);
		}
		//object->SetPivot(Pivot::BOTTOM);
		//item event...
		return object;
	}));

	load.insert(make_pair("Slime", [](D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXVECTOR2 render, wstring animator, D3DXVECTOR2 offset, bool bDefault)->GameObject* {
		GameObject* object = _ObjectPool->CreateObject<Slime>("Slime", pos, D3DXVECTOR2(15, 15));
		object->SetRenderSize(D3DXVECTOR2(25, 25), Pivot::CENTER, offset);
		object->LoadAnimator(animator);
		if (bDefault == false)
		{
			object->SetRenderSize(render, Pivot::CENTER, offset);
			object->SetCollisionSize(size);
		}
		return object;
	}));
	                                                                                                                     
	load.insert(make_pair("MiniBoss", [](D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXVECTOR2 render, wstring animator, D3DXVECTOR2 offset, bool bDefault)->GameObject* {
		GameObject* object = _ObjectPool->CreateObject<MiniBoss>("MiniBoss", pos, D3DXVECTOR2(90, 90));
		object->SetRenderSize(D3DXVECTOR2(250, 250), Pivot::CENTER, offset);
		object->LoadAnimator(animator);
		if (bDefault == false)
		{
			object->SetRenderSize(render, Pivot::CENTER, offset);
			object->SetCollisionSize(size);
		}
		return object;
	}));
	load.insert(make_pair("Golem", [](D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXVECTOR2 render, wstring animator, D3DXVECTOR2 offset, bool bDefault)->GameObject* {
		GameObject* object = _ObjectPool->CreateObject<Golem>("Golem", pos, D3DXVECTOR2(50, 65));
		object->SetRenderSize(D3DXVECTOR2(120, 135), Pivot::CENTER, offset);
		object->LoadAnimator(animator);
		if (bDefault == false)
		{
			object->SetRenderSize(render, Pivot::CENTER, offset);
			object->SetCollisionSize(size);
		}
		return object;
	}));
	load.insert(make_pair("BackGround", [](D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXVECTOR2 render, wstring animator, D3DXVECTOR2 offset, bool bDefault)->GameObject* {
		GameObject* object = _ObjectPool->FindObject<BackGround>("BackGround");
		object->Transform().SetPos(D3DXVECTOR2(0.f,0.f));

		object->SetRenderSize(D3DXVECTOR2(WinSizeX, WinSizeY), Pivot::LEFT_TOP);
		object->LoadAnimator(animator);
		//object->LoadAnimator(ResourcePath +L"Animator/Lobby.anim");
		if (bDefault == false)
		{
			object->SetRenderSize(render, Pivot::LEFT_TOP);
			object->SetCollisionSize(size);
		}
		return object;
	}));

	
	load.insert(make_pair("JustRenderObject", [](D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXVECTOR2 render, wstring animator, D3DXVECTOR2 offset, bool bDefault)->GameObject* {
		GameObject* object = _ObjectPool->CreateObject<JustRenderObject>("JustRenderObject", pos, D3DXVECTOR2(25, 25));

		object->SetRenderSize(D3DXVECTOR2(70, 70), Pivot::CENTER, offset);
		object->LoadAnimator(animator);
		if (bDefault == false)
		{
			object->SetRenderSize(render, Pivot::CENTER, offset);
			object->SetCollisionSize(size);
		}

		return object;
	}));
	load.insert(make_pair("Light", [](D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXVECTOR2 render, wstring animator, D3DXVECTOR2 offset, bool bDefault)->GameObject* {


		if (bDefault == false)
		{
			_LightSystem->RegisterLight(pos, D3DXCOLOR(1, 1, 1, 1), size.x);

		}
		else
		{
			_LightSystem->RegisterLight(pos, D3DXCOLOR(1, 1, 1, 1), 100.f);
		}
		return nullptr;
	}));




}

void ObjectSave::Save(wstring file)
{

	BinaryWriter w;
	w.Open(file);
	{
		int check = 0;
		vector<GameObject*> objects = _ObjectPool->GetArray();
		for (int i = 0;i < (int)objects.size(); i++)
		{
			string name = objects[i]->Name();
			if (String::Contain(name, "Bullet") ||
				String::Contain(name, "Light") ||
				String::Contain(name, "Mouse") ||
				String::Contain(name, "GameData"))
			{
				objects.erase(objects.begin() + i);
				i--;
			}
			//if (name == "BackGround")
			//{
			//	if (check == 2)continue;

			//	check++;
			//	objects.erase(objects.begin() + i);
			//	i--;
			//}

		}

		w.Int((int)objects.size());
		for (int i = 0;i < (int)objects.size(); i++)
		{
			GameObject* object = objects[i];
			w.String(object->Name());
			w.Vector2(object->Transform().GetPos());
			FloatRect rc = object->GetCollider();
			w.Vector2(D3DXVECTOR2(rc.right - rc.left, rc.bottom - rc.top));
			FloatRect area = object->GetRenderArea();
			w.Vector2(D3DXVECTOR2(area.right - area.left, area.bottom - area.top));


			FloatRect colArea = object->GetColliderArea();
			D3DXVECTOR2 colPos = { (colArea.right + colArea.left)*0.5f, (colArea.top + colArea.bottom)*0.5f };
			D3DXVECTOR2 renPos = { (area.right + area.left)*0.5f, (area.top + area.bottom)*0.5f };
			D3DXVECTOR2 offset = renPos - colPos;

			w.Vector2(offset);

			Animator* anim = object->GetAnimator();
			if (anim)
				w.String(anim->Name());
			else
				w.String("");
		}


	}
	w.Close();

}
