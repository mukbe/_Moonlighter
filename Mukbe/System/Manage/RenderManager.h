#pragma once

//레이어 정렬, 패스에 잘 넣어주기
class RenderManager
{
	friend class SceneBase;
public:
	enum class Layer : short
	{
		BackGround = 0 , Terrain, GameText, Object, Light, UI, UIText, Imgui,
	};

	void Request(class GameObject*const obj, const Layer& layer);
	void Remove(class GameObject*const obj, const Layer& layer);
	void Remove(class GameObject*const obj);
		

	

private:
	using MapIter = unordered_map<Layer, vector<class GameObject*>>::iterator;
	using VecIter = vector<class GameObject*>::iterator;
	unordered_map<Layer, vector<class GameObject*>> renderList;

	RenderManager();
	~RenderManager();

	void Render();

	void ObjectRender();
	void LightRender();
	void UIRender();
	void ImguiRender();
};

