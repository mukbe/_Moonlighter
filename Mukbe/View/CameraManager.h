#pragma once

#define ZOOM_MAX 2.5f
#define ZOOM_MIN 0.5f

//���콺�� �ٸ޼��� �޾ƿͼ� �� ũ�� �����ϸ� �ɵ�
class CameraManager
{
	SingletonHeader(CameraManager)  // �̱��� ���� 
	enum class Mode 
	{
		Mode_Free,
		Mode_Target,

	};

public:

	void Update();
	void ImguiRender();

	FloatRect GetRenderRect(); 
	FloatRect ScreentToWorldFloatRect(FloatRect screenRect);
	FloatRect WorldToScreenFloatRect(FloatRect worldRect);

	D3DXVECTOR2 GetPos() { return pos; }
	//void SetPos(D3DXVECTOR2 p)
	//{
	//	pos = p;
	//}

	float GetZoom() { return zoom; }
	void AddZoom(float value);

	D3DXVECTOR2 ScreenToWorld(D3DXVECTOR2 vr);
	D3DXVECTOR2 WorldToScreen(D3DXVECTOR2 vr);

	D3DXVECTOR2 GetMousePos();

	BOOL IsCollision(D3DXVECTOR2 p);
	Matrix2D GetView() { return view; }

	void Shake(float amount = 2.f, float time = 0.3f);
	void ModeTargetPlayer(GameObject* obj);
	void ModeFreeCamera();

	void DebugRender();
	//cbuffer bind
	void CameraDataBind();
private:
	void UpdateMatrix();
	void ClipMouse();
	void ShakeUpdateMatrix();

	Matrix2D view;
	D3DXVECTOR2 pos;
	RECT renderRect;
	FloatRect boundRect;
	float zoom;
	
	D3DXVECTOR2 pick;
	D3DXVECTOR2 picked;

	Mode cameraMode;
	D3DXVECTOR2 targetPos;
	POINT oldIndex;
	float saveTime;

	float shakeAmount;
	float shakeTime;
	D3DXVECTOR2 shakeDir;
	D3DXVECTOR2 oldPos;
	bool bShake;

	GameObject* target;
	float speed;
private:

	class CameraBuffer : public ShaderBuffer
	{
	private:
		struct Struct
		{
			D3DXVECTOR4 Matrix;

			D3DXVECTOR2 CameraPos;
			D3DXVECTOR2 Padding;

		}data;

	public:
		CameraBuffer()
			:ShaderBuffer(&data, sizeof Struct)
		{}

		void Setting(D2D1::Matrix3x2F mat)
		{
			data.CameraPos = { mat._31,mat._32 };
			memcpy(&data.Matrix, &mat, sizeof(FLOAT)*4);
		}
	};

	unique_ptr<CameraBuffer> buffer;


};

#define CAMERA CameraManager::Get()