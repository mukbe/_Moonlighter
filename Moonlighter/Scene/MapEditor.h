#pragma once

class MapEditor : public SceneBase
{
	enum ObjectKind
	{
		Object_None,
		Object_StaticObjectBase,
	};

public:
	MapEditor();
	~MapEditor();

	virtual void Init();
	virtual void OnceInit();
	virtual void Update(float tick);
	virtual void ImguiRender();

	void CreateObject(ObjectKind val);
private:
	class MouseObject* mouse;

	ObjectKind current;
	D3DXVECTOR2 oldPickPos;
	
};

