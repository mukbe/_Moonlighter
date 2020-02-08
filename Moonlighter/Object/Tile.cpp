#include "stdafx.h"
#include "Tile.h"



Tile::Tile(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:GameObject(name, pos, size)
{
}

Tile::~Tile()
{
}

void Tile::Init()
{
	SetTileMapTexture();
	_RenderPool->Request(this, RenderManager::Layer::Terrain);
}

void Tile::Release()
{
	_RenderPool->Remove(this, RenderManager::Layer::Terrain);
}

void Tile::Update(float tick)
{
}

void Tile::Render()
{
}

void Tile::SetTileMapTexture(string key)
{
	if (key.empty())
		imageKey = "DefaultTileMap";
	else
		imageKey = key;

	texture = _ImageManager->FindTexture(imageKey);
}
