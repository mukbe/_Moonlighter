#include "Mukbe.h"
#include "SceneBase.h"

bool SceneBase::DebugMode = false;

SceneBase::SceneBase()
	: messageManager(new MessageManager), objectManager(new ObjectManager), renderManager(new RenderManager), bFirstInit(true)
{
	
}

SceneBase::~SceneBase()
{
	//Release();
	SafeDelete(messageManager);
	SafeDelete(objectManager);
	SafeDelete(renderManager);

}

void SceneBase::Init()
{
}

void SceneBase::OnceInit()
{
	bFirstInit = false;
}

void SceneBase::Release()
{
	messageManager->RemoveAllMessage();
}

void SceneBase::Update(float tick)
{
	messageManager->Update(tick);
	objectManager->Update(tick);
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
}


