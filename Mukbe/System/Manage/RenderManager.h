#pragma once



//���̾� ����, �н��� �� �־��ֱ�
class RenderManager
{
	friend class SceneBase;
	using Layer = int;
public:

	//void Request(class GameObject*const obj, const RenderLayer& layer);
	//void Remove(class GameObject*const obj, const RenderLayer& layer);
	void Request(class GameObject*const obj, const Layer& mask);
	void Remove(class GameObject*const obj, const Layer& mask);
	void Remove(class GameObject*const obj);
		

	

private:
	using MapIter = unordered_map<RenderLayer, vector<class GameObject*>>::iterator;
	using VecIter = vector<class GameObject*>::iterator;
	unordered_map<RenderLayer, vector<class GameObject*>> renderList;

	RenderManager();
	~RenderManager();

	void Render();

	void ObjectRender();
	void LightRender();
	void UIRender();
	void ImguiRender();
};

