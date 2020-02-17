#include "Mukbe.h"
#include "SceneBase.h"

bool SceneBase::DebugMode = false;

SceneBase::SceneBase()
	: messageManager(new MessageManager), objectManager(new ObjectManager), renderManager(new RenderManager)
	, mapTool(new MapTool)
{
	
}

SceneBase::~SceneBase()
{
	//Release();
	SafeDelete(messageManager);
	SafeDelete(objectManager);
	SafeDelete(renderManager);
	SafeDelete(mapTool);

}

void SceneBase::Init()
{
}

void SceneBase::Release()
{
	messageManager->RemoveAllMessage();
	mapTool->Release();
}

void SceneBase::Update(float tick)
{
	messageManager->Update(tick);
	objectManager->Update(tick);
	mapTool->Update();
}

void SceneBase::ObjectRender()
{
	renderManager->ObjectRender();
}

void SceneBase::LightRender()
{
	renderManager->LightRender();
}

void SceneBase::UIRender()
{
	renderManager->UIRender();
}

void SceneBase::ImguiRender()
{
	renderManager->ImguiRender();
	mapTool->ImguiRender();
}


