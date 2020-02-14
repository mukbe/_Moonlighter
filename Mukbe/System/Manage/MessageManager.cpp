#include "Mukbe.h"
#include "MessageManager.h"


MessageManager::MessageManager()
{
	for (UINT i = 0; i < 20; ++i)
	{
		dataPool.push_back(new DataContext());
	}

}


MessageManager::~MessageManager()
{
	RemoveAllMessage();

	while (dataPool.size() > 0)
	{
		SafeDelete(dataPool.front());
		dataPool.pop_front();
	}
}

void MessageManager::Update(float tick)
{
	MsgListIter Iter = reserveList.begin();
	for (;Iter != reserveList.end();)
	{
		Iter->second.DelayTime -= tick;
		if (Iter->second.DelayTime <= 0.f)
		{
			Iter->first->SendCallbackMessage(Iter->second);
			Iter = reserveList.erase(Iter);
		}
		else
			Iter++;

		
	}
}

void MessageManager::RemoveAllMessage()
{
	MsgListIter Iter = reserveList.begin();
	for (;Iter != reserveList.end();)
	{
		if (Iter->second.Data != nullptr)
		{
			ReturnData(Iter->second.Data);
			Iter = reserveList.erase(Iter);
		}
		else
			Iter++;
	}
}

void MessageManager::ReserveMessage(MessageComponent * gameObject, TagMessage msg)
{
	gameObject->SendCallbackMessage(msg);
}

void MessageManager::ReserveMessage(MessageComponent * gameObject, string name, float delay)
{
	gameObject->SendCallbackMessage(name, delay);
}

void MessageManager::ReturnData(DataContext * const data)
{
	dataPool.emplace_back(data);
}

DataContext* MessageManager::CreateData()
{
	return (new DataContext());
}

DataContext * MessageManager::GetData()
{
	DataContext* data = nullptr;
	if (dataPool.size() != 0)
	{
		data = dataPool.front();
		dataPool.pop_front();
	}
	else
	{
		data = CreateData();
	}
	return data;
}


