#pragma once

class RenderTargetBuffer
{
public:
	RenderTargetBuffer(int width, int height, DXGI_FORMAT format);
	~RenderTargetBuffer();

	ID3D11RenderTargetView* GetRTV() { return rtv; }
	ID3D11ShaderResourceView* GetSRV() { return srv; }
	ID3D11DepthStencilView* GetDSV() { return dsv; }
	void SetArraySize(int size) { arraySize = size; }
	int GetArraySize() { return arraySize; }
	void SetCubeMap(bool set) { bCubeMap = set; arraySize = 6; }

	//클래스 생성 후 어떤 용도로 쓸지 먼저 결정하고 이 함수로 생성
	void Create();

	//rtv를 바인딩한다
	void BindRenderTarget();

private:
	void CreateBuffer();
	void CreateArrayBuffer();
	void CreateCubeBuffer();
	

private:
	int width;
	int height;
	DXGI_FORMAT format;

	int arraySize;
	bool bCubeMap;

	ID3D11Texture2D* renderTargetTexture;
	ID3D11RenderTargetView* rtv;
	ID3D11ShaderResourceView* srv;
	ID3D11DepthStencilView* dsv;

};

