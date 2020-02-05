#pragma once



//Singleton
class Time
{
public:
	static bool Stopped() { return isTimerStopped; }
	//< ���� ���������κ��� ����ð�
	static float Delta() { return isTimerStopped ? 0.0f : timeElapsed; }
	static float Tick() { return InvLockFPS; }
	void Update();
	void Print();

	void Start();
	void Stop();

	float FPS() const { return framePerSecond; }
	float Running() const { return runningTime; }

	float GetWorldTime() { return worldTime; }
	void AddWorldTime(float val) { worldTime += val; }

	UINT GetHour() { return hour; }
	UINT GetMinute() { return minute; }
	float GetDayTimeRatio() { return dayTimeRatio; }

	float GetLockFPS() { return lockFPS; }
	void SetLockFPS(float val);
private:
	
	void UpdateWorldTime();
private:
	static bool isTimerStopped;///< Ÿ�̸� ����
	static float timeElapsed;///< ���� ���������κ��� ����ð�
	static float InvLockFPS;


	INT64 ticksPerSecond;///< �ʴ� ƽī��Ʈ
	INT64 currentTime;///< ���� �ð�
	INT64 lastTime;///< �����ð�
	INT64 lastFPSUpdate;///< ������ FPS ������Ʈ �ð�
	INT64 fpsUpdateInterval;///< fps ������Ʈ ����

	UINT frameCount;///< ������ ��
	float runningTime;///< ���� �ð�
	float framePerSecond;///< FPS
	float lockFPS;

	float worldTime;
	UINT hour;
	UINT minute;

	const float secondsPerDay;
	float dayTimeRatio;


	SingletonHeader(Time)
};