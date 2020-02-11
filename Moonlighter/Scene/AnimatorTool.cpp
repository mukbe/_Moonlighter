#include "stdafx.h"
#include "AnimatorTool.h"


AnimatorTool::AnimatorTool()
{
	selectedAnim = -1;
	selectedClip = -1;
	currentClip = nullptr;
}


AnimatorTool::~AnimatorTool()
{
	for (Animator* ani : animator)
		SafeDelete(ani);
}

void AnimatorTool::Init()
{
	animator.push_back(new Animator);
	animator[0]->name = "Temp asfsad";
	animator[0]->AddAnimation("Test clip1", new AnimationClip);
	animator[0]->AddAnimation("Test clip2", new AnimationClip);

}

void AnimatorTool::ImguiRender()
{
	SceneBase::ImguiRender();

	static bool aniOpen = true;
	ImGuiWindowFlags win_flag = 0;
	win_flag |= ImGuiWindowFlags_MenuBar;
	ImGui::SetNextWindowPos(ImVec2(0.f, 0.f));
	ImGui::SetNextWindowSize(ImVec2(WinSizeX * 0.25f, WinSizeY));
	ImGui::Begin("Animator", &aniOpen, win_flag);

	CreateMenuBar();
	ImGui::BeginGroup();
	if (ImGui::Button("Add Animator", ImVec2(100, 20)))
	{
		ImGui::OpenPopup("Add Anim");
	} ImGui::SameLine();
	if (ImGui::Button("Add Clip", ImVec2(100, 20)))
	{
		ImGui::OpenPopup("Add Clip");
	}
	ImGui::Separator();


	ImGui::EndGroup();


	ImGuiWindowFlags pop_anim_flag = 0;
	pop_anim_flag |= ImGuiWindowFlags_NoMove;
	if (ImGui::BeginPopup("Add Anim", pop_anim_flag))
	{
		static char buf[128];
		ImGuiInputTextFlags flag = 0;
		flag |= ImGuiInputTextFlags_EnterReturnsTrue;
		if (ImGui::InputText("Animator Name", buf, ARRAYSIZE(buf), flag))
		{
			animator.push_back(new Animator);
			animator[animator.size() - 1]->name = buf;
			ZeroMemory(buf, 128);
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}

	if (ImGui::BeginPopup("Add Clip", pop_anim_flag))
	{
		static char buf[128];
		ImGuiInputTextFlags flag = 0;
		flag |= ImGuiInputTextFlags_EnterReturnsTrue;
		if (ImGui::InputText("Clip Name", buf, ARRAYSIZE(buf), flag))
		{
			if (selectedAnim != -1)
			{
				animator[selectedAnim]->AddAnimation(buf, new AnimationClip);
				ZeroMemory(buf, 128);
			}
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}

	vector<int> deleteList;
	for (int i = 0;i < (int)animator.size(); i++)
	{
		Animator* anim = animator[i];

		//bool is_selected = (selection_mask & (1 << i)) != 0;
		ImGuiTreeNodeFlags tree_flag = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_DefaultOpen;
		if (selectedAnim == i)
		{
			tree_flag |= ImGuiTreeNodeFlags_Selected;
		}

		if( ImGui::TreeNodeEx((void*)i, tree_flag, anim->name.c_str()))
		{

			if (ImGui::IsItemClicked())
			{
				selectedAnim = i;
				selectedClip = -1;
				currentClip = nullptr;
			}
			if (ImGui::IsItemClicked(1))
			{
				selectedAnim = i;
				selectedClip = -1;
				currentClip = nullptr;
				ImGui::OpenPopup("Animator Menu");
			}
			if (ImGui::BeginPopup("Animator Menu", pop_anim_flag))
			{
				if (ImGui::MenuItem("Save as"))
				{
					Path::SaveFileDialog(L"", Path::AnimationFilter, ResourcePath + L"Animator/", [&](wstring name) {
						AnimatorTool::SaveAnimatorBinary(animator[selectedAnim], name);
					});
				}
				if (ImGui::MenuItem("Save"))
				{
					AnimatorTool::SaveAnimatorBinary(animator[selectedAnim], ResourcePath + L"Animator/" + String::StringToWString(animator[selectedAnim]->name));
				}
				if (ImGui::MenuItem("Delete"))
				{
					deleteList.push_back(selectedAnim);
				}
				
				static char buf[128];
				ImGuiInputTextFlags flag = 0;
				flag |= ImGuiInputTextFlags_EnterReturnsTrue;
				if (ImGui::InputText("Animator Name", buf, ARRAYSIZE(buf), flag))
				{
					if (selectedAnim != -1)
					{
						animator[selectedAnim]->name = buf;
						ZeroMemory(buf, 128);
					}
					ImGui::CloseCurrentPopup();
				}

				

				ImGui::EndPopup();
			}


			
			vector<pair<string, AnimationClip*>>::iterator Iter = anim->animations.begin();
			int count = 0;
			for (; Iter != anim->animations.end(); ++Iter, count++)
			{
				AnimationClip* clip = Iter->second;
				bool clip_selected = (selectedAnim == i) && (selectedClip == count);
				ImGui::Selectable(Iter->first.c_str(), &clip_selected);
				if (ImGui::IsItemClicked(0))
				{
					selectedAnim = i;
					selectedClip = count;
				}
				if (ImGui::IsItemClicked(1))
				{
					selectedAnim = i;
					selectedClip = count;
					ImGui::OpenPopup("AnimatorClip Menu");
				}
			}

			if (ImGui::BeginPopup("AnimatorClip Menu", pop_anim_flag))
			{

				if (ImGui::MenuItem("Delete"))
				{
					SafeDelete(animator[selectedAnim]->animations.at(selectedClip).second);
					animator[selectedAnim]->animations.erase(animator[selectedAnim]->animations.begin() + selectedClip);
					selectedClip = -1;
					currentClip = nullptr;
					ImGui::CloseCurrentPopup();
				}


				static char buf[128];
				ImGuiInputTextFlags flag = 0;
				flag |= ImGuiInputTextFlags_EnterReturnsTrue;
				if (ImGui::InputText("AnimatorClip Name", buf, ARRAYSIZE(buf), flag))
				{
					animator[selectedAnim]->animations[selectedClip].first = buf;
					ZeroMemory(buf, 128);
					ImGui::CloseCurrentPopup();
				}
				ImGui::EndPopup();
			}


			
			ImGui::TreePop();

		}
	}



	ImGui::Separator();
	ImGui::Text("selectedAnim %d", selectedAnim);
	if (deleteList.empty() == false)
	{
		SafeDelete(animator[deleteList[0]]);
		animator.erase(animator.begin() + deleteList[0]);
		selectedAnim = -1;
		selectedClip = -1;
		currentClip = nullptr;
	}

	ImGui::End();
	ShowAnimation();
}

void AnimatorTool::Update(float tick)
{
	SceneBase::Update(tick);

	if (currentClip != nullptr)
	{
		currentClip->Uptate();
	}
}

void AnimatorTool::CreateMenuBar()
{
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("Menu"))
		{
			if (ImGui::MenuItem("Save", "Ctrl+S")) 
			{
				for (Animator* anim : animator)
				{
					AnimatorTool::SaveAnimatorBinary(anim, ResourcePath + L"Animator/" + String::StringToWString(anim->name));
				}
			}
			if (ImGui::MenuItem("Load", "Ctrl+L"))
			{
				WCHAR path[64] = L"../_Resources/Animator";
				Path::FileSearch(path, [&](wstring file) {
					LoadAnimatorBinary(file);
				});
			}
			ImGui::EndMenu();
		}


		if (ImGui::BeginMenu("Examples"))
		{
			//ImGui::MenuItem("Documents", NULL, &show_app_documents);
			ImGui::EndMenu();
		}


		ImGui::EndMenuBar();
	}
}

void AnimatorTool::ShowAnimation()
{
	if (selectedClip == -1) return;

	
	Animator* anim = animator[selectedAnim];
	AnimationClip* clip = nullptr;
	vector<pair<string, AnimationClip*>>::iterator Iter = anim->animations.begin();
	for (int count = 0; Iter != anim->animations.end(); ++Iter, count++)
	{
		if (selectedClip == count)
		{
			clip = Iter->second;
			break;
		}
	}
	currentClip = clip;
	clip->ImguiRender();

}

void AnimatorTool::SaveAnimatorBinary(Animator* anim, wstring name)
{
	BinaryWriter* w = new BinaryWriter();

	wstring path = name;
	if (String::Contain(name, L".anim") == false)
		path += L".anim";

	w->Open(path);
	{
		Animator::Save(anim, w);
	}
	w->Close();
}

void AnimatorTool::LoadAnimatorBinary(wstring name)
{
	Animator* anim = nullptr;
	Animator::Load(&anim, name);
	animator.push_back(anim);
}
