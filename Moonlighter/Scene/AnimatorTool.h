#pragma once
class AnimatorTool : public SceneBase
{
public:
	AnimatorTool();
	~AnimatorTool();
	virtual void Init();
	virtual void ImguiRender();

	virtual void Update(float tick);

	void CreateMenuBar();
	void ShowAnimation();

	void SaveAnimatorBinary(Animator* anim, wstring name);
	void LoadAnimatorBinary(wstring name);
private:
	vector<Animator*> animator;
	int selectedAnim;
	int selectedClip;
	AnimationClip* currentClip;
};

