#pragma once

class StateBase;
class Unit : public GameObject
{
	ClassInherited(GameObject)
public:
	Unit(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	~Unit();

	//�ʱ�ȭ
	virtual void Init();
	//�޸� ����
	virtual void Release();
	//���� ��ƾ
	virtual void Update(float tick);

	virtual void Render();
	//imgui debugUI render
	virtual void ImguiRender();


	virtual void LoadAnimator() {}

	Animator* GetAnimator() { return animator; }
	void ChangeState(string stateName);
	string GetStringUnitDirection();
	void SetDirection(UnitDirection dir);
protected:
	Animator* animator;
	UnitDirection direction;

	unordered_map<string, StateBase*> unitState;
	StateBase* currentState;
	shared_ptr<Texture> shadowTex;
};

