#pragma once

class FloatRect
{
public:
	static FloatRect MoveRect(FloatRect rc, float dx, float dy);
	static FloatRect MoveRect(FloatRect rc, D3DXVECTOR2 v);
	//static FloatRect CalculateTransform(FloatRect rc, Matrix2D* mat);

	FloatRect operator+=(const D3DXVECTOR2& v);
	FloatRect operator-=(const D3DXVECTOR2& v);


public:
	float left;
	float top;
	float right;
	float bottom;

	FloatRect();
	FloatRect(D3DXVECTOR2 pos, float d , Pivot p);
	FloatRect(D3DXVECTOR2 pos, float w, float h, Pivot p);
	FloatRect(D3DXVECTOR2 pos, D3DXVECTOR2 size, Pivot p);
	FloatRect(float l, float t, float r, float b);
	RECT GetRect();
	D3DXVECTOR2 GetSize() { return D3DXVECTOR2(right - left, bottom - top); }
	void Update(D3DXVECTOR2 pos, D3DXVECTOR2 size, Pivot p);

public:
	static FloatRect Calculate(D3DXVECTOR2 pos, D3DXVECTOR2 size, Pivot p);


};

