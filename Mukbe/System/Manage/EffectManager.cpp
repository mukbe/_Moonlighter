#include "Mukbe.h"
#include "EffectManager.h"


SingletonCpp(EffectManager)
EffectManager::EffectManager()
{
}


EffectManager::~EffectManager()
{
}

void EffectManager::Update(float tick)
{

	VecIter Iter = playList.begin();

	for (; Iter != playList.end(); ++Iter)
	{
		EffectDesc& effect = *Iter;
		effect.UpdateTime += tick;
		if (effect.UpdateTime >= effect.InvFps)
		{
			effect.UpdateTime -= effect.InvFps;
			effect.Frame++;
			if (effect.Frame >= effect.MaxFrame)
			{
				effect.RoopCount--;
				effect.Frame = 0;
			}
		}
	}

	for (Iter = playList.begin(); Iter != playList.end();)
	{
		if ((*Iter).RoopCount <= 0)
		{
			Iter = playList.erase(Iter);
		}
		else
		{
			Iter++;
		}
	}
}

void EffectManager::Render()
{
	p2DRenderer->SetCamera(true);
	for (int i = 0; i < playList.size(); i++)
	{
		playList[i].Image->FrameRender(playList[i].Rect, &playList[i].Transform , playList[i].Frame);
	}
}

void EffectManager::Fire(string key, D3DXVECTOR2 pos, D3DXVECTOR2 size, float radian, float fps)
{
	EffectDesc effect = Find(key);
	effect.Transform = Matrix2D(pos);
	effect.Transform.SetRadian(radian);
	effect.Rect = FloatRect(D3DXVECTOR2(0, 0), size, Pivot::CENTER);
	effect.InvFps = 1.f / fps;
	effect.RoopCount = 1;
	if (effect.Image->GetMaxFrame().x < 1.5f)
		effect.RoopCount++;
	playList.push_back(effect);
}

void EffectManager::AddEffect(string key, string imageKey)
{
	EffectDesc effect;
	effect.Image = _ImageManager->FindTexture(imageKey);
	effect.MaxFrame = (UINT)effect.Image->GetMaxFrame().x;
	effectList.insert(make_pair(key, effect));
}

EffectDesc EffectManager::Find(string key)
{
	MapIter Iter = effectList.find(key);
	if (Iter != effectList.end())
	{
		return Iter->second;
	}

	//없는거임 예외처리 해야됨
	return EffectDesc();
}
