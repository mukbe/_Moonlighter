#pragma once
#include "Animation.h"
#include "./Interfaces/ICloneable.h"

class Animator : public ICloneable
{
private:
	using MapIter = unordered_map<string, AnimationClip*>::iterator;
	unordered_map<string, AnimationClip*> animations;

	AnimationClip* currentAnim;
public:
	virtual void Clone(void** clone);

	Animator();
	~Animator();
	
	void Update();
	void Render(FloatRect rc, Matrix2D* world, float alpha);

	void AddAnimation(const string& key, AnimationClip* anim);
	void DeleteAnimation(const string& key);
	void ChangeAnimation(const string& key);

	void Play();
	void Stop();
	void Pause();

	AnimationClip* GetCurrentAnim() { return currentAnim; }
	AnimationClip* FindAnimation(const string& key);

};


