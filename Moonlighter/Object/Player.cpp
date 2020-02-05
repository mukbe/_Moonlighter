#include "stdafx.h"
#include "Player.h"


Player::Player(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:GameObject(name, pos, size)
{

	animator = new Animator;


}


Player::~Player()
{
}


void Player::Init()
{
	_ImageManager->AddFrameTexture("Player", ResourcePath + L"Player/will_dungeon.png", 10, 13);
	tex = _ImageManager->FindTexture("Player");
	frameX =  0;
	frameY = 11;

	AnimationClip* clip = new AnimationClip;
	clip->PushBackFrame(0, 3, 7, 3);
	clip->SetFrameImage("Player");
	clip->SetLoop(true);
	clip->SetFps(20.f);
	clip->RegisterCallBackTable("Walk_Left", []() {
		LOG->Print("Walk_Left");
	});
	animator->AddAnimation("Walk_Left", clip);

	clip = new AnimationClip;
	clip->PushBackFrame(0, 2, 7, 2);
	clip->SetFrameImage("Player");
	clip->SetLoop(true);
	clip->SetFps(20.f);
	clip->RegisterCallBackTable("Walk_Right", []() {
		LOG->Print("Walk_Right");
	});
	animator->AddAnimation("Walk_Right", clip);

	clip = new AnimationClip;
	clip->PushBackFrame(0, 0, 7, 0);
	clip->SetFrameImage("Player");
	clip->SetLoop(true);
	clip->SetFps(20.f);
	clip->RegisterCallBackTable("Walk_Up", []() {
		LOG->Print("Walk_Up");
	});
	animator->AddAnimation("Walk_Up", clip);

	clip = new AnimationClip;
	clip->PushBackFrame(0, 1, 7, 1);
	clip->SetFrameImage("Player");
	clip->SetLoop(true);
	clip->SetFps(20.f);
	clip->RegisterCallBackTable("Walk_Down", []() {
		LOG->Print("Walk_Down");
	});
	animator->AddAnimation("Walk_Down", clip);


	clip = new AnimationClip;
	clip->PushBackFrame(0, 11, 9, 11);
	clip->SetFrameImage("Player");
	clip->SetLoop(true);
	clip->SetFps(20.f);
	clip->RegisterCallBackTable("Idle_Down", []() {
		LOG->Print("Idle_Down");
	});
	animator->AddAnimation("Idle_Down", clip);

	clip = new AnimationClip;
	clip->PushBackFrame(0, 10, 9, 10);
	clip->SetFrameImage("Player");
	clip->SetLoop(true);
	clip->SetFps(20.f);
	clip->RegisterCallBackTable("Idle_Up", []() {
		LOG->Print("Idle_Up");
	});
	animator->AddAnimation("Idle_Up", clip);

	clip = new AnimationClip;
	clip->PushBackFrame(0, 8, 9, 8);
	clip->SetFrameImage("Player");
	clip->SetLoop(true);
	clip->SetFps(20.f);
	clip->RegisterCallBackTable("Idle_Right", []() {
		LOG->Print("Idle_Right");
	});
	animator->AddAnimation("Idle_Right", clip);

	clip = new AnimationClip;
	clip->PushBackFrame(0, 9, 9, 9);
	clip->SetFrameImage("Player");
	clip->SetLoop(true);
	clip->SetFps(20.f);
	clip->RegisterCallBackTable("Idle_Left", []() {
		LOG->Print("Idle_Left");
	});
	clip->RegisterAniFrameCallBack(0, "Idle_Left");
	animator->AddAnimation("Idle_Left", clip);




	animator->ChangeAnimation("Walk_Down");

	_RenderPool->Request(this, RenderManager::Layer::Object);
	_RenderPool->Request(this, RenderManager::Layer::Imgui);
}

void Player::Release()
{
	_RenderPool->Remove(this, RenderManager::Layer::Imgui);
	_RenderPool->Remove(this, RenderManager::Layer::Object);

	SafeDelete(animator);
	
}



void Player::Update(float tick)
{
	lifeTiem += tick;


	if (KeyCode->Press(VK_LEFT))
		animator->ChangeAnimation("Walk_Left");
	else if(KeyCode->Press(VK_RIGHT))
		animator->ChangeAnimation("Walk_Right");
	else if (KeyCode->Press(VK_UP))
		animator->ChangeAnimation("Walk_Up");
	else if (KeyCode->Press(VK_DOWN))
		animator->ChangeAnimation("Walk_Down");

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
	animator->Render(rc, &transform, alpha);
	//tex->FrameRender(rc, &transform, frameX, frameY, alpha);
}

void Player::ImguiRender()
{
	ImGui::Begin(u8"�ù�");
	ImGui::Text("%d", animator->GetCurrentAnim()->GetCurrentFrameInfo().FrameX);
	ImGui::End();
}

