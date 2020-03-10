#pragma once

class GameData
{
	SingletonHeader(GameData)
public:
	void ImguiRender();
	void Update();
	void Render();

	void BossProgressBarInit(class Unit* unit);
	void SetBossHp(float hp);

	void PlayerProgressBarInit(class Unit* unit);
	void SetHp(float hp);
	
	void Potion();

	
	void RenderOff();
	float GetPlayerHp()
	{
		return playerHp;
	}
	bool bPlayerBarRender;
	bool bBossBarRender;

	void AddItem(POINT index);
	vector<pair<POINT, int>> GetItems()
	{
		return items;
	}
private:
	float playerHp;
	vector<pair<POINT, int>> items;

	ProgressBar* playerBar;

	class Unit* boss;
	ProgressBar* bossBar;

	int potionCount;
	shared_ptr<Texture> potionTex;
	shared_ptr<Texture> heartTex;
	shared_ptr<Texture> invenTex;
	shared_ptr<Texture> bagTex;
	shared_ptr<Texture> itemTex;

	bool bShowInve;
};

