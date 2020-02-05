#include "Mukbe.h"
#include "SceneManager.h"

SingletonCpp(SceneManager)

SceneManager::SceneManager()
	:nowScene(nullptr)
{
}

SceneManager::~SceneManager()
{
	MapIter Iter = scenes.begin();
	for (; Iter != scenes.end();)
	{
		SceneBase* node = Iter->second;
		node->Release();
		SafeDelete(node);

		Iter = scenes.erase(Iter);
	}
}

void SceneManager::Update(float tick)
{
	if (nowScene != nullptr)
		nowScene->Update(tick);

}

void SceneManager::AddScene(string name, SceneBase * node)
{
	scenes.insert(make_pair(name, node));
}

void SceneManager::PopScene(string name)
{
	MapIter Iter = scenes.find(name);
	if (Iter != scenes.end())
	{
		SceneBase* node = Iter->second;
		node->Release();
		SafeDelete(node);

		scenes.erase(Iter);
	}
}

void SceneManager::ChangeScene(string name)
{
	if (nowScene != nullptr)
	{
		nowScene->Release();
		SafeDelete(nowScene);
	}

	SceneBase* scene = FindScene(name);
	nowScene = scene;
	scene->Init();
}

SceneBase * SceneManager::GetNowScene()
{
	Log_ErrorAssert(nowScene != nullptr);
	return nowScene;
}

SceneBase * SceneManager::FindScene(string name)
{
	MapIter Iter = scenes.find(name);

	if (Iter != scenes.end())
		return Iter->second;

	
	LOG->Warning(__FILE__, __LINE__, "no scene");
	return nullptr;
}
