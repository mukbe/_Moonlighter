#pragma once
// 2020.02.05 Mokube 
// Animation 
#define USEIMGUI


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
	static void Save(AnimationClip* clip, BinaryWriter* w);
	static void Load(AnimationClip** ppClip, BinaryReader* r);
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
	const bool IsLoop() { return isLoop; }
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

#ifdef USEIMGUI
private:
	D3DXVECTOR2 pickedFrame = { 0.f, 0.f };
	vector<pair<int, int>> drag_save_frame = vector<pair<int, int>>();
	ImVec2 clicked_start = { 0, 0 };
	ImVec2 clicked_end = { 0, 0 };
	int current_item = -1;
	int current_item_callback = -1;
	float aniFrame_size = 100.f;
#endif // USEIMGUI

};

