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

	void Init();

private:
	LightingSystem* light;
	BulletSystem* bullet;
};

#define _LightSystem SubSystemManager::Get()->GetLightingSubSystem()
#define _BulletSystem SubSystemManager::Get()->GetBulletSubSystem()