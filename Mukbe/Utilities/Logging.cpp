#include "Mukbe.h"
#include "Logging.h"

SingletonCpp(Logging)

Logging::Logging()
{

}

Logging::~Logging()
{

}

void Logging::Init(const char * filename)
{
	handle.FileName = filename;
	handle.w.open(filename, ios::app);
	handle.r.open(filename, ios::in);

	tm pt;
	time_t  curTime = 0;
	time(&curTime);
	localtime_s(&pt, &curTime);
	

	//snprintf(str, 128, "%02i%02i%02i %d : %d : %d", pt.tm_year + 1900, pt.tm_mon + 1, pt.tm_mday, pt.tm_hour
	//	, pt.tm_min, pt.tm_sec);

	handle.w << "===================================================" << endl;

	handle.w << " " << pt.tm_year + 1900 << "." << pt.tm_mon + 1 << "." << pt.tm_mday << '\t';
	if (pt.tm_hour < 10)
		handle.w << "0";
	handle.w << pt.tm_hour << ":";
	if (pt.tm_min < 10)
		handle.w << "0";
	handle.w << pt.tm_min << ":";
	if (pt.tm_sec < 10)
		handle.w << "0";
	handle.w << pt.tm_sec << '\t';

	D3DDesc desc;
	DxRenderer::GetDesc(&desc);
	handle.w << " '" << String::WStringToString(desc.AppName).c_str() << "' Start Succeeded" << endl;
}

void Logging::Release()
{
	handle.r.close();
	handle.w << '\t'<< '\t' << '\t'<<" End" << endl;
	handle.w << "===================================================" << endl;
	handle.w.close();
}

void Logging::Print(const char * str, ...)
{
	char buffer0[2048];

	va_list args;
	va_start(args, str);
	vsnprintf(buffer0, 2048, str, args);
	va_end(args);

	tm pt;
	time_t  curTime = 0;
	time(&curTime);
	localtime_s(&pt, &curTime);

	handle.w << " " << pt.tm_year + 1900 << "." << pt.tm_mon + 1 << "." << pt.tm_mday << '\t';
	if (pt.tm_hour < 10)
		handle.w << "0";
	handle.w << pt.tm_hour << ":";
	if (pt.tm_min < 10)
		handle.w << "0";
	handle.w << pt.tm_min << ":";
	if (pt.tm_sec < 10)
		handle.w << "0";
	handle.w << pt.tm_sec << '\t';

	handle.w << buffer0 << endl;

	if (logs.size() >= LOG_MAX_MESSAGE)
		logs.erase(logs.begin());

	logs.push_back(buffer0);
}

void Logging::Print(const char * funcName, const char * str, ...)
{
	char buffer0[2048];
	char buffer1[2048];

	va_list args;
	va_start(args, str);
	vsnprintf(buffer0, 2048, str, args);
	va_end(args);

	tm pt;
	time_t  curTime = 0;
	time(&curTime);
	localtime_s(&pt, &curTime);

	handle.w << " " << pt.tm_year + 1900 << "." << pt.tm_mon + 1 << "." << pt.tm_mday << '\t';
	if (pt.tm_hour < 10)
		handle.w << "0";
	handle.w << pt.tm_hour << ":";
	if (pt.tm_min < 10)
		handle.w << "0";
	handle.w << pt.tm_min << ":";
	if (pt.tm_sec < 10)
		handle.w << "0";
	handle.w << pt.tm_sec << '\t';

	sprintf_s(buffer1, 2048, "%s : %s", funcName, buffer0);

	handle.w << buffer1 << endl;

	if (logs.size() >= LOG_MAX_MESSAGE)
		logs.erase(logs.begin());

	logs.push_back(buffer1);

}

void Logging::Warning(const char * filename, int line, const char * condition)
{
	D3DDesc desc;
	DxRenderer::GetDesc(&desc);
	char message[2048]{ 0 };

	tm pt;
	time_t  curTime = 0;
	time(&curTime);
	localtime_s(&pt, &curTime);

	if (pt.tm_hour < 10)
		handle.w << "0";
	handle.w << pt.tm_hour << ":";
	if (pt.tm_min < 10)
		handle.w << "0";
	handle.w << pt.tm_min << ":";
	if (pt.tm_sec < 10)
		handle.w << "0";
	handle.w << pt.tm_sec << '\t';
	handle.w << "Assertion Failure!" << endl;
	handle.w << "File: " << filename << endl;
	handle.w << "Line: " << line << endl;
	handle.w << "Code: " << condition << endl;

	snprintf(message, 2048,
		"%02i:%02i:%02i Assertion Failure! \nFile: %s \nLine: %i \nCode: %s"
		, pt.tm_hour, pt.tm_min, pt.tm_sec, filename, line, condition);

	MessageBox(desc.Handle
		, String::StringToWString(message).c_str()
		, String::StringToWString(condition).c_str()
		, MB_ICONWARNING);

	logs.push_back(message);
}

void Logging::Error(const char * filename, int line, const char * condition)
{
	D3DDesc desc;
	DxRenderer::GetDesc(&desc);
	char message[2048]{ 0 };

	tm pt;
	time_t  curTime = 0;
	time(&curTime);
	localtime_s(&pt, &curTime);

	if (pt.tm_hour < 10)
		handle.w << "0";
	handle.w << pt.tm_hour << ":";
	if (pt.tm_min < 10)
		handle.w << "0";
	handle.w << pt.tm_min << ":";
	if (pt.tm_sec < 10)
		handle.w << "0";
	handle.w << pt.tm_sec << '\t';
	handle.w << "Fatal Assertion Failure!" << endl;
	handle.w << "File: " << filename << endl;
	handle.w << "Line: " << line << endl;
	handle.w << "Code: " << condition << endl;

	snprintf(message, 2048,
		"%02i:%02i:%02i Fatal Assertion Failure! \nFile: %s \nLine: %i \nCode: %s"
		, pt.tm_hour, pt.tm_min, pt.tm_sec, filename, line, condition);

	MessageBox(desc.Handle
		, String::StringToWString(message).c_str()
		, String::StringToWString(condition).c_str()
		, MB_ICONSTOP);

	logs.push_back(message);
}

void Logging::ImShowData()
{
	ImGuiWindowFlags flag = 0;
	flag |= ImGuiWindowFlags_NoTitleBar;
	flag |= ImGuiWindowFlags_AlwaysAutoResize;
	static bool open = true;
	ImGui::SetNextWindowSize(ImVec2(400, 200));
	ImGui::SetNextWindowPos(ImVec2(WinSizeX - 400, WinSizeY - 200));
	ImGui::Begin("Log",&open,flag);
	for (size_t t = 0; t < logs.size(); t++)
	{
		ImGui::Text(logs[t].c_str());
		ImGui::Separator();
	}

	ImGui::End();
}
