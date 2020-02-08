#include "stdafx.h"
#include "SceneMapTool.h"

#include "./Object/Player.h"

SceneMapTool::SceneMapTool()
{
}


SceneMapTool::~SceneMapTool()
{
}

void SceneMapTool::Init()
{
	_ImageManager->AddFrameTexture("Player", ResourcePath + L"Player/will_dungeon.png", 10, 13);

	_ObjectPool->CreateObject<Player>("", D3DXVECTOR2(100, 100), D3DXVECTOR2(100, 100));

}

void SceneMapTool::ImguiRender()
{
	SceneBase::ImguiRender();


}
