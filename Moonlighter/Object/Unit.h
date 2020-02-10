#pragma once

class Unit : public GameObject
{
	ClassInherited(GameObject)
public:
	Unit(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	~Unit();
protected:
	Animator* animator;

};

