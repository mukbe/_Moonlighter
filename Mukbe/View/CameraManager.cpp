#include "Mukbe.h"
#include "CameraManager.h"
#include "./Utilities/Matrix2D.h"
#include "./Render/ShaderBuffer.h"

SingletonCpp(CameraManager)

CameraManager::CameraManager()
	:target(nullptr)
{

	pos = D3DXVECTOR2(0.f,0.f);
	zoom = 1.f;
	view = Matrix2D(pos, D3DXVECTOR2(WinSizeX, WinSizeY), Pivot::LEFT_TOP);
	buffer = make_unique<CameraBuffer>();
	bShake = false;

	UpdateMatrix();
	cameraMode = Mode::Mode_Free;
	oldIndex = { 0,0 };
	targetPos = pos;

	saveTime = 0.f;
	boundRect = FloatRect(D3DXVECTOR2(WinSizeX*0.5f, WinSizeY*0.5f), D3DXVECTOR2(WinSizeX*0.3f, WinSizeY*0.3f), Pivot::CENTER);
	speed = 350.f;
	fade = Fade_None;
	bFadeComplete = true;
	fadeValue = 0.f;
	limitEndPos = { Math::FloatMax,Math::FloatMax };
}


CameraManager::~CameraManager()
{

}

void CameraManager::Update()
{
	switch (cameraMode)
	{
		case CameraManager::Mode::Mode_Free:
		{
			if (Mouse::Get()->Down(1))
			{
				memcpy(&picked, Mouse::Get()->GetPosition(), sizeof(D3DXVECTOR2));

				while (ShowCursor(FALSE) >= 0);
			}
			if (Mouse::Get()->Up(1))
			{
				while (ShowCursor(TRUE) <= 0);
				ClipCursor(NULL);
			}

			if (Mouse::Get()->Press(1))
			{

				ClipMouse();

				memcpy(&pick, Mouse::Get()->GetPosition(), sizeof(D3DXVECTOR2));

				D3DXVECTOR2 delta = picked - pick;
				pos += delta * zoom;

				memcpy(&picked, Mouse::Get()->GetPosition(), sizeof(D3DXVECTOR2));

				UpdateMatrix();
			}
		}
		break;
		case CameraManager::Mode::Mode_Target:
		{
			FloatRect targetCollider = WorldToScreenFloatRect(target->GetCollider());
			FloatRect temp;
			if (!Math::IsAABBInAABB(boundRect, targetCollider, &temp))
			{
				if (temp.GetSize().x != targetCollider.GetSize().x && temp.GetSize().y != targetCollider.GetSize().y)
				{
					D3DXVECTOR2 center = { WinSizeX * 0.5f, WinSizeY * 0.5f };
					D3DXVECTOR2 targetPos = { (targetCollider.left + targetCollider.right)*0.5f, (targetCollider.top + targetCollider.bottom)*0.5f };
					D3DXVECTOR2 delta = targetPos - center;
					float amount = D3DXVec2Length(&delta);
					amount *= 0.001f;
					Math::D3DXVector2Normalize(delta);
					
					pos += delta * TickTime * speed * zoom*amount;
				}
			}

			
			D3DXVECTOR2 end = ScreenToWorld(D3DXVECTOR2(WinSizeX, WinSizeY));
			if (pos.x <= 0) pos.x = 0.f;
			if (pos.y <= 0) pos.y = 0.f;
			
			if (end.x >= limitEndPos.x)
			{
				D3DXVECTOR2 offset = limitEndPos - (D3DXVECTOR2( WinSizeX, WinSizeY) / zoom);
				pos.x = offset.x * zoom;
			}
			if (end.y >= limitEndPos.y)
			{
				D3DXVECTOR2 offset = limitEndPos - (D3DXVECTOR2(WinSizeX, WinSizeY) / zoom);
				pos.y = offset.y * zoom;
			}

			UpdateMatrix();

		}
		break;
	}



	if (bShake)
	{
		if (shakeTime > 0)
		{
			shakeDir = Math::RandVec2();
			shakeTime -= Time::Tick();
		}
		else
		{
			UpdateMatrix();
			bShake = false;
		}



		ShakeUpdateMatrix();
	}

	switch (fade)
	{
	case CameraManager::Fade_None:
	{

	}
	break;
	case CameraManager::Fade_In:
	{
		bFadeComplete = false;

		fadeValue += 0.01f;
		fadeValue >= 1.f ? fadeValue = 1.f: fadeValue;
		buffer->SetFadeValue(fadeValue);

		if (fadeValue >= 1.f)
		{
			bFadeComplete = true;
			fade = Fade_None;
		}
	}
	break;
	case CameraManager::Fade_Out:
	{
		bFadeComplete = false;

		fadeValue -= 0.01f;
		fadeValue <= 0 ? fadeValue = 0.f : fadeValue;
		buffer->SetFadeValue(fadeValue);

		if (fadeValue <= 0.f)
		{
			bFadeComplete = true;
			fade = Fade_In;
		}
	}
	break;
	}


	//boundRect = FloatRect(pos + D3DXVECTOR2(WinSizeX*0.5f, WinSizeY*0.5f), D3DXVECTOR2(WinSizeX*0.4f, WinSizeY*0.4f), Pivot::CENTER);
}

void CameraManager::ImguiRender()
{
}

FloatRect CameraManager::GetRenderRect()
{
	FloatRect rc;
	rc.left = rc.top = 0;
	rc.right = WinSizeX;
	rc.bottom = WinSizeY;
	D3DXVECTOR2 start = ScreenToWorld(D3DXVECTOR2(rc.left, rc.top));
	D3DXVECTOR2 end = ScreenToWorld(D3DXVECTOR2(rc.right, rc.bottom));

	rc.left = start.x;
	rc.top = start.y;
	rc.right = end.x;
	rc.bottom = end.y;

	return rc;
}

FloatRect CameraManager::ScreentToWorldFloatRect(FloatRect screenRect)
{
	FloatRect rc;
	rc.left = screenRect.left;
	rc.top = screenRect.top;
	rc.right = screenRect.right;
	rc.bottom = screenRect.bottom;
	D3DXVECTOR2 start = ScreenToWorld(D3DXVECTOR2(rc.left, rc.top));
	D3DXVECTOR2 end = ScreenToWorld(D3DXVECTOR2(rc.right, rc.bottom));

	rc.left = start.x;
	rc.top = start.y;
	rc.right = end.x;
	rc.bottom = end.y;

	return rc;
}

FloatRect CameraManager::WorldToScreenFloatRect(FloatRect worldRect)
{
	FloatRect rc;
	rc.left = worldRect.left;
	rc.top = worldRect.top;
	rc.right = worldRect.right;
	rc.bottom = worldRect.bottom;
	D3DXVECTOR2 start = WorldToScreen(D3DXVECTOR2(rc.left, rc.top));
	D3DXVECTOR2 end = WorldToScreen(D3DXVECTOR2(rc.right, rc.bottom));

	rc.left = start.x;
	rc.top = start.y;
	rc.right = end.x;
	rc.bottom = end.y;

	return rc;
}



void CameraManager::AddZoom(float value)
{
	zoom += value;

	if (zoom < ZOOM_MIN) zoom = ZOOM_MIN;
	if (zoom > ZOOM_MAX) zoom = ZOOM_MAX;

	bool check = true;
	check &= !Math::FloatEqual(zoom, ZOOM_MAX);
	check &= !Math::FloatEqual(zoom, ZOOM_MIN);
	if (check)
	{
		pos.x += WinSizeX * 0.5f * value;
		pos.y += WinSizeY * 0.5f * value;
	}

	UpdateMatrix();
}



D3DXVECTOR2 CameraManager::ScreenToWorld(D3DXVECTOR2 vr)
{
	vr.x += pos.x;
	vr.y += pos.y;
	vr /= zoom;
	return std::move(vr);
}

D3DXVECTOR2 CameraManager::WorldToScreen(D3DXVECTOR2 vr)
{
	vr *= zoom;
	vr.x -= pos.x;
	vr.y -= pos.y;
	return std::move(vr);
}


D3DXVECTOR2 CameraManager::GetMousePos()
{
	D3DXVECTOR2 mouse;
	memcpy(&mouse, Mouse::Get()->GetPosition(), sizeof(D3DXVECTOR2));

	D3DXVECTOR2 pt = ScreenToWorld(mouse);
	return pt;
}

BOOL CameraManager::IsCollision(D3DXVECTOR2 p)
{
	FloatRect rc = GetRenderRect();

	if (rc.left <= p.x &&
		rc.right >= p.x &&
		rc.top <= p.y &&
		rc.bottom >= p.y)
	{
		return true;
	}
	return false;
}

void CameraManager::Shake(float amount, float time)
{
	shakeAmount = amount;
	shakeTime = time;
	shakeDir = Math::RandVec2();
	oldPos = pos;
	bShake = true;
}

void CameraManager::ModeTargetPlayer(GameObject* obj)
{
	cameraMode = Mode::Mode_Target;
	target = obj;
}

void CameraManager::ModeFreeCamera()
{
	cameraMode = Mode::Mode_Free;
}

void CameraManager::SetLimitPos(D3DXVECTOR2 end)
{
	limitEndPos = end;
}

void CameraManager::StartFadeOut()
{
	fade = Fade_Out;
	bFadeComplete = false;
}

void CameraManager::DebugRender()
{
	p2DRenderer->SetCamera(true);
	p2DRenderer->DrawRectangle(boundRect, nullptr);
}

void CameraManager::CameraDataBind()
{
	//쉐이더에서 사용할 카메라의 행렬을 바인딩하면 쉐이더에 항상 들어감

	buffer->Setting(view.GetResult());
	buffer->SetPSBuffer(0);
	buffer->SetVSBuffer(0);
	buffer->SetCSBuffer(0);

}

void CameraManager::ShakeUpdateMatrix()
{
	view.SetPos(-pos + shakeDir * shakeAmount);
	view.SetScale(zoom);

}

void CameraManager::UpdateMatrix()
{
	view.SetPos(-pos);
	view.SetScale(zoom);
}

void CameraManager::ClipMouse()
{
	RECT cR;
	D3DDesc desc;
	DxRenderer::GetDesc(&desc);
	POINT p1, p2;
	POINT mouseScreenPos;

	GetCursorPos(&mouseScreenPos);

	GetClientRect(desc.Handle, &cR);
	memcpy(&p1, &cR.left, sizeof(POINT));
	memcpy(&p2, &cR.right, sizeof(POINT));
	ClientToScreen(desc.Handle, &p1);
	ClientToScreen(desc.Handle, &p2);
	memcpy(&cR.left, &p1, sizeof(POINT));
	memcpy(&cR.right, &p2, sizeof(POINT));

	if (PtInRect(&cR, mouseScreenPos))
		ClipCursor(&cR);
}
