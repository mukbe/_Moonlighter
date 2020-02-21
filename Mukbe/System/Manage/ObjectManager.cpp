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
	for (int i = 0; i < (int)objects.size(); i++)
	{
		GameObject* a = objects[i];
		if (a->IsActive() == false) continue;
		if (a->GetCollisionType() == CollisionType_None) continue;
		// ..elas

		for (int j = i + 1; j < (int)objects.size();j++)
		{
			GameObject* b = objects[j];
			if (b->IsActive() && b->GetCollisionType() != CollisionType_None)
			{
				if (Math::IsAABBInAABB(a->GetCollider(), b->GetCollider()))
				{
					manifold.push_back(Manifold(a, b, Manifold::Type::Manifold_On));
				}
			}
		}
	}

	for (int i = 0; i < (int)manifold.size(); i++)
	{
		Manifold& mf = manifold[i];
		bool bCheck = false;
		for (int j = i + 1; j < (int)manifold.size();j++)
		{
			Manifold& mf2 = manifold[j];
			if (mf == mf2)
			{
				mf.type = Manifold::Type::Manifold_Stay;
				manifold.erase(manifold.begin() + j);
				j--;
				bCheck = true;
			}
		}
		if (mf.bOnce == false && bCheck == false)
		{
			mf.type = Manifold::Type::Manifold_Exit;
		}
	}

	for (int i = 0; i < (int)manifold.size(); i++)
	{
		Manifold& mf = manifold[i];
		switch (mf.type)
		{
			case Manifold::Type::Manifold_On:
			{
				_MessagePool->ReserveMessage(mf.a, "OnCollisionEnter", 0.f, mf.b);
				_MessagePool->ReserveMessage(mf.b, "OnCollisionEnter", 0.f, mf.a);
				mf.bOnce = false;
			}
			break;
			case Manifold::Type::Manifold_Stay :
			{
				_MessagePool->ReserveMessage(mf.a, "OnCollisionStay", 0.f, mf.b);
				_MessagePool->ReserveMessage(mf.b, "OnCollisionStay", 0.f, mf.a);
			}
			break;
			case Manifold::Type::Manifold_Exit :
			{
				_MessagePool->ReserveMessage(mf.a, "OnCollisionExit", 0.f, mf.b);
				_MessagePool->ReserveMessage(mf.b, "OnCollisionExit", 0.f, mf.a);
				manifold.erase(manifold.begin() + i);
				i--;
			}
			break;
			default:
			break;
		}
	}


	for (int i= 0; i < (int)objects.size(); i++)
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


