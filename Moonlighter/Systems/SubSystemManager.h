#pragma once

class LightingSystem;
class BulletSystem;
class GameData;
class SubSystemManager
{
	SingletonHeader(SubSystemManager)
public:

	LightingSystem* GetLightingSubSystem();
	BulletSystem* GetBulletSubSystem();
	GameData* GetGameData();

	void Init();

private:
	LightingSystem* light;
	BulletSystem* bullet;
	GameData* gamedata;
};

#define _GameData SubSystemManager::Get()->GetGameData()
#define _LightSystem SubSystemManager::Get()->GetLightingSubSystem()
#define _BulletSystem SubSystemManager::Get()->GetBulletSubSystem()