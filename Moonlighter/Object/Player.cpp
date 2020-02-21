#include "stdafx.h"
#include "Player.h"
#include "./Object/State/StateBase.h"

Player::Player(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:Unit(name, pos, size)
{
	unitState.insert(make_pair("Idle", new StateIdle(this)));
	unitState.insert(make_pair("Move", new StateMove(this)));
	unitState.insert(make_pair("Sword", new StateSword(this)));
	unitState.insert(make_pair("Bow", new StateBow(this)));
	unitState.insert(make_pair("Roll", new StateRoll(this)));

	AddCallback("IsClick", [&](TagMessage msg) {
		Log_PrintF("sibal Ssibal %d", 111);
	});
	test = 0;
}


Player::~Player()
{
}


void Player::Init()
{
	Super::Init();

	ChangeState("Idle");

}

void Player::Release()
{
	Super::Release();

	
}

void Player::Update(float tick)
{
	if (test == 0)
		Super::Update(tick);

	//if (test == 1)
	//	transform.SetPos(CAMERA->GetMousePos());
}


void Player::Render()
{
	//_ImageManager->FindTexture("Back")->Render(FloatRect(D3DXVECTOR2(0, 0), D3DXVECTOR2(WinSizeX, WinSizeY), Pivot::LEFT_TOP), nullptr);

	Super::Render();
}

void Player::ImguiRender()
{
	//ImGui::Begin(u8"½Ã¹ß");
	//ImGui::Text("%d", animator->GetCurrentAnim()->GetCurrentFrameInfo().FrameX);
	//ImGui::End();
}

void Player::LoadAnimator()
{
	Animator::Load(&animator, ResourcePath + L"Animator/Player.anim");
	animator->ChangeAnimation("Idle_Down");
}

void Player::OnCollisionEnter(GameObject * other)
{
	int temp = static_cast<Player*>(other)->test;
	Log_Print("%d is collision Enter %d", test, temp);
}

void Player::OnCollisionStay(GameObject * other)
{
	int temp = static_cast<Player*>(other)->test;
	Log_Print("%d is collision Stay %d", test, temp);
	if (test == 0)
	{
		FloatRect origin = other->GetCollider();
		FloatRect otherRc = other->GetCollider();
		if (Math::IsAABBInAABBReaction(&otherRc, GetCollider()))
		{
			other->Transform().SetPos(other->Transform().GetPos() + D3DXVECTOR2(otherRc.left - origin.left, otherRc.top - origin.top));
		}
	}
}

void Player::OnCollisionExit(GameObject * other)
{
	int temp = static_cast<Player*>(other)->test;
	Log_Print("%d is collision Exit %d", test, temp);

}
