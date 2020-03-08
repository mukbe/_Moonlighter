#include "stdafx.h"
#include "GameData.h"
#include "./Object/Unit/Unit.h"


SingletonCpp(GameData)

GameData::GameData()
{
	playerBar = nullptr;
	bossBar = nullptr;
	bPlayerBarRender = false;
	bBossBarRender = false;
	potionCount = 3;

	_ImageManager->AddTexture("Potion", ResourcePath + L"UI/UI_Potion.png");
	potionTex = _ImageManager->FindTexture("Potion");
	_ImageManager->AddTexture("heart", ResourcePath + L"UI/heart.png");
	heartTex = _ImageManager->FindTexture("heart");
	_ImageManager->AddTexture("UI_Bag", ResourcePath + L"UI/UI_Bag.png");
	bagTex = _ImageManager->FindTexture("UI_Bag");

	_ImageManager->AddTexture("Inventory", ResourcePath + L"UI/Inventory.png");
	invenTex = _ImageManager->FindTexture("Inventory");


	itemTex = _ImageManager->FindTexture("Items");

	bShowInve = false;
	
}


GameData::~GameData()
{
}

void GameData::ImguiRender()
{
}

void GameData::Update()
{
	if (bossBar)
		bossBar->Update();
	if (playerBar)
		playerBar->Update();

	if (KeyCode->Down('I'))
		bShowInve = !bShowInve;

}

void GameData::Render()
{
	p2DRenderer->SetCamera(false);

	if (bossBar && bBossBarRender)
		bossBar->Render(nullptr);
	if (playerBar && bPlayerBarRender)
	{
		playerBar->Render(nullptr);

		potionTex->Render(FloatRect(D3DXVECTOR2(WinSizeX - 100, 50), 60, 62, Pivot::CENTER), nullptr);
		wstring str = to_wstring(potionCount);
		p2DRenderer->DrawText2D(FloatRect(D3DXVECTOR2(WinSizeX - 60, 60), 20, 20, Pivot::CENTER), str, D3DXCOLOR(1, 1, 1, 1));
		heartTex->Render(FloatRect(D3DXVECTOR2( WinSizeX*0.2f-130, WinSizeY*0.05f), 48,48, Pivot::CENTER), nullptr);
		
		bagTex->Render(FloatRect(D3DXVECTOR2(WinSizeX - 100, 150), 99,98, Pivot::CENTER), nullptr);

	}
	if (invenTex && bShowInve)
	{
		invenTex->Render(FloatRect(D3DXVECTOR2(0, 0), WinSizeX, WinSizeY, Pivot::LEFT_TOP), nullptr);

		D3DXVECTOR2 startPos = D3DXVECTOR2(160, 270);
		D3DXVECTOR2 offset = D3DXVECTOR2(110, 120);
		for (int i = 0; i < (int)items.size(); i++)
		{
			POINT index = items[i].first;
			D3DXVECTOR2 pos = startPos + D3DXVECTOR2(offset.x * (i % 5), offset.y * (int)(i / 5));
			itemTex->FrameRender(FloatRect( pos, 70, Pivot::LEFT_TOP), nullptr,index.x,index.y);
			wstring str = to_wstring(items[i].second);
			p2DRenderer->DrawText2D(FloatRect(pos + D3DXVECTOR2(65,65), 20, 20, Pivot::CENTER), str, D3DXCOLOR(0, 0, 0, 1));

		}

	}


}

void GameData::BossProgressBarInit(Unit * unit)
{
	if (bossBar)
		return;

	bossBar = new ProgressBar;
	bossBar->Init(unit->GetHpMax(), FloatRect(D3DXVECTOR2(WinSizeX*0.5f, WinSizeY*0.8f), WinSizeX*0.6f, 20.f, Pivot::CENTER), 10.f, true);
	float hp = unit->GetHp();

}

void GameData::SetBossHp(float hp)
{
	if (bossBar)
		bossBar->SetCurrentValue(hp);
}

void GameData::PlayerProgressBarInit(Unit * unit)
{
	if (playerBar)
		return;

	playerBar = new ProgressBar;
	playerBar->Init(unit->GetHpMax(), FloatRect(D3DXVECTOR2(WinSizeX*0.2f, WinSizeY*0.05f), 200, 20.f, Pivot::CENTER), 10.f, true);
	playerHp = unit->GetHp();


}

void GameData::SetHp(float hp)
{
	if (playerBar)
	{
		playerBar->SetCurrentValue(hp);
		playerHp = hp;
	}
}

void GameData::Potion()
{
	if (potionCount > 0)
	{
		potionCount--;
		playerHp += 120.f;
		if (playerHp > 200.f)
			playerHp = 200.f;

		playerBar->SetCurrentValue(playerHp);

	}
}

void GameData::RenderOff()
{
	bBossBarRender = bPlayerBarRender = false;
}

void GameData::AddItem(POINT index)
{
	bool bCheck = false;
	for (int i = 0; i < (int)items.size(); i++)
	{
		POINT key = items[i].first;
		if (key.x == index.x &&
			key.y == index.y)
		{
			bCheck = true;
			items[i].second++;
		}
	}

	if (bCheck == false)
	{
		items.push_back(make_pair(index, 1));
	}
}
