#pragma once
class MessageComponent
{
	friend class MessageManager;
private:
	typedef unordered_map<string, function<void(TagMessage)>>::iterator MessageIter;
	unordered_map<string, function<void(TagMessage)>> messageList;

public:
	MessageComponent();
	virtual~MessageComponent();

	//메세지로 받을 콜백등록
	void AddCallback(string msgName, function<void(TagMessage)> func);

private:
	
	void SendCallbackMessage(TagMessage msg);
	void SendCallbackMessage(const string name, const float delay = 0.f, DataContext* data = nullptr);

};

