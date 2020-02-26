#include "stdafx.h"
#include "Unit.h"
#include "./Object/State/StateBase.h"


Unit::Unit(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:GameObject(name, pos, size)
{
	direction = UnitDirection::Down;
	currentState = nullptr;
	shadowTex = _ImageManager->FindTexture("Shadow");

	AddCallback("Knockback", [&](TagMessage msg) {
		Knockback(msg.Data->GetValue <D3DXVECTOR2>());
	});

	AddCallback("Damge", [&](TagMessage msg) {
		Damge(msg.Data->GetValue<float>());
	});

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
	
	animator->Render(renderRect, &transform, alpha);

	if (SceneBase::DebugMode)
	{
		p2DRenderer->DrawEllipse(FloatRect(D3DXVECTOR2(0, 0), detectRange*2.f, Pivot::CENTER), &transform, DefaultBrush::yello);
		p2DRenderer->DrawEllipse(FloatRect(D3DXVECTOR2(0, 0), attackRange*2.f, Pivot::CENTER), &transform, DefaultBrush::yello);
	}
}

void Unit::ImguiRender()
{

}

void Unit::ChangeState(string stateName)
{

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
