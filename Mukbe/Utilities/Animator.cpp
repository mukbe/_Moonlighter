#include "Mukbe.h"
#include "Animator.h"

void Animator::Save(Animator * anim, BinaryWriter * w)
{
	w->String(anim->name);
	w->Int((int)anim->animations.size());
	MapIter Iter = anim->animations.begin();
	for (; Iter != anim->animations.end(); ++Iter)
	{
		w->String(Iter->first);
		AnimationClip::Save(Iter->second, w);
	}
}

void Animator::Load(Animator ** ppAnim, BinaryReader * r)
{
	Animator* anim = new Animator();
	anim->name = r->String();
	int animationCount = r->Int();
	for (int i = 0; i < animationCount; i++)
	{
		string clipKey = r->String();
		AnimationClip* clip = nullptr;
		AnimationClip::Load(&clip, r);
		anim->AddAnimation(clipKey, clip);
	}
	

	*ppAnim = anim;
}

void Animator::Clone(void ** clone)
{
	*clone = new Animator;
	Animator* other = reinterpret_cast<Animator*>(*clone);

	MapIter Iter = animations.begin();
	while (Iter != animations.end())
	{
		AnimationClip* anim;
		Iter->second->Clone((void**)&anim);
		other->AddAnimation(Iter->first, Iter->second);

		Iter++;
	}
}


Animator::Animator()
	:currentAnim(nullptr)
{
}

Animator::~Animator()
{
	MapIter Iter = animations.begin();
	for (;Iter != animations.end();)
	{
		if (Iter->second != nullptr)
		{
			SafeDelete(Iter->second);
		}
		else
		{
			Log_PrintF("");
		}

		Iter = animations.erase(Iter);
	}

}

void Animator::Update()
{
	if (currentAnim != nullptr)
		currentAnim->Uptate();
}

void Animator::Render(FloatRect rc, Matrix2D * world, float alpha)
{
	if (currentAnim != nullptr)
		currentAnim->Redner(rc, world, alpha);
}


inline void Animator::AddAnimation(const string& key, AnimationClip * anim) 
{
	animations.insert(make_pair(key, anim));
}

void Animator::DeleteAnimation(const string & key)
{
	MapIter Iter = animations.find(key);
	if (Iter != animations.end())
	{
		animations.erase(Iter);
	}
}

void Animator::ChangeAnimation(const string & key)
{
	currentAnim = animations[key];
	currentAnim->Play();
	//Log_WarnAssert(currentAnim == nullptr);
}

void Animator::Play()
{
	currentAnim->Play();
}

void Animator::Stop()
{
	currentAnim->Stop();
}

void Animator::Pause()
{
	currentAnim->Pause();
}

AnimationClip * Animator::FindAnimation(const string & key)
{
	return animations[key];
}

