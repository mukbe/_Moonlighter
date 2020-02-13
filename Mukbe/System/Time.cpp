#include "Mukbe.h"
#include "Time.h"

SingletonCpp(Time)

bool Time::isTimerStopped = true;
float Time::timeElapsed = 0.0f;
float Time::InvLockFPS = 0.0f;

Time::Time(void) :
	ticksPerSecond(0), currentTime(0), lastTime(0), lastFPSUpdate(0), fpsUpdateInterval(0),
	frameCount(0), runningTime(0), framePerSecond(0)
	, worldTime(3000.0f), hour(0), minute(0), day(0)
	, secondsPerDay(600), dayTimeRatio(0)
{
	QueryPerformanceFrequency((LARGE_INTEGER *)&ticksPerSecond);
	fpsUpdateInterval = ticksPerSecond >> 1;



	dayTimeRatio = (Math::PI * 2.0f) / (secondsPerDay * 100);

	lockFPS = 60.f;
	InvLockFPS = 1.f / lockFPS;
}

Time::~Time(void)
{

}

void Time::UpdateWorldTime()
{
	worldTime += Delta() * 400.0f;


	float time24HClock = (float)Math::Lerp(0.f, 24.f, worldTime * dayTimeRatio / (Math::PI * 0.5f));

	day = (UINT)time24HClock / 24;
	hour = (UINT)time24HClock % 24;
	minute = (UINT)((time24HClock - hour - day * 24) * 60.0f);
}

void Time::Update()
{
	if (isTimerStopped) return;

	//1. 현재시간을 가져와 시간 간격 및 진행 시간을 계산한다.
	QueryPerformanceCounter((LARGE_INTEGER *)&currentTime);
	timeElapsed = (float)(currentTime - lastTime) / (float)ticksPerSecond;


	if (lockFPS != 0.f && lockFPS > 0.f)
	{
		while (timeElapsed < (1.0f / lockFPS))
		{
			QueryPerformanceCounter((LARGE_INTEGER*)&this->currentTime);
			timeElapsed = (float)((currentTime - lastTime)) / (float)ticksPerSecond;
		}
	}
	else if (Math::FloatEqual(lockFPS, 0.f))
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&this->currentTime);
		timeElapsed = (float)((currentTime - lastTime)) / (float)ticksPerSecond;
		InvLockFPS = timeElapsed;
	}


	runningTime += timeElapsed;

	//2. FPS Update
	frameCount++;
	if (currentTime - lastFPSUpdate >= fpsUpdateInterval)
	{
		float tempCurrentTime = (float)currentTime / (float)ticksPerSecond;
		float tempLastTime = (float)lastFPSUpdate / (float)ticksPerSecond;
		framePerSecond = (float)frameCount / (tempCurrentTime - tempLastTime);

		lastFPSUpdate = (INT64)currentTime;
		frameCount = 0;
	}

	lastTime = currentTime;

	UpdateWorldTime();
}

void Time::Print()
{

}

void Time::Start()
{
	if (!isTimerStopped)
		assert(false);

	QueryPerformanceCounter((LARGE_INTEGER *)&lastTime);
	isTimerStopped = false;
}

void Time::Stop()
{
	if (isTimerStopped)
		assert(false);

	INT64 stopTime = 0;
	QueryPerformanceCounter((LARGE_INTEGER *)&stopTime);
	runningTime += (float)(stopTime - lastTime) / (float)ticksPerSecond;
	isTimerStopped = true;
}

void Time::SetLockFPS(float val)
{
	if (val <= 0.0001f)
	{
		lockFPS = val;
	}
}
