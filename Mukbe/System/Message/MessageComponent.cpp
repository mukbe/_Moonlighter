#include "Mukbe.h"
#include "MessageComponent.h"
#include "./System/Manage/MessageManager.h"

MessageComponent::MessageComponent()
{
	messageList.clear();
}


MessageComponent::~MessageComponent()
{
	messageList.clear();
}

void MessageComponent::AddCallback(string msgName, function<void(TagMessage)> func)
{
	messageList.insert(make_pair(msgName, func));
}

void MessageComponent::SendCallbackMessage(TagMessage msg)
{
	if (msg.DelayTime > 0.f)
	{
		//메세지 보류
		_GameWorld->GetMessagePool()->ReserveMessage(this, msg);
	}
	else
	{
		MessageIter Iter = messageList.find(msg.Name);
		if (Iter != messageList.end())
		{
			Iter->second(msg);
			if (msg.Data != nullptr)
			{
				//데이터 반환
				_GameWorld->GetMessagePool()->ReturnData(msg.Data);

			}
		}
	}
}

void MessageComponent::SendCallbackMessage(const string name, const float delay, DataContext* data)
{
	if (delay > 0.f)
	{
		//메세지 보류
		_GameWorld->GetMessagePool()->ReserveMessage(this, TagMessage(name, delay, data));
	}
	else
	{
		MessageIter Iter = messageList.find(name);
		if (Iter != messageList.end())
		{
			Iter->second(TagMessage(name, delay, data));
			if (data != nullptr)
			{
				//데이터 반환
				_GameWorld->GetMessagePool()->ReturnData(data);
			}
		}
	}
}


