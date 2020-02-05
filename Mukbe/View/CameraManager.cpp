#include "Mukbe.h"
#include "CameraManager.h"
#include "./Utilities/Matrix2D.h"
#include "./Render/ShaderBuffer.h"

SingletonCpp(CameraManager)

CameraManager::CameraManager()
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
			if (Mouse::Get()->Down(0))
			{
				memcpy(&picked, Mouse::Get()->GetPosition(), sizeof(D3DXVECTOR2));

				while (ShowCursor(FALSE) >= 0);
			}
			if (Mouse::Get()->Up(0))
			{
				while (ShowCursor(TRUE) <= 0);
				ClipCursor(NULL);
			}

			if (Mouse::Get()->Press(0))
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
			//POINT index = _GameData->GetIndex();
			//if (oldIndex.x != index.x || oldIndex.y != index.y)
			//{
			//	oldIndex = index;
			//	targetPos = IndexToPos(index, TileManager::tileSize, TileManager::pivotPos) * zoom - D3DXVECTOR2(WinSizeX*0.5f, WinSizeY*0.5f);

			//	saveTime = 0.f;

			//}
			//float factor = saveTime * 2.f;
			//saveTime += Time::Tick();
			//factor > 1.0f ? factor = 1.f : factor;
			//pos = Math::LerpSmoothArrival(pos, targetPos, factor, 3);

			//UpdateMatrix();
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

void CameraManager::Shake()
{
	shakeAmount = 2.f;
	shakeTime = 0.3f;
	shakeDir = Math::RandVec2();
	oldPos = pos;
	bShake = true;
}

void CameraManager::ModeTargetPlayer()
{
	cameraMode = Mode::Mode_Target;
}

void CameraManager::ModeFreeCamera()
{
	cameraMode = Mode::Mode_Free;
}

void CameraManager::CameraDataBind()
{
	//쉐이더에서 사용할 카메라의 행렬을 바인딩하면 쉐이더에 항상 들어감

	buffer->Setting(view.GetResult());
	buffer->SetPSBuffer(0);
	buffer->SetVSBuffer(0);
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
