#pragma once
#include <iostream>
#include <fstream>
#include <time.h>

using namespace std;


//ofstream ����
//ifstream �б�
#define LOG_MAX_MESSAGE 30

struct LogHandle
{
	string FileName;
	ofstream w;
	ifstream r;
	//mutex mut;
};


class Logging
{
	SingletonHeader(Logging)
private:
	vector<string> logs;
	LogHandle handle;

public:
	void Init(const char* filename = "../LogTest.txt");
	void Release();
	void Print(const char* str, ...);
	void Print(const char* funcName, const char* str, ...);
	void Warning(const char* filename, int line, const char* condition);
	void Error(const char* filename, int line, const char* condition);
	void ImShowData();

};

#define LOG Logging::Get()
//�����ϸ� ���� ���� �����ؼ� ���
#define Log_WarnAssert(x) if(!(x)) { LOG->Warning(__FILE__, __LINE__, "" #x); }
//�����ϸ� ���� ���� �����ؼ� ���
#define Log_ErrorAssert(x) if(!(x)) { LOG->Error(__FILE__, __LINE__, "" #x); }

#define Log_Print(x,...) LOG->Print(x,##__VA_ARGS__)
#define Log_PrintF(x,...) LOG->Print(__FUNCTION__, x, ##__VA_ARGS__)