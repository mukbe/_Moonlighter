#pragma once

using namespace D2D1;

class Matrix2D
{
private:
	Matrix3x2F rotate;
	Matrix3x2F scale;
	Matrix3x2F trans;
	Matrix3x2F result;

	D3DXVECTOR2 pos;
	float rotation;
	D3DXVECTOR2 scaleValue;

	void UpdateMatrix();

public:
	Matrix2D();
	Matrix2D(D3DXVECTOR2 pos,D3DXVECTOR2 scale = D3DXVECTOR2(1,1), float radian = 0.f);

	Matrix3x2F GetResult() { return result; }
	D3DXVECTOR2 GetPos() { return pos; }
	float GetRotation() { return rotation; }

	void SetScale(D3DXVECTOR2 s, D3DXVECTOR2 center);
	void SetScale(D3DXVECTOR2 s);
	void SetScale(float x, float y);
	void SetScale(float v);

	void SetRotate(float rad, D3DXVECTOR2 pos = D3DXVECTOR2(0,0), bool isLocal = true);
	//for physics
	void SetRadian(float rad);

	void SetPos(D3DXVECTOR2 p);
	void SetPos(float x, float y);
	void SetPos(POINT p);
	
	Matrix3x2F GetInv() 
	{
		Matrix3x2F temp = result;
		D2D1InvertMatrix(&temp);
		return temp;
		
	}




	Matrix2D operator*(const Matrix2D& other);
	
};

