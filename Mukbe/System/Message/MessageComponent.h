#pragma once
class MessageComponent
{
public:
	MessageComponent();
	virtual~MessageComponent();

private:
	typedef unordered_map<string, function<void(TagMessage)>>::iterator MessageIter;
private:
	unordered_map<string, function<void(TagMessage)>> messageList;

public:
	//�޼����� ���� �ݹ���
	void AddCallback(string msgName, function<void(TagMessage)> func);
	
	void SendCallbackMessage(TagMessage msg);
	void SendCallbackMessage(const string name, const float delay = 0.f, DataContext* data = nullptr);

};

