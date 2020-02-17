#pragma once
class Math
{
public:
	static const float PI;
	static const float Epsilon;
	static const D3DXVECTOR2 gravity;
	static const float gravityScale;

	static const int IntMin;
	static const int IntMax;
	static const float FloatMin;
	static const float FloatMax;

	static float NegativeChecking(float value);
	static float ToRadian(float degree);
	static float ToDegree(float radian);

	static int Random(int r1, int r2);
	static float Random(float r1, float r2);

	// Returns random float in [0, 1).
	static float RandF();
	static D3DXVECTOR2 RandVec2();

	static float Lerp(float val1, float val2,float amount);
	static float Clamp(float value, float min, float max);
	static int Clamp(int value, int min, int max);

	static float Modulo(float val1, float val2);

	static D3DXCOLOR RandomColor();

	//평행이면 0, b가 a의 시계방향에 있으면 양수, b가 a에 반시계방향이면 음수 
	static float Cross(const D3DXVECTOR2& a, const D3DXVECTOR2& b)
	{
		return a.x * b.y - a.y * b.x;
	}
	//백터 PB가 백터 PA 시계방향이면 양수, 반시계면 음수
	static float Cross(const D3DXVECTOR2& p, const D3DXVECTOR2& a, const D3DXVECTOR2& b)
	{
		return Cross(a - p, b - p);
	}


	static D3DXVECTOR2 Cross(const D3DXVECTOR2& v, float a)
	{
		return D3DXVECTOR2(a * v.y, -a * v.x);
	}

	static D3DXVECTOR2 Cross(float a, const D3DXVECTOR2& v)
	{
		return D3DXVECTOR2(-a * v.y, a * v.x);
	}
	static bool BiasGreaterThan(float a, float b)
	{
		const float k_biasRelative = 0.95f;
		const float k_biasAbsolute = 0.01f;
		return a >= b * k_biasRelative + a * k_biasAbsolute;
	}

	static void D3DXVector2Normalize(D3DXVECTOR2& vec)
	{
		float len = D3DXVec2Length(&vec);
		vec /= len;
	}

	template<typename T>
	static T Min(const T& a, const T& b)
	{
		return a < b ? a : b;
	}

	template<typename T>
	static T Max(const T& a, const T& b)
	{
		return a > b ? a : b;
	}

	template<typename T>
	static T Lerp(const T& a, const T& b, float t)
	{
		return a + (b - a)*t;
	}

	template<typename T>
	static T LerpSmoothArrival(const T& a, const T& b, const float& t, int amount)
	{
		int temp = amount;
		float ratio = 1 - t;
		temp = Clamp(amount, 3, 7);
		return a + (b - a) * (1 - powf(ratio, (float)temp));
	}
	template<typename T>
	static T LerpSmoothStart(const T& a, const T& b, const float& t, int amount)
	{
		int temp = amount;
		temp = Clamp(amount, 3, 7);
		return a + (b - a) * powf(t, (float)temp);
	}

	template<typename T>
	static T SmoothStepLerp(const T& a, const T& b, const float& ratio)
	{
		return a + (b - a) * ratio * ratio * (3.f - 2.f * ratio);
	}

	template<typename T>
	static T Abs(const T& a)
	{
		if (a >= 0.0f)
			return a;
		else
			return -a;
	}
	static bool FloatEqual(const float & f1, const float & f2)
	{
		return (fabsf(f1 - f2) <= Math::Epsilon);
	}


	static float Angle(D3DXVECTOR3 v1, D3DXVECTOR3 v2);

	static bool IsPointInAABB(D3DXVECTOR2 rectPos, D3DXVECTOR2 rectSize, D3DXVECTOR2 ptPos);
	static bool IsPointInAABB(FloatRect rc, D3DXVECTOR2 ptPos);
	static bool IsPointInCircle(D3DXVECTOR2 origin, float radius, D3DXVECTOR2 ptPos);

	static bool IsAABBInAABB(FloatRect rc0, FloatRect rc1, FloatRect * temp = nullptr);
	static bool IsAABBInCircle(FloatRect rc, D3DXVECTOR2 origin, float radius);
	static bool IsAABBInAABBReaction(FloatRect* me, FloatRect other, D3DXVECTOR2* dir = nullptr );

	static bool IsLineInLine(Line l1, Line l2, D3DXVECTOR2* point = nullptr);

	static bool IsSegmentLineInLine(Line l1, Line l2, D3DXVECTOR2* point = nullptr);

private:
	static bool ParallSegments(Line l1, Line l2, D3DXVECTOR2* point = nullptr);
	static bool InBoundingRect(D3DXVECTOR2 p, D3DXVECTOR2 a, D3DXVECTOR2 b);

};