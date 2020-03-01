#pragma once

class SceneManager
{
	SingletonHeader(SceneManager)
	friend class Program;

public:
	void Release();
	void Update(float tick);

	void AddScene(string name, SceneBase* node);
	void PopScene(string name);
	void ChangeScene(string name, bool useFade = false);

	SceneBase* GetNowScene();

private:
	SceneBase* FindScene(string name);

	using MapIter = unordered_map<string, SceneBase*>::iterator;
	unordered_map<string, SceneBase*> scenes;

	SceneBase* nowScene;
	SceneBase* changeScene;

};

#define _SceneManager SceneManager::Get()
#define _GameWorld SceneManager::Get()->GetNowScene()
#define _MessagePool SceneManager::Get()->GetNowScene()->GetMessagePool()
#define _ObjectPool SceneManager::Get()->GetNowScene()->GetObjectPool()
#define _RenderPool SceneManager::Get()->GetNowScene()->GetRenderPool()
#define _TileMap SceneManager::Get()->GetNowScene()->GetTileManager()
