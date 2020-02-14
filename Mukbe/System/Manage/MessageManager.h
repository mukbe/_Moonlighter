#pragma once
//씬이 넘어갈때마다 메세지 내용을 초기화 시켜줘야 한다

class MessageComponent;
class DataContext;
struct TagMessage;
class MessageManager
{
	friend class SceneBase;
private:
	typedef vector<pair<MessageComponent*, TagMessage>>::iterator MsgListIter;

private:
	MessageManager();
	~MessageManager();
	void Update(float tick);

	void RemoveAllMessage();

public:
	//메세지 예약
	void ReserveMessage(MessageComponent* gameObject, TagMessage msg);
	//바로 메세지를 전달해보고 딜레이가 같으면 예약메세지로 등록됨
	void ReserveMessage(MessageComponent* gameObject, string name, float delay = 0.f);
	//데이터를 같이 메세지로 예약
	template<typename T>
	void ReserveMessage(MessageComponent* gameObject, string name, float delay, const T& data);

	void ReturnData(DataContext* const data);

private:
	deque<DataContext*> dataPool;
	vector<pair<MessageComponent*, TagMessage>> reserveList;


	DataContext* CreateData();
	DataContext* GetData();



};

template<typename T>
inline void MessageManager::ReserveMessage(MessageComponent * gameObject, string name, float delay, const T & data)
{
	DataContext* const value = GetData();
	value->SetValue(data);
	ReserveMessage(gameObject, TagMessage(name, delay, value));
}


//#define MessagePool MessageManager::Get()