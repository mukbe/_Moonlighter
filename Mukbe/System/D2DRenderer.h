#pragma once

namespace DefaultBrush
{
	enum Enum
	{
		white = 0, black, yello, red, blue, green, gray, end
	};
}


class Matrix2D;
class D2DRenderer
{
	SingletonHeader(D2DRenderer)
public:
	D3DXCOLOR clearColor;
	void Create2DBuffer();
	void BeginDraw();
	void EndDraw();
	void BeginDrawWithoutClear();

	HRESULT AddTextFormat(wstring fontname, float size);

	ID2D1Bitmap* CreateD2DBitmapFromFile(wstring file);


	ID2D1RenderTarget* GetRenderTarget() { return d2dRenderTarget; }
	ID2D1DeviceContext* GetDeviceContext() { return d2dDeviceContext; }
	IDWriteFactory* GetDWriteFactory() { return dwFactory; }
private:
	typedef unordered_map<wstring, IDWriteTextFormat*> mapTextList;
	typedef unordered_map<wstring, IDWriteTextFormat*>::iterator mapTextIter;

private:
	//== 2dRenderer
	ID2D1Factory1* d2dFactory;
	ID2D1RenderTarget * d2dRenderTarget;

	IWICImagingFactory* wicFactory;
	IDWriteFactory* dwFactory;

	ID2D1Device* d2dDevice;
	ID2D1DeviceContext* d2dDeviceContext;

	//ÅØ½ºÆ®·¹ÀÌ¾Æ¿ô
	IDWriteTextLayout* dwLayout;
	ID2D1SolidColorBrush*	dwDefaultBrush[DefaultBrush::end];

	//ÅØ½ºÆ® Ãâ·Â ½ºÅä¸®Áö
	mapTextList		dwTextFormats;

	bool bCamera;
	ID2D1Layer* pLayer;
public:

	void DrawText2D(D3DXVECTOR2 pos, wstring text, float size, DefaultBrush::Enum defaultBrush = DefaultBrush::black, DWRITE_TEXT_ALIGNMENT align = DWRITE_TEXT_ALIGNMENT_CENTER, wstring font = L"¸¼Àº°íµñ");
	void DrawText2D(D3DXVECTOR2 pos, wstring text, float size, D3DXCOLOR color, DWRITE_TEXT_ALIGNMENT align = DWRITE_TEXT_ALIGNMENT_CENTER, wstring font = L"¸¼Àº°íµñ");
	void DrawText2D(FloatRect rc, wstring text, DefaultBrush::Enum defaultBrush = DefaultBrush::black, DWRITE_TEXT_ALIGNMENT align = DWRITE_TEXT_ALIGNMENT_CENTER, wstring font = L"¸¼Àº°íµñ");
	void DrawText2D(FloatRect rc, wstring text, D3DXCOLOR color, DWRITE_TEXT_ALIGNMENT align = DWRITE_TEXT_ALIGNMENT_CENTER, wstring font = L"¸¼Àº°íµñ");

	//void DrawTextField(D3DXVECTOR2 pos, wstring text, D3DXVECTOR2 size, int width, int height, DefaultBrush::Enum defaultBrush = DefaultBrush::black, DWRITE_TEXT_ALIGNMENT align = DWRITE_TEXT_ALIGNMENT_CENTER, wstring font = L"¸¼Àº°íµñ");


	void DrawLine(D3DXVECTOR2 start, D3DXVECTOR2 end, Matrix2D* transform, DefaultBrush::Enum defaultBrush = DefaultBrush::black, float strokeWidth = 1);
	void DrawLine(D3DXVECTOR2 start, D3DXVECTOR2 end, Matrix2D* transform, D3DXCOLOR color, float strokeWidth = 1);
	void DrawRectangle(FloatRect rc, Matrix2D* transform, D2D1::ColorF::Enum color, float alpha, float strokeWidth = 1);
	void DrawRectangle(FloatRect rc, Matrix2D* transform, DefaultBrush::Enum defaultBrush = DefaultBrush::black, float strokeWidth = 1);
	void DrawEllipse(FloatRect rc, Matrix2D* transform, D2D1::ColorF::Enum color, float alpha, float strokeWidth = 1);
	void DrawEllipse(FloatRect rc, Matrix2D* transform, DefaultBrush::Enum defaultBrush = DefaultBrush::black,float strokeWidth = 1);
	void FillRectangle(FloatRect rc, Matrix2D* transform, D2D1::ColorF::Enum color, float alpha);
	void FillRectangle(FloatRect rc, Matrix2D* transform, DefaultBrush::Enum defaultBrush = DefaultBrush::black);
	void FillEllipse(FloatRect rc, Matrix2D* transform, D2D1::ColorF::Enum color, float alpha);
	void FillEllipse(FloatRect rc, Matrix2D* transform, DefaultBrush::Enum defaultBrush = DefaultBrush::black);


	//==============================================================
	void SetCamera(bool b) { bCamera = b; }
	void IASet(Matrix2D* transform);


	void DrawRectangle(D2D1_RECT_F rc, D2D1::ColorF::Enum color, float alpha, float strokeWidth = 1);
	void DrawRectangle(D2D1_RECT_F rc, DefaultBrush::Enum defaultBrush = DefaultBrush::black, float strokeWidth = 1);

};

#define p2DRenderer D2DRenderer::Get()
#define DeviceContext2D D2DRenderer::Get()->GetDeviceContext()