#pragma once

struct Manifold
{
	enum Type
	{
		Manifold_On,
		Manifold_Stay,
		Manifold_Exit,
		Manifold_None
	};
	GameObject* a;
	GameObject* b;
	Type type;
	bool bOnce;
	Manifold(GameObject* aa, GameObject* bb, Type t) : a(aa), b(bb),type(t)
	{
		bOnce = true;
	}
	const bool& operator==(Manifold other)
	{
		if (a == other.a)
			if (b == other.b)
				return true;

		return false;
	}
	const bool& operator!=(Manifold other)
	{
		if (a == other.a)
			if (b == other.b)
				return false;

		return true;
	}

};

class TileNode;
class ObjectManager
{
	friend class SceneBase;		//씬에서 생성함
public:
	void DeletaObject(class GameObject* object);
	
	//게임오브젝트와 상속성 검사, 해당 포인터형으로 반환
	IS_INHERITED_THAN_RETURN(GameObject) CreateObject(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	//게임오브젝트와 상속성 검사, 해당 포인터형으로 반환
	IS_INHERITED_THAN_RETURN(GameObject) FindObject(string name);
	//게임오브젝트랑 상속성검사 UI베이스 같은놈으로 리턴받을때 주의, 몬스터의 포인터가 UI의 포인터로 바뀔 우려가 있다
	IS_INHERITED_THAN_RETURN_VECTOR_ARRAY(GameObject) FindObjects(string name);
	//커스텀으로 상속성검사 <베이스,받아올 포인터형> UI의 포인터를 가져올때 UI의 베이스를 두는지 검사 가능
	IS_INHERITED_THAN_RETURN_VECTOR_ARRAY_WITH_CUSTOM FindObjectInheritedMid(string name);

	void SetUpdate(bool b) { bUpdate = b; }
	vector<class GameObject*> GetArray() { return objects; }
private:
	using VecIter = vector<class GameObject*>::iterator;
	vector<class GameObject*> objects;
	vector<class GameObject*> deleteList;

	vector<struct Manifold> manifold;
	bool bUpdate;

	ObjectManager();
	~ObjectManager();

	void Update(float tick);

};

IS_INHERITED_THAN_RETURN(class GameObject) ObjectManager::CreateObject(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
{
	Derived* temp = new Derived(name, pos, size);

	//virtual void GameObject::Init
	temp->Init();
	

	objects.push_back(temp);
	

	return temp;
}



IS_INHERITED_THAN_RETURN(class GameObject) ObjectManager::FindObject(string name)
{
	for (size_t t = 0; t < objects.size(); t++)
	{
		if (name == objects[t]->Name())
			return static_cast<Derived*>(objects[t]);
	}

	LOG->Error(__FILE__, __LINE__, "can't find object");
	return nullptr;
}


IS_INHERITED_THAN_RETURN_VECTOR_ARRAY(GameObject) ObjectManager::FindObjects(string name)
{
	vector<Derived*> vec;
	for (size_t t = 0; t < objects.size(); t++)
	{
		if (name == objects[t]->Name())
			vec.push_back(static_cast<Derived*>(objects[t]));
	}
	return std::move(vec);
}

 IS_INHERITED_THAN_RETURN_VECTOR_ARRAY_WITH_CUSTOM ObjectManager::FindObjectInheritedMid(string name)
{
	 vector<Derived*> vec;
	 for (GameObject* obj : objects)
	 {
		 if (obj->Name() == name)
		 {
			 vec.push_back(static_cast<std::enable_if_t<Is_Inherited<Base, typeid(*obj)>::Result, Derived*>>(obj));
		 }
	 }
	 return std::move(vec);
}


