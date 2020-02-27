//#include "..\..\..\Moonlighter\Scene\MapTool.h"
#include "Mukbe.h"
#include "MapTool.h"
#include "./System/Object/Tile.h"

D3DXVECTOR2 MapTool::tileSize = { 20, 20 };
D3DXVECTOR2 MapTool::tileMaxIndex = { 5,5 };

D3DXVECTOR2 MapTool::PositionToIndex(D3DXVECTOR2 position)
{
	POINT temp = { (LONG)(position.x / tileSize.x),(LONG)(position.y / tileSize.y) };
	D3DXVECTOR2 index = { (float)temp.x, (float)temp.y };
	return index;
}

D3DXVECTOR2 MapTool::IndexToPosition(D3DXVECTOR2 index)
{
	D3DXVECTOR2 position = { (float)(index.x * tileSize.x),(float)(index.y * tileSize.y) };
	return position;
}

MapTool::MapTool()
{
}


MapTool::~MapTool()
{
}

void MapTool::Init()
{
	for (int y = 0; y < tileMaxIndex.y; y++)
	{
		for (int x = 0; x < tileMaxIndex.x; x++)
		{
			Tile* tile = _ObjectPool->CreateObject<Tile>("Tile", D3DXVECTOR2(x * tileSize.x, tileSize.y * y), tileSize);
			
			tiles.push_back(tile);
		}
	}
}


void MapTool::Release()
{
}

void MapTool::Update()
{
}

void MapTool::Render()
{
}

void MapTool::ImguiRender()
{
}

Tile * MapTool::GetTileAsIndex(D3DXVECTOR2 index)
{
	index.x = Math::Clamp(index.x, 0.f, tileMaxIndex.x);
	index.y = Math::Clamp(index.y, 0.f, tileMaxIndex.y);
	
	return tiles[index.x + index.y * tileMaxIndex.x];
}

Tile * MapTool::GetTileAsPosition(D3DXVECTOR2 position)
{
	D3DXVECTOR2 index = MapTool::PositionToIndex(position);
	
	return GetTileAsIndex(index);
}
