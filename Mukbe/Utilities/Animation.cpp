#include "Mukbe.h"
#include "Animation.h"



void AnimationClip::Save(AnimationClip * clip, BinaryWriter * w)
{
	w->Float(clip->fps);
	w->Bool(clip->isLoop);
	w->String(clip->imageKey);
	w->Int(clip->maxFrame[0]);
	w->Int(clip->maxFrame[1]);

	//프레임저장
	w->Int((int)clip->frames.size());
	for (int i = 0; i < (int)clip->frames.size(); i++)
	{
		AniFrame temp = clip->frames[i];
		w->Int(temp.FrameX);
		w->Int(temp.FrameY);
		w->Int((int)temp.callBacks.size());
		for (int j = 0; j < (int)temp.callBacks.size(); j++)
		{
			w->String(temp.callBacks[j]);
		}

	}

}

void AnimationClip::Load(AnimationClip ** ppClip, BinaryReader * r)
{
	AnimationClip* clip = new AnimationClip();
	clip->fps = r->Float();
	clip->isLoop = r->Bool();
	clip->imageKey = r->String();
	clip->maxFrame[0] = r->Int();
	clip->maxFrame[1] = r->Int();

	int frameCount = r->Int();

	for (int i = 0; i < frameCount; i++)
	{
		AniFrame temp;
		temp.FrameX = r->Int();
		temp.FrameY = r->Int();
		int callBacksCount = r->Int();
		for (int j = 0; j < callBacksCount; j++)
		{
			temp.AddCallBack(r->String());
		}
		clip->PushBackAniFrame(temp);
	}



#ifdef DEBUGMODE
	Log_ErrorAssert(_ImageManager->FindTexture(clip->imageKey) == false);
#else
	clip->texture = _ImageManager->FindTexture(clip->imageKey);
#endif // DEBUGMODE

	clip->invFps = 1.f / clip->fps;

	*ppClip = clip;
}

void AnimationClip::Clone(void** clone)
{
	*clone = new AnimationClip;
	AnimationClip* other = reinterpret_cast<AnimationClip*>(*clone);
	other->callBackFuncTable = this->callBackFuncTable;
	other->frames = this->frames;
	other->fps = this->fps;
	other->invFps = this->invFps;
	other->updateTime = this->updateTime;
	other->isLoop = this->isLoop;
	other->currentIndex = this->currentIndex;
	other->currentFrame = this->currentFrame;
	other->imageKey = this->imageKey;
	memcpy_s(other->maxFrame, sizeof(int) * 2, this->maxFrame, sizeof(int) * 2);
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
			if (currentIndex >= (int)frames.size())
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
					if(callBackFuncTable[currentFrame.callBacks[i]])
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

void AnimationClip::ImguiRender()
{
#ifdef USEIMGUI
	ImGuiWindowFlags window_flag;
	window_flag |= ImGuiWindowFlags_NoMove;
	window_flag |= ImGuiWindowFlags_NoTitleBar;
	ImGui::SetNextWindowPos(ImVec2(WinSizeX * 0.25f, 0.f));
	ImGui::SetNextWindowSize(ImVec2(WinSizeX * 0.6f, WinSizeY ));
	static bool bOpen = true;

	ImGui::Begin("Ani Frame Info", &bOpen);
	if (ImGui::Button("Set Texture", ImVec2(100, 40)))
	{
		D3DDesc desc;
		pRenderer->GetDesc(&desc);
		Path::OpenFileDialog(L"", Path::ImageFilter, ResourcePath, [&](wstring path) {
			wstring nameW = Path::GetFileNameWithoutExtension(path);
			string name = String::WStringToString(nameW);
			_ImageManager->AddTexture(name, path);
			texture = _ImageManager->FindTexture(name);
			maxFrame[0] = maxFrame[1] = 1;
			imageKey = name;
		}, desc.Handle);
	}
	ImGuiInputTextFlags input_flag = ImGuiInputTextFlags_EnterReturnsTrue;
	if (ImGui::InputInt2("Max Frame", maxFrame, input_flag))
	{
		
	}

	if (texture)
	{
		ImGui::Text("File Path %s", texture->GetFilePath().c_str());
		ImGui::Text("Image Key %s", imageKey.c_str());


		ImVec2 size = ImGui::GetWindowSize();
		ImGuiIO& io = ImGui::GetIO();

		if (drag_save_frame.empty())
			pickedFrame = { 0.f, 0.f };
		else
			pickedFrame = { (float)drag_save_frame[0].first, (float)drag_save_frame[0].second };


		ImGui::Image(texture->GetSRV()
			, ImVec2(size.x * 0.4f, 300)
			, ImVec2(pickedFrame.x / maxFrame[0], pickedFrame.y / maxFrame[1])
			, ImVec2((pickedFrame.x + 1.f )/ maxFrame[0], (pickedFrame.y + 1.f) / maxFrame[1])); 
		ImGui::SameLine();

		ImVec2 pos = ImGui::GetCursorScreenPos();
		ImGui::Image(texture->GetSRV(), ImVec2(size.x * 0.4f, 300));

		if (drag_save_frame.empty() == false)
		{
			for (int i = 0; i < (int)drag_save_frame.size(); i++)
			{
				D3DXVECTOR2 drag_frame = { (float)drag_save_frame[i].first, (float)drag_save_frame[i].second };

				ImVec2 frame_Start = { ImGui::GetItemRectSize().x * drag_frame.x / maxFrame[0] + pos.x,ImGui::GetItemRectSize().y *drag_frame.y / maxFrame[1] + pos.y };
				ImVec2 frame_End = { ImGui::GetItemRectSize().x * (drag_frame.x + 1.f) / maxFrame[0] + pos.x ,ImGui::GetItemRectSize().y * (drag_frame.y + 1.f) / maxFrame[1] + pos.y };

				ImGui::GetWindowDrawList()->AddRect(frame_Start, frame_End, IM_COL32(0, 255, 255, 255));

			}
		}

		if (ImGui::IsMouseClicked(0) && ImGui::IsItemClicked())
		{
			clicked_start.x = io.MousePos.x - pos.x;
			clicked_start.y = io.MousePos.y - pos.y;
		}

		if (ImGui::IsMouseReleased(1) && ImGui::IsItemHovered())
		{
			drag_save_frame.clear();
		}

		ImVec2 drag_start = { clicked_start.x + pos.x, clicked_start.y + pos.y };
		if (ImGui::IsMouseDragging(0) && ImGui::IsItemHovered())
		{
			ImGui::GetWindowDrawList()->AddRect(drag_start, io.MousePos, IM_COL32(0, 255, 255, 255));

			ImGui::Text("%.2f, %.2f", drag_start.x, drag_start.y);
			ImGui::Text("%.2f, %.2f", io.MousePos.x, io.MousePos.y);
		}

		if (ImGui::IsMouseReleased(0) && ImGui::IsItemHovered())
		{
			drag_save_frame.clear();

			clicked_end.x = io.MousePos.x - pos.x;
			clicked_end.y = io.MousePos.y - pos.y;

			pickedFrame.x = (int)(clicked_start.x / ImGui::GetItemRectSize().x * (float)maxFrame[0]);
			pickedFrame.y = (int)(clicked_start.y / ImGui::GetItemRectSize().y * (float)maxFrame[1]);

			D3DXVECTOR2 pickend;
			pickend.x = (int)(clicked_end.x / ImGui::GetItemRectSize().x * (float)maxFrame[0]);
			pickend.y = (int)(clicked_end.y / ImGui::GetItemRectSize().y * (float)maxFrame[1]);

			function<void(float*, float*)> Swap_Position = [&](float* start, float* end)
			{
				if (*start > *end)
				{
					float temp = *start;
					*start = *end;
					*end = temp;
				}
			};
			Swap_Position(&pickedFrame.x, &pickend.x);
			Swap_Position(&pickedFrame.y, &pickend.y);

			for (int y = (int)pickedFrame.y; y <= (int)pickend.y; y++)
			{
				for (int x = (int)pickedFrame.x; x <= (int)pickend.x; x++)
				{
					drag_save_frame.push_back(make_pair(x, y));
				}
			}
		}

		if (ImGui::Button("Add AniFrame", ImVec2(120, 20)))
		{
			PushBackFrame(drag_save_frame);
		} ImGui::SameLine();
		if (ImGui::Button("Reverse Add AniFrame", ImVec2(200, 20)))
		{
			vector<pair<int, int>> temp;
			for (int i = (int)drag_save_frame.size() - 1;i >= 0; i--)
			{
				temp.push_back(drag_save_frame[i]);
			}
			PushBackFrame(temp);
		}

		ImVec2 child_size = ImGui::GetWindowSize();
		child_size.x *= 0.25f;
		child_size.y *= 0.25f;

		ImGui::BeginChild("Ani Frame Child", child_size);

		if (ImGui::ArrowButton("Up Frame", ImGuiDir_Up))
		{
			if (current_item != -1 && current_item != 0)
			{
				AniFrame temp = frames[current_item];
				frames[current_item] = frames[current_item - 1];
				frames[current_item - 1] = temp;
				current_item--;
			}
		} ImGui::SameLine();
		if (ImGui::ArrowButton("Down Frame", ImGuiDir_Down))
		{
			if (current_item != -1 && current_item != (int)frames.size() - 1)
			{
				AniFrame temp = frames[current_item];
				frames[current_item] = frames[current_item + 1];
				frames[current_item + 1] = temp;
				current_item++;
			}
		} ImGui::SameLine();
		if (ImGui::Button("Delete Frame", ImVec2(120, 20)))
		{
			if (current_item != -1)
			{
				frames.erase(frames.begin() + current_item);
				current_item = -1;
				current_item_callback = -1;
			}
		} ImGui::SameLine();
		if (ImGui::Button("Clear Frame", ImVec2(120, 20)))
		{
			frames.clear();
		}
		for (int i = 0; i < (int)frames.size(); i++)
		{
			string str = to_string(i) + ". Frame < " + to_string(frames[i].FrameX) + " , " + to_string(frames[i].FrameY) + " >";
			bool is_select = ImGui::Selectable(str.c_str(), current_item == i);

			if (is_select)
			{
				current_item = i;
				current_item_callback = -1;
			}

		}
		ImGui::EndChild(); ImGui::SameLine();

		ImGui::BeginChild("Frame CallBack Child", child_size);

		if (current_item != -1)
		{
			AniFrame& aniframe = frames[current_item];

			if (ImGui::Button("Add CallBack", ImVec2(100, 20)))
			{
				ImGui::OpenPopup("Popup_Add_CallBack");
			}ImGui::SameLine();
			if (ImGui::Button("Delete CallBack", ImVec2(100, 20)))
			{
				if (current_item_callback != -1)
				{
					aniframe.callBacks.erase(aniframe.callBacks.begin() + current_item_callback);
					current_item_callback = -1;
				}
			}

			ImGuiWindowFlags pop_anim_flag = 0;
			pop_anim_flag |= ImGuiWindowFlags_NoMove;
			if (ImGui::BeginPopup("Popup_Add_CallBack", pop_anim_flag))
			{
				static char buf[128];
				ImGuiInputTextFlags flag = 0;
				flag |= ImGuiInputTextFlags_EnterReturnsTrue;
				if (ImGui::InputText("CallBack Name", buf, ARRAYSIZE(buf), flag))
				{
					aniframe.AddCallBack(buf);
					ZeroMemory(buf, 128);
					ImGui::CloseCurrentPopup();
				}
				ImGui::EndPopup();
			}

			for (int i = 0; i < (int)aniframe.callBacks.size(); i++)
			{
				bool is_select = ImGui::Selectable(aniframe.callBacks[i].c_str(), current_item_callback == i);

				if (is_select)
					current_item_callback = i;
			}
		}
		ImGui::EndChild(); ImGui::SameLine();
		
		ImGui::SetNextWindowSize(ImVec2(400,500));
		ImGui::BeginChild("Frame View Child", child_size);
		ImGui::Checkbox("IsPlay", &isPlay);
		ImGui::Checkbox("IsLoop", &isLoop);
		ImGui::SliderFloat("Frame_size", &aniFrame_size, 50.f, 300.f, "%.1f");

		if (ImGui::InputFloat("Frame Fps", &fps, 1.f, 5.f, 0, input_flag))
		{
			invFps = 1.f / fps;
		}
		
		ImGui::Image(texture->GetSRV()
			, ImVec2(aniFrame_size, aniFrame_size)
			, ImVec2((float)currentFrame.FrameX / maxFrame[0], (float)currentFrame.FrameY / maxFrame[1])
			, ImVec2(((float)currentFrame.FrameX + 1.f) / maxFrame[0], ((float)currentFrame.FrameY + 1.f) / maxFrame[1]));

		ImGui::Text("%d", currentFrame.FrameX);
		ImGui::EndChild();
	}


	ImGui::End();

#endif // USEIMGUI

}
