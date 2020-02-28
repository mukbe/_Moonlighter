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
	friend class SceneBase;		//������ ������
public:
	void DeletaObject(class GameObject* object);
	
	//���ӿ�����Ʈ�� ��Ӽ� �˻�, �ش� ������������ ��ȯ
	IS_INHERITED_THAN_RETURN(GameObject) CreateObject(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	//���ӿ�����Ʈ�� ��Ӽ� �˻�, �ش� ������������ ��ȯ
	IS_INHERITED_THAN_RETURN(GameObject) FindObject(string name);
	//���ӿ�����Ʈ�� ��Ӽ��˻� UI���̽� ���������� ���Ϲ����� ����, ������ �����Ͱ� UI�� �����ͷ� �ٲ� ����� �ִ�
	IS_INHERITED_THAN_RETURN_VECTOR_ARRAY(GameObject) FindObjects(string name);
	//Ŀ�������� ��Ӽ��˻� <���̽�,�޾ƿ� ��������> UI�� �����͸� �����ö� UI�� ���̽��� �δ��� �˻� ����
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


