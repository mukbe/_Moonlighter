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
	_ObjectPool->CreateObject<Player>("", D3DXVECTOR2(100, 100), D3DXVECTOR2(100, 100));
}
