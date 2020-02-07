#pragma once
// 2020.02.05 Mokube 
// Animation 


#include "./Interfaces/ICloneable.h"

struct AniFrame
{
	int FrameX;
	int FrameY;
	vector<string> callBacks;
	AniFrame() : FrameX(0),FrameY(0) {}
	AniFrame(int x, int y) : FrameX(x), FrameY(y) {}
	AniFrame(pair<int, int> frame)
	{
		FrameX = frame.first;
		FrameY = frame.second;
	}

	void AddCallBack(string name) { callBacks.push_back(name); }
	void AddCallBack(string names[])
	{
		for (int i = 0; i < _ARRAYSIZE(names); i++)
			callBacks.push_back(names[i]);
	}
};


class AnimationClip : public ICloneable
{
private:
	using CallBackFunc = function<void(void)>;

public:
	virtual void Clone(void** clone);

	AnimationClip();
	~AnimationClip();
	
	void Uptate();
	void Redner(FloatRect rc, Matrix2D* world, float alpha);
	void Init();

	void Stop();
	void Pause();
	void Play();


	void PushBackFrame(pair<int, int> frame);
	void PushBackFrame(vector<pair<int, int>> frames);
	void PushBackFrame(int x, int y);
	void PushBackFrame(int startX, int startY, int endX, int endY, bool reverse = false, bool axisX = true);
	void PushBackAniFrame(AniFrame aniframe);
	
	void RegisterAniFrameCallBack(int index, string name);
	void RegisterAniFrameCallBack(int index, string name[]);
	void RegisterAniFrameCallBack(int index[], string name);
	void RegisterAniFrameCallBack(int index[], string name[]);


	void SetFrameImage(string image);
	void SetFps(float val);
	void SetLoop(bool loop);


	void RegisterCallBackTable(string name, CallBackFunc func);
	void DeleteCallBackTable(string name);

	//Get
	const bool IsPlay() { return isPlay; }
	const bool IsKoop() { return isLoop; }
	const AniFrame& GetCurrentFrameInfo() { return currentFrame; }
	const string& GetImageKey() { return imageKey; }

	void ImguiRender();

private:
	unordered_map<string, CallBackFunc> callBackFuncTable;
	vector<AniFrame> frames;

	float fps;
	float invFps;
	float updateTime;
	bool isPlay;
	bool isLoop;

	int currentIndex;
	AniFrame currentFrame;

	string imageKey;
	shared_ptr<Texture> texture;
	int maxFrame[2];
};

