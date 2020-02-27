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
	unitState.insert(make_pair("Hit", new StateHit(this)));

	iff = IFFEnum_Player;




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
	Super::Update(tick);

}


void Player::Render()
{
	//_ImageManager->FindTexture("Back")->Render(FloatRect(D3DXVECTOR2(0, 0), D3DXVECTOR2(WinSizeX, WinSizeY), Pivot::LEFT_TOP), nullptr);

	Super::Render();
}

void Player::ImguiRender()
{
	//ImGui::Begin(u8"시발");
	//ImGui::Text("%d", animator->GetCurrentAnim()->GetCurrentFrameInfo().FrameX);
	//ImGui::End();
}

void Player::LoadAnimator()
{
	Animator::Load(&animator, ResourcePath + L"Animator/Player.anim");
	animator->ChangeAnimation("Idle_Down");

	function<void(D3DXVECTOR2)> arrow = [&](D3DXVECTOR2 dir) {
		D3DXVECTOR2 range = { 15.f,15.f };
		D3DXVECTOR2 startPos = transform.GetPos() + dir * 15.f;
		if (Math::Abs(dir.x) >= 1.f)
		{
			range.y = 3.f;
			//startPos.y -= size.y*0.5f;
		}
		if (Math::Abs(dir.y) >= 1.f)
		{
			range.x = 3.f;

		}

		_BulletSystem->Fire(startPos, range, 1.f, 10, "Bullet_Arrow", direction, IFFEnum::IFFEnum_Player, dir * 400.f, "Arrow");

	};
	function<void(D3DXVECTOR2,string)> sword = [&](D3DXVECTOR2 dir, string effect) {
		D3DXVECTOR2 startPos = transform.GetPos() + dir * 15.f;
		//startPos.y -= size.y *0.6f;



		_BulletSystem->Fire(startPos, 25, 0.1f, 20, "", direction, IFFEnum::IFFEnum_Player,D3DXVECTOR2(0.f,0.f), effect);
	};

	animator->FindAnimation("Bow_Up")->RegisterCallBackTable("Arrow", bind(arrow, D3DXVECTOR2(0, -1)));
	animator->FindAnimation("Bow_Right")->RegisterCallBackTable("Arrow", bind(arrow, D3DXVECTOR2(1, 0)));
	animator->FindAnimation("Bow_Down")->RegisterCallBackTable("Arrow", bind(arrow, D3DXVECTOR2(0, 1)));
	animator->FindAnimation("Bow_Left")->RegisterCallBackTable("Arrow", bind(arrow, D3DXVECTOR2(-1, 0)));

	animator->FindAnimation("Sword_Up")->RegisterCallBackTable("Sword1", bind(sword, D3DXVECTOR2(0, -1),"Sword1"));
	animator->FindAnimation("Sword_Right")->RegisterCallBackTable("Sword1", bind(sword, D3DXVECTOR2(1, 0), "Sword1"));
	animator->FindAnimation("Sword_Down")->RegisterCallBackTable("Sword1", bind(sword, D3DXVECTOR2(0, 1), "Sword1"));
	animator->FindAnimation("Sword_Left")->RegisterCallBackTable("Sword1", bind(sword, D3DXVECTOR2(-1, 0), "Sword1"));

	animator->FindAnimation("Sword_Up")->RegisterCallBackTable("Sword2", bind(sword, D3DXVECTOR2(0, -1), "Sword2"));
	animator->FindAnimation("Sword_Right")->RegisterCallBackTable("Sword2", bind(sword, D3DXVECTOR2(1, 0), "Sword2"));
	animator->FindAnimation("Sword_Down")->RegisterCallBackTable("Sword2", bind(sword, D3DXVECTOR2(0, 1), "Sword2"));
	animator->FindAnimation("Sword_Left")->RegisterCallBackTable("Sword2", bind(sword, D3DXVECTOR2(-1, 0), "Sword2"));


}

void Player::Knockback(D3DXVECTOR2 dir)
{
	if (currentState->Name() == "StateRoll")
		return;
	ChangeState("Hit");
	((StateHit*)currentState)->SetDir(dir);
}

void Player::Damge(float dmg)
{
	if (currentState->Name() == "StateRoll")
		return;
	//데미지 처리

}

void Player::OnCollisionEnter(GameObject * other)
{

}

void Player::OnCollisionStay(GameObject * other)
{
	FloatRect origin = other->GetCollider();
	FloatRect otherRc = other->GetCollider();
	if (Math::IsAABBInAABBReaction(&otherRc, GetCollider()) 
		&& other->GetCollisionType() == CollisionType_Dynamic 
		&& currentState->Name() != "StateRoll"
		&& other->Name() != "Bullet"
		&& other->GetIFF() != IFFEnum_Monster)
	{
		other->Transform().SetPos(other->Transform().GetPos() + D3DXVECTOR2(otherRc.left - origin.left, otherRc.top - origin.top));
	}
	
	if (KeyCode->Down('F'))
	{
		other->PlayerInteractions();
	}

}

void Player::OnCollisionExit(GameObject * other)
{

}
