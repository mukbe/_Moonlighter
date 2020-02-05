#include "Mukbe.h"
#include "Matrix2D.h"



void Matrix2D::UpdateMatrix()
{
	//SRT
	result = scale * rotate * trans;
}

Matrix2D::Matrix2D()
	:pos(0, 0), rotation(0.f)
{
	result = rotate = trans = scale = Matrix3x2F::Identity();
}

Matrix2D::Matrix2D(D3DXVECTOR2 pos, D3DXVECTOR2 scale, float radian)
{
	this->rotation = radian;
	this->pos = pos;
	this->scaleValue = scale;

	result = rotate = Matrix3x2F::Identity();
	trans = Matrix3x2F::Translation(pos.x, pos.y);
	SetScale(scale);
	SetRotate(radian);
	UpdateMatrix();
}

void Matrix2D::SetScale(D3DXVECTOR2 s, D3DXVECTOR2 center)
{
	scale = Matrix3x2F::Scale(s.x, s.y, Point2F(center.x,center.y));
	UpdateMatrix();
	
}

void Matrix2D::SetScale(D3DXVECTOR2 s)
{
	scale = Matrix3x2F::Scale(s.x, s.y);
	UpdateMatrix();
}

void Matrix2D::SetScale(float x, float y)
{
	scale = Matrix3x2F::Scale(x, y);
	UpdateMatrix();

}

void Matrix2D::SetScale(float v)
{
	scale = Matrix3x2F::Scale(v,v);
	UpdateMatrix();
}


void Matrix2D::SetRotate(float rad, D3DXVECTOR2 pos, bool isLocal)
{
	rotation = rad;
	if (!isLocal)
	{
		rotate = Matrix3x2F::Rotation((float)D3DXToDegree(rad), Point2F(pos.x, pos.y));
	}
	else
	{
		rotate = Matrix3x2F::Rotation((float)D3DXToDegree(rad));
	}

	UpdateMatrix();
}

void Matrix2D::SetRadian(float rad)
{
	rotation = rad;
	rotate = Matrix3x2F::Rotation((float)D3DXToDegree(rad));
	UpdateMatrix();
}

void Matrix2D::SetPos(D3DXVECTOR2 p)
{
	pos = p;
	trans = Matrix3x2F::Translation(p.x, p.y);
	UpdateMatrix();
}

void Matrix2D::SetPos(float x, float y)
{
	pos = { x,y };
	trans = Matrix3x2F::Translation(x, y);
	UpdateMatrix();
}

void Matrix2D::SetPos(POINT p)
{
	pos = { (float)p.x, (float)p.y };
	trans = Matrix3x2F::Translation((float)p.x, (float)p.y);
	UpdateMatrix();
}




//테스트 안해봄
Matrix2D  Matrix2D::operator*(const Matrix2D & other)
{
	Matrix2D val;
	val.scale = this->scale * other.scale;
	val.rotate = this->rotate * other.rotate;
	val.trans = this->trans * other.trans;
	val.result = this->result * other.result;
	val.pos = this->pos + other.pos;
	val.rotation = this->rotation + other.rotation;
	val.scaleValue.x = this->scaleValue.x * other.scaleValue.x;
	val.scaleValue.y = this->scaleValue.y * other.scaleValue.y;

	return val;
}


