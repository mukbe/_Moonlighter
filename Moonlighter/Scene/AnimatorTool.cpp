#include "stdafx.h"
#include "AnimatorTool.h"



AnimatorTool::AnimatorTool()
{
	selectedAnim = -1;
	selectedClip = -1;
}


AnimatorTool::~AnimatorTool()
{
}

void AnimatorTool::Init()
{
}

void AnimatorTool::ImguiRender()
{
	SceneBase::ImguiRender();

	static bool aniOpen = true;
	ImGuiWindowFlags win_flag = 0;
	win_flag |= ImGuiWindowFlags_MenuBar;
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


	if (ImGui::BeginPopup("Add Anim"))
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
	if (ImGui::BeginPopup("Add Clip"))
	{
		static char buf[128];
		ImGuiInputTextFlags flag = 0;
		flag |= ImGuiInputTextFlags_EnterReturnsTrue;
		if (ImGui::InputText("Animator Name", buf, ARRAYSIZE(buf), flag))
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


	for (int i = 0;i < (int)animator.size(); i++)
	{
		Animator* anim = animator[i];

		//bool is_selected = (selection_mask & (1 << i)) != 0;
		ImGuiTreeNodeFlags tree_flag = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick;
		if (selectedAnim == i)
		{
			tree_flag |= ImGuiTreeNodeFlags_Selected;
		}

		if (ImGui::TreeNodeEx((void*)i, tree_flag, anim->name.c_str()))
		{
			if (ImGui::IsItemClicked())
				selectedAnim = i;
			{
				unordered_map<string, AnimationClip*>::iterator Iter = anim->animations.begin();
				int count = 0;
				for (; Iter != anim->animations.end(); ++Iter, count++)
				{
					AnimationClip* clip = Iter->second;
					bool clip_selected = (selectedAnim == i) && (selectedClip == count);
					ImGui::Selectable(Iter->first.c_str(),&clip_selected);
					if (ImGui::IsItemClicked())
					{
						selectedAnim = i;
						selectedClip = count;
					}
				}

			}

		ImGui::TreePop();
		}
	}



	ImGui::Text("selectedAnim %d", selectedAnim);


	ImGui::End();


	ShowAnimation();
}

void AnimatorTool::Update()
{
	SceneBase::Update(TickTime);

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


			ImGui::EndMenu();
		}


		if (ImGui::BeginMenu("Examples"))
		{
			//ImGui::MenuItem("Main menu bar", NULL, &show_app_main_menu_bar);
			//ImGui::MenuItem("Console", NULL, &show_app_console);
			//ImGui::MenuItem("Log", NULL, &show_app_log);
			//ImGui::MenuItem("Simple layout", NULL, &show_app_layout);
			//ImGui::MenuItem("Property editor", NULL, &show_app_property_editor);
			//ImGui::MenuItem("Long text display", NULL, &show_app_long_text);
			//ImGui::MenuItem("Auto-resizing window", NULL, &show_app_auto_resize);
			//ImGui::MenuItem("Constrained-resizing window", NULL, &show_app_constrained_resize);
			//ImGui::MenuItem("Simple overlay", NULL, &show_app_simple_overlay);
			//ImGui::MenuItem("Manipulating window titles", NULL, &show_app_window_titles);
			//ImGui::MenuItem("Custom rendering", NULL, &show_app_custom_rendering);
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
	unordered_map<string, AnimationClip*>::iterator Iter = anim->animations.begin();
	for (int count = 0; Iter != anim->animations.end(); ++Iter, count++)
	{
		if (selectedClip == count)
		{
			clip = Iter->second;
			break;
		}
	}


}
