#include "Mukbe.h"
#include "Tile.h"



Tile::Tile(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:GameObject(name, pos, size)
{
	rc = renderRect = FloatRect(pos, size, Pivot::LEFT_TOP);
}

Tile::~Tile()
{
}

void Tile::Init()
{
	Super::Init();
	SetTileMapTexture();
}

void Tile::Release()
{
	Super::Release();
}

void Tile::Update(float tick)
{
	Super::Update(tick);
}

void Tile::Render()
{
	Super::Render();
	if (SceneBase::DebugMode)
		p2DRenderer->FillRectangle(renderRect, &transform, DefaultBrush::gray);
}

void Tile::SetTileMapTexture(string key)
{
	if (key.empty())
		imageKey = "DefaultTileMap";
	else
		imageKey = key;

	texture = _ImageManager->FindTexture(imageKey);
}
