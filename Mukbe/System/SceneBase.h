#pragma once


class SceneBase 
{
public:
	SceneBase();
	virtual ~SceneBase();

	virtual void Init();
	virtual void Release();
	
	virtual void Update(float tick);


	virtual void ObjectRender();
	virtual void LightRender();
	virtual void UIRender();
	virtual void ImguiRender();




	class MessageManager* GetMessagePool() { return messageManager; }
	class ObjectManager* GetObjectPool() { return objectManager; }
	class RenderManager* GetRenderPool() { return renderManager; }
public:
	static bool DebugMode;
protected:
	class MessageManager* messageManager;
	class ObjectManager* objectManager;
	class RenderManager* renderManager;
};

