#pragma once
class AnimatorTool : public SceneBase
{
public:
	AnimatorTool();
	~AnimatorTool();
	virtual void Init();
	virtual void ImguiRender();

	virtual void Update();

	void CreateMenuBar();
	void ShowAnimation();
private:
	vector<Animator*> animator;
	int selectedAnim;
	int selectedClip;
	AnimationClip* currentClip;
};

