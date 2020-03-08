#pragma once

struct EffectDesc
{
	Matrix2D Transform;
	FloatRect Rect;
	UINT Frame;
	UINT MaxFrame;
	float InvFps;
	float UpdateTime;
	int RoopCount;
	float Delay;
	shared_ptr<Texture> Image;
	EffectDesc() : Frame(0), RoopCount(0), InvFps(1 / 60.f), UpdateTime(0.f),Delay(0.f) {}
};
class EffectManager
{
	SingletonHeader(EffectManager)
public:

	void Update(float tick);
	void Render();

	void Fire(string key, D3DXVECTOR2 pos, D3DXVECTOR2 size, float radian = 0.f , float fps = 60.f, float removeDelay = 0.f);
	void AddEffect(string key, string imageKey);
private:
	using MapIter = unordered_map < string, EffectDesc>::iterator;
	using VecIter = vector < EffectDesc>::iterator;
	unordered_map<string, EffectDesc> effectList;
	vector<EffectDesc> playList;

	EffectDesc Find(string key);

};

#define EFFECTS EffectManager::Get()