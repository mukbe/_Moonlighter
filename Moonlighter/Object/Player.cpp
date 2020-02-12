#include "stdafx.h"
#include "Player.h"


Player::Player(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:Unit(name, pos, size)
{



}


Player::~Player()
{
}


void Player::Init()
{
	Super::Init();
	CreateAnimation();
	Animator::Load(&animator, ResourcePath + L"Animator/Player.anim");
	animator->ChangeAnimation("Move_Down");


}

void Player::Release()
{
	Super::Release();

	SafeDelete(animator);
	
}

void Player::Update(float tick)
{
	Super::Update(tick);


	if (KeyCode->Press(VK_LEFT))
		animator->ChangeAnimation("Move_Left");
	else if(KeyCode->Press(VK_RIGHT))
		animator->ChangeAnimation("Move_Right");
	else if (KeyCode->Press(VK_UP))
		animator->ChangeAnimation("Move_Up");
	else if (KeyCode->Press(VK_DOWN))
		animator->ChangeAnimation("Move_Down");

	if (KeyCode->Up(VK_LEFT))
		animator->ChangeAnimation("Idle_Left");
	else if (KeyCode->Up(VK_RIGHT))
		animator->ChangeAnimation("Idle_Right");
	else if (KeyCode->Up(VK_UP))
		animator->ChangeAnimation("Idle_Up");
	else if (KeyCode->Up(VK_DOWN))
		animator->ChangeAnimation("Idle_Down");

	animator->Update();
}


void Player::Render()
{
	Super::Render();
	animator->Render(rc, &transform, alpha);
}

void Player::ImguiRender()
{
	ImGui::Begin(u8"½Ã¹ß");
	ImGui::Text("%d", animator->GetCurrentAnim()->GetCurrentFrameInfo().FrameX);
	ImGui::End();
}

void Player::CreateAnimation()
{

}

