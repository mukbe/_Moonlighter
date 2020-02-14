#pragma once
//���� �Ѿ������ �޼��� ������ �ʱ�ȭ ������� �Ѵ�

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
	//�޼��� ����
	void ReserveMessage(MessageComponent* gameObject, TagMessage msg);
	//�ٷ� �޼����� �����غ��� �����̰� ������ ����޼����� ��ϵ�
	void ReserveMessage(MessageComponent* gameObject, string name, float delay = 0.f);
	//�����͸� ���� �޼����� ����
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