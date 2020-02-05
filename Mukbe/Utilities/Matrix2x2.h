#pragma once

struct Matrix2x2
{
	union
	{
		struct
		{
			float m00, m01;
			float m10, m11;
		};

		float m[2][2];
		float v[4];
	};

	Matrix2x2() {}
	Matrix2x2(float radians)
	{
		float c = std::cos(radians);
		float s = std::sin(radians);

		m00 = c; m01 = -s;
		m10 = s; m11 = c;
	}

	Matrix2x2(float a, float b, float c, float d)
		: m00(a), m01(b)
		, m10(c), m11(d)
	{
	}

	void Set(float radians)
	{
		float c = std::cos(radians);
		float s = std::sin(radians);

		m00 = c; m01 = -s;
		m10 = s; m11 = c;
	}

	Matrix2x2 Abs(void) const
	{
		return Matrix2x2(std::abs(m00), std::abs(m01), std::abs(m10), std::abs(m11));
	}

	D3DXVECTOR2 AxisX(void) const
	{
		return D3DXVECTOR2(m00, m10);
	}

	D3DXVECTOR2 AxisY(void) const
	{
		return D3DXVECTOR2(m01, m11);
	}

	Matrix2x2 Transpose(void) const
	{
		return Matrix2x2(m00, m10, m01, m11);
	}

	const D3DXVECTOR2 operator*(const D3DXVECTOR2& rhs) const
	{
		return D3DXVECTOR2(m00 * rhs.x + m01 * rhs.y, m10 * rhs.x + m11 * rhs.y);
	}

	const Matrix2x2 operator*(const Matrix2x2& rhs) const
	{
		// [00 01]  [00 01]
		// [10 11]  [10 11]

		return Matrix2x2(
			m[0][0] * rhs.m[0][0] + m[0][1] * rhs.m[1][0],
			m[0][0] * rhs.m[0][1] + m[0][1] * rhs.m[1][1],
			m[1][0] * rhs.m[0][0] + m[1][1] * rhs.m[1][0],
			m[1][0] * rhs.m[0][1] + m[1][1] * rhs.m[1][1]
		);
	}
};