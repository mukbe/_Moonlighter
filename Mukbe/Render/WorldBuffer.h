#pragma once
#include "./Render/ShaderBuffer.h"
#include "../Moonlighter/Shaders/ShaderHeader.h"

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
		memcpy(&data.Matrix, &mat, sizeof(FLOAT) * 4);
	}


};

class WorldBuffer : public ShaderBuffer
{
public:
	WorldBuffer() : ShaderBuffer(&data, sizeof(Struct))
	{
		Setting(D2D1::Matrix3x2F::Identity());
	}

	void Setting(D2D1::Matrix3x2F mat)
	{
		data.Pos = { mat._31,mat._32 };
		memcpy(&data.Matrix, &mat, sizeof(FLOAT) * 4);
	}

	struct Struct
	{
		D3DXVECTOR4 Matrix;

		D3DXVECTOR2 Pos;
		D3DXVECTOR2 Padding;
	}data;


private:

	ShaderBuffer_Mecro(WorldBuffer)
};


class MaterialBuffer : public ShaderBuffer
{
public:
	MaterialBuffer()
		: ShaderBuffer(&Data, sizeof(Data))
	{
		Data.Ambient = D3DXCOLOR(1, 1, 1, 1);
		Data.Diffuse = D3DXCOLOR(1, 1, 1, 1);
		Data.Specular = D3DXCOLOR(1, 1, 1, 1);
		Data.Emissive = D3DXCOLOR(0, 0, 0, 1);

		Data.Shininess = 1;
		Data.DetailFactor = 1;
		Data.textureCheck = 0;
	}

	struct Struct
	{
		D3DXCOLOR Ambient;
		D3DXCOLOR Diffuse;
		D3DXCOLOR Specular;
		D3DXCOLOR Emissive;

		float Shininess;
		float DetailFactor;
		int textureCheck;

		float Padding;
	}Data;

	ShaderBuffer_Mecro(MaterialBuffer)
};


struct LightDesc
{
	int isActive;
	float Range;
	D3DXVECTOR2 Position;

	D3DXCOLOR Color;
	D3DXVECTOR4 Transform;
};

class LightSystemBuffer : public ShaderBuffer
{
private:
	struct Struct
	{
		float Tick;
		D3DXVECTOR3 Padding;

		LightDesc LightTable[LIGHT_MAX];
	}data;

public:
	LightSystemBuffer()
		: ShaderBuffer(&data, sizeof(data))
	{
		data.Tick = TickTime;
		ZeroMemory(data.LightTable, sizeof(LightDesc) * LIGHT_MAX);
	}

	void SetLight(int id_light, LightDesc desc)
	{
		memcpy(&data.LightTable[id_light], &desc, sizeof(LightDesc));
	}
	void OffLight(int id_light)
	{
		data.LightTable[id_light].isActive = false;
		
	}
	ShaderBuffer_Mecro(LightSystemBuffer)

};
