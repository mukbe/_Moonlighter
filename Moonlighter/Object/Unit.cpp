#include "stdafx.h"
#include "Unit.h"
#include "./Object/State/StateBase.h"


Unit::Unit(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:GameObject(name, pos, size)
{
	direction = UnitDirection::Down;
	currentState = nullptr;
	shadowTex = _ImageManager->FindTexture("Shadow");
}


Unit::~Unit()
{
}

void Unit::Init()
{
	Super::Init();
	LoadAnimator();
}

void Unit::Release()
{
	Super::Release();

	SafeDelete(animator);

}

void Unit::Update(float tick)
{
	Super::Update(tick);


	if (currentState)
		currentState->Excute();

	animator->Update();

}

void Unit::Render()
{
	Super::Render();
	
	shadowTex->Render(rc, &transform, 0.3f);
	animator->Render(renderRect, &transform, alpha);

}

void Unit::ImguiRender()
{

}

void Unit::ChangeState(string stateName)
{
	if(currentState)
		currentState->Exit();

	currentState = unitState[stateName];
	currentState->Enter();
}

string Unit::GetStringUnitDirection()
{
	return GetStringDirection(direction);
}

void Unit::SetDirection(UnitDirection dir)
{
	direction = dir;
}
