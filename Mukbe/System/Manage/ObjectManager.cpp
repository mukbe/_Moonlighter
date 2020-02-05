#include "Mukbe.h"
#include "ObjectManager.h"

ObjectManager::ObjectManager()
{
	deleteList.clear();
	objects.clear();
}


ObjectManager::~ObjectManager()
{
	if (objects.empty() == false)
	{
		VecIter Iter = objects.begin();
		for (; Iter != objects.end();)
		{
			(*Iter)->Release();
			SafeDelete(*Iter);
			Iter = objects.erase(Iter);
		}
	}


	if (deleteList.empty() == false)
	{
		VecIter Iter = deleteList.begin();
		for (; Iter != deleteList.end();)
		{
			(*Iter)->Release();
			SafeDelete(*Iter);
			Iter = deleteList.erase(Iter);
		}
	}

}




void ObjectManager::Update(float tick)
{

	for (int i= 0; i < objects.size(); i++)
	{
		objects[i]->Update(tick);
	}


	if (deleteList.empty() == false)
	{
		VecIter Iter = deleteList.begin();
		for (; Iter != deleteList.end();)
		{
			(*Iter)->Release();
			SafeDelete(*Iter);
			Iter = deleteList.erase(Iter);
		}
	}
	
}


void ObjectManager::DeletaObject(GameObject * object)
{
	for (size_t t = 0; t < objects.size(); t++)
	{
		if (objects[t] == object)
		{
			deleteList.emplace_back(object);
			objects.erase(objects.begin() + t);
			break;
		}
	}

}


