#include "Mukbe.h"
#include "GameObject.h"
#include "./Utilities/Matrix2D.h"



GameObject::GameObject(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	: name(name), bActive(true), worldBuffer(nullptr), shaderKey("None")
	, alpha(1.f), lifeTiem(0.f)
{
	worldBuffer = Buffers->FindShaderBuffer<WorldBuffer>();
	transform = Matrix2D(pos);

	bActive = true;
	this->size = size;
	pivot = Pivot::BOTTOM;
	rc = FloatRect(D3DXVECTOR2(0.f, 0.f), size, pivot);
	renderRect = FloatRect(D3DXVECTOR2(0.f,0.f), size, pivot);
}


GameObject::~GameObject()
{
	
}

void GameObject::Init()
{
	_RenderPool->Request(this, GetLayer());
}

void GameObject::Release()
{
	_RenderPool->Remove(this, GetLayer());
}



void GameObject::Update(float tick)
{
	lifeTime += tick;
}


void GameObject::Render()
{
	if (SceneBase::DebugMode)
		p2DRenderer->FillRectangle(rc, &transform, DefaultBrush::white);


}

FloatRect GameObject::GetCollider()
{
	return FloatRect::MoveRect(rc, transform.GetPos());
}

void GameObject::SetRenderSize( D3DXVECTOR2 size, Pivot p, D3DXVECTOR2 pos)
{
	renderRect = FloatRect(pos, size, p);
}


//void GameObject::PostRender()
//{
//	if (bActive == false)return;
//	if (shaderKey == "None") return;
//
//	CAMERA->CameraDataBind();
//	worldBuffer->Setting(transform.GetResult());
//	worldBuffer->SetPSBuffer(1);
//	Shaders->BindShader(shaderKey);
//
//	UINT stride = sizeof(VertexType);
//	UINT offset = 0;
//
//	DeviceContext->IASetInputLayout(nullptr);
//	DeviceContext->IASetVertexBuffers(0, 0, nullptr, nullptr, nullptr);
//	DeviceContext->IASetIndexBuffer(nullptr, DXGI_FORMAT_UNKNOWN, 0);
//	DeviceContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
//
//	pRenderer->TurnOnAlphaBlend();
//	DeviceContext->Draw(4, 0);
//	pRenderer->TurnOffAlphaBlend();
//
//}
