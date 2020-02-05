#include "Mukbe.h"
#include "Animation.h"



void AnimationClip::Clone(void** clone)
{
	*clone = new AnimationClip;
	AnimationClip* other = reinterpret_cast<AnimationClip*>(*clone);
	other->callBackFuncTable = this->callBackFuncTable;
	other->frames = this->frames;
	other->fps = this->fps;
	other->invFps = this->invFps;
	other->updateTime = this->updateTime;
	other->isPlay = this->isPlay;
	other->isLoop = this->isLoop;
	other->currentIndex = this->currentIndex;
	other->currentFrame = this->currentFrame;
	other->imageKey = this->imageKey;
	other->SetFrameImage(other->imageKey);
}

AnimationClip::AnimationClip()
	: isPlay(true), isLoop(false), fps(60.f), updateTime(0.f), currentIndex(0)
{
	invFps = 1.f / fps;
}

AnimationClip::~AnimationClip()
{
}

void AnimationClip::Uptate()
{
	if (isPlay)
	{
		updateTime += TickTime;
		if (updateTime >= invFps)
		{
			updateTime -= invFps;
			currentIndex++;
			if (currentIndex >= frames.size())
			{
				currentIndex = 0;

				if (!isLoop)
				{
					isPlay = false;
					return;
				}
			}

			currentFrame = frames[currentIndex];

			if (currentFrame.callBacks.size() > 0)
			{
				for (int i = 0; i < (int)currentFrame.callBacks.size(); i++)
				{
					callBackFuncTable[currentFrame.callBacks[i]]();
				}
			}
		}
	}

}

void AnimationClip::Redner(FloatRect rc, Matrix2D* world, float alpha)
{
	if (texture)
	{
		texture->FrameRender(rc, world, currentFrame.FrameX, currentFrame.FrameY, alpha);
	}
}

void AnimationClip::Init()
{
	currentFrame = frames[0];
}

void AnimationClip::Stop()
{
	isPlay = false;
	currentIndex = 0;
	currentFrame = frames[0];
}

void AnimationClip::Pause()
{
	isPlay = false;
}

void AnimationClip::Play()
{
	isPlay = true;
}

void AnimationClip::PushBackFrame(pair<int, int> frame)
{
	frames.push_back(AniFrame(frame));
}

void AnimationClip::PushBackFrame(vector<pair<int, int>> frames)
{
	for (int i = 0;i < (int)frames.size(); i++)
	{
		PushBackFrame(frames[i]);
	}
}

void AnimationClip::PushBackFrame(int x, int y)
{
	frames.push_back(AniFrame(x, y));
}

void AnimationClip::PushBackFrame(int startX, int startY, int endX, int endY, bool reverse, bool axisX)
{
	if (axisX)
	{
		if (reverse)
		{
			for (int y = endY; y >= startY; y--)
			{
				for (int x = endX; x >= startX; x--)
				{
					PushBackFrame(x, y);
				}
			}
		}
		else
		{
			for (int y = startY; y <= endY; y++)
			{
				for (int x = startX; x < endX; x++)
				{
					PushBackFrame(x, y);
				}
			}
		}
	}
	else
	{
		if (reverse)
		{
			for (int x = endX; x >= startX; x--)
			{
				for (int y = endY; y >= startY; y--)
				{
					PushBackFrame(x, y);
				}
			}
		}
		else
		{
			for (int x = startX; x <= endX; x++)
			{
				for (int y = startY; y < endY; y++)
				{
					PushBackFrame(x, y);
				}
			}

		}
	}
}

void AnimationClip::PushBackAniFrame(AniFrame aniframe)
{
	frames.push_back(aniframe);
}

void AnimationClip::RegisterAniFrameCallBack(int index, string name)
{
	frames[index].AddCallBack(name);
}

void AnimationClip::RegisterAniFrameCallBack(int index, string name[])
{
	frames[index].AddCallBack(name);
}

void AnimationClip::RegisterAniFrameCallBack(int index[], string name)
{
	for(int i = 0; i < _ARRAYSIZE(index);i ++)
	{
		frames[i].AddCallBack(name);
	}
}

void AnimationClip::RegisterAniFrameCallBack(int index[], string name[])
{
	for (int i = 0; i < _ARRAYSIZE(index);i++)
	{
		frames[i].AddCallBack(name);
	}
}

void AnimationClip::SetFrameImage(string image)
{
	imageKey = image;
	texture = _ImageManager->FindTexture(imageKey);
}

void AnimationClip::SetFps(float val)
{
	val > 0.5f ? fps = val : fps = 0.5f; 
	fps = val;
	invFps = 1.f / fps;
}

void AnimationClip::SetLoop(bool loop)
{
	isLoop = loop;
}

void AnimationClip::RegisterCallBackTable(string name, CallBackFunc func)
{
	callBackFuncTable.insert(make_pair(name, func));
}

void AnimationClip::DeleteCallBackTable(string name)
{
	unordered_map<string, CallBackFunc>::iterator Iter = callBackFuncTable.find(name);
	if (Iter != callBackFuncTable.end())
	{
		callBackFuncTable.erase(Iter);
	}
}
