#pragma once
#include <any>

struct TagMessage
{
	string Name;
	float DelayTime;
	class DataContext* Data;

	TagMessage() : Name(""), DelayTime(0.f), Data(nullptr) {}
	explicit TagMessage(string name, float delay, DataContext* data)
		: Name(name), DelayTime(delay), Data(data) {}
	
};

class GameObject;
class DataContext
{
public:
	template<typename T>
	void SetValue(T val)
	{
		if (value.has_value())
			value.reset();

		value = val;
	}

	template<typename T>
	T GetValue()
	{
		assert(value.has_value());
		T t;
		try
		{
			t = any_cast<T>(value);
		}
		catch (bad_any_cast& e)
		{
			LOG->Error(__FILE__, __LINE__, "bad_any_cast");
			ZeroMemory(&t, sizeof(T));
		}
		return t;
	}

	string GetType()
	{
		string str = "";
		if (!value.has_value())
			str = "no value";
		else
			str = value.type().name();
		
		return str;
	}

private:
	any value;

};
