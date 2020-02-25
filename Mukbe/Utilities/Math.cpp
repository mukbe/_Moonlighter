#include "Mukbe.h"
#include "Math.h"

const float Math::PI = 3.14159265f;
const float Math::Epsilon = 1E-6f;
const int Math::IntMin = -2147483647;
const int Math::IntMax = 2147483647;
const float Math::FloatMin = -3.402823E+38f;
const float Math::FloatMax = 3.402823E+38f;
const float Math::gravityScale = 50.f;
const D3DXVECTOR2 Math::gravity = { 0, 9.8f * gravityScale };
float Math::NegativeChecking(float value)
{
	if (value < 0.0f)
		return -1.0f;
	else
		return 1.0f;
}

float Math::ToRadian(float degree)
{
	return degree * PI / 180.0f;
}

float Math::ToDegree(float radian)
{
	return radian * 180.0f / PI;
}

float Math::Random(float r1, float r2)
{
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = r2 - r1;
	float val = random * diff;
	
	return r1 + val;
}

float Math::RandF()
{
	return (float)(rand()) / (float)RAND_MAX;
}

D3DXVECTOR2 Math::RandVec2()
{
	float val0 = RandF() > 0.5f ? RandF() : -RandF();
	float val1 = RandF() > 0.5f ? RandF() : -RandF();
	return D3DXVECTOR2(val0, val1);
}

float Math::Lerp(float val1, float val2, float amount)
{
	return val1 + (val2 - val1)* amount;
}

float Math::Clamp(float value, float min, float max)
{
	value = value > max ? max : value;
	value = value < min ? min : value;

	return value;
}

int Math::Clamp(int value, int min, int max)
{
	value = value > max ? max : value;
	value = value < min ? min : value;

	return value;
}


float Math::Modulo(float val1, float val2)
{
	while (val1 - val2 >= 0)
		val1 -= val2;

	return val1;
}

D3DXCOLOR Math::RandomColor()
{
	float r = Math::Random(0.0f, 1.0f);
	float g = Math::Random(0.f, 1.0f);
	float b = Math::Random(0.f, 1.0f);
	float a = Math::Random(0.3f, 0.5f);
	return D3DXCOLOR(r,g,b,a);
}


int Math::Random(int r1, int r2)
{
	return (int)(rand() % (r2 - r1 + 1)) + r1;
}


float Math::Angle(D3DXVECTOR3 v1, D3DXVECTOR3 v2)
{
	float angle = 0;

	float dot = D3DXVec3Dot(&v1, &v2);
	float length1 = D3DXVec3Length(&v1);
	float length2 = D3DXVec3Length(&v2);

	angle = acosf(dot / (length1 * length2));

	return angle;
}

float Math::Angle(D3DXVECTOR2 v1, D3DXVECTOR2 v2)
{
	float angle = 0;

	float dot = D3DXVec2Dot(&v1, &v2);
	float length1 = D3DXVec2Length(&v1);
	float length2 = D3DXVec2Length(&v2);

	angle = acosf(dot / (length1 * length2));

	return angle;
}


bool Math::IsPointInAABB(D3DXVECTOR2 rectPos, D3DXVECTOR2 rectSize, D3DXVECTOR2 ptPos)
{
	float left, top, right, bottom;
	left = rectPos.x;
	top = rectPos.y;
	right = rectPos.x + rectSize.x;
	bottom = rectPos.y - rectSize.y;

	if (ptPos.x < left || ptPos.x > right)
		return false;
	else if (ptPos.y > bottom || ptPos.y < top)
		return false;

	return true;
}

bool Math::IsPointInAABB(FloatRect rc, D3DXVECTOR2 ptPos)
{
	if (ptPos.x < rc.left || ptPos.x > rc.right)
		return false;
	else if (ptPos.y > rc.bottom || ptPos.y < rc.top)
		return false;

	return true;
}

bool Math::IsPointInCircle(D3DXVECTOR2 origin, float radius, D3DXVECTOR2 ptPos)
{
	float distance = D3DXVec2Length(&(ptPos - origin));

	if (distance <= radius) return true;

	return false;
}

bool Math::IsAABBInAABB(FloatRect rc0, FloatRect rc1, FloatRect * temp)
{
	if (rc0.right < rc1.left || rc0.left > rc1.right) return false;
	if (rc0.bottom < rc1.top || rc0.top > rc1.bottom) return false;

	if (temp != nullptr)
	{
		temp->left = Math::Max(rc0.left, rc1.left);
		temp->right = Math::Min(rc0.right, rc1.right);
		temp->top = Math::Max(rc0.top, rc1.top);
		temp->bottom = Math::Min(rc0.bottom, rc1.bottom);
	}
	return true;
}

bool Math::IsAABBInCircle(FloatRect rc, D3DXVECTOR2 origin, float radius)
{
	FloatRect temp, pt;
	pt = FloatRect(origin, radius, Pivot::CENTER);
	if (IsAABBInAABB(rc, pt))
	{
		if (origin.x <= rc.left && origin.y <= rc.top)
		{
			float dx = fabsf(rc.left - origin.x);
			float dy = fabsf(rc.top - origin.y);
			if (dx * dx + dy * dy > radius * radius)
				return false;
		}
		if (origin.x >= rc.right && origin.y <= rc.top)
		{
			float dx = fabsf(rc.right - origin.x);
			float dy = fabsf(rc.top - origin.y);
			if (dx * dx + dy * dy > radius * radius)
				return false;
		}
		if (origin.x >= rc.right && origin.y >= rc.bottom)
		{
			float dx = fabsf(rc.right - origin.x);
			float dy = fabsf(rc.bottom - origin.y);
			if (dx * dx + dy * dy > radius * radius)
				return false;
		}
		if (origin.x <= rc.left && origin.y >= rc.bottom)
		{
			float dx = fabsf(rc.left - origin.x);
			float dy = fabsf(rc.bottom - origin.y);
			if (dx * dx + dy * dy > radius * radius)
				return false;
		}

		return true;
	}

	return false;
}

bool Math::IsAABBInAABBReaction(FloatRect * move, FloatRect hold, D3DXVECTOR2* dir)
{
	FloatRect rcInter;

	if (IsAABBInAABB(*move, hold, &rcInter) == false)
		return false;

	float interW = rcInter.right - rcInter.left;
	float interH = rcInter.bottom - rcInter.top;

	if (Math::FloatEqual(interW, interH))
	{
		if (Math::FloatEqual(rcInter.left, hold.left))
		{
			move->left -= interW;
			move->right -= interW;
			if (dir)
				*dir = D3DXVECTOR2(1.f, 0.f);
		}
		else if (Math::FloatEqual(rcInter.right, hold.right))
		{
			move->left += interW;
			move->right += interW;
			if (dir)
				*dir = D3DXVECTOR2(-1.f, 0.f);
		}
		//위
		if (Math::FloatEqual(rcInter.top, hold.top))
		{
			move->top -= interH;
			move->bottom -= interH;
			if (dir)
				*dir = D3DXVECTOR2(0.f, -1.f);
		}
		//아래
		else if (Math::FloatEqual(rcInter.bottom, hold.bottom))
		{
			move->top += interH;
			move->bottom += interH;
			if (dir)
				*dir = D3DXVECTOR2(0.f, 1.f);
		}
	}
	else if (interW < interH)
	{
		if (Math::FloatEqual(rcInter.left, hold.left))
		{
			move->left -= interW;
			move->right -= interW;
			if (dir)
				*dir = D3DXVECTOR2(1.f, 0.f);
		}
		else if (Math::FloatEqual(rcInter.right, hold.right))
		{
			move->left += interW;
			move->right += interW;
			if (dir)
				*dir = D3DXVECTOR2(-1.f, 0.f);
		}
	}
	else
	{
		//위
		if (Math::FloatEqual(rcInter.top, hold.top))
		{
			move->top -= interH;
			move->bottom -= interH;
			if (dir)
				*dir = D3DXVECTOR2(0.f, 1.f);
		}
		//아래
		else if (Math::FloatEqual(rcInter.bottom, hold.bottom))
		{
			move->top += interH;
			move->bottom += interH;
			if (dir)
				*dir = D3DXVECTOR2(0.f, -1.f);
		}
	}

	return true;
	
}
bool Math::IsAABBInAABBReaction(FloatRect& move, FloatRect& hold)
{
	FloatRect rcHold;
	rcHold.left = hold.left;
	rcHold.top = hold.top;
	rcHold.right = hold.right;
	rcHold.bottom = hold.bottom;

	FloatRect rcMove;
	rcMove.left = move.left;
	rcMove.top = move.top;
	rcMove.right = move.right;
	rcMove.bottom = move.bottom;

	FloatRect rcInter;

	if (!Math::IsAABBInAABB(rcInter, rcHold, &rcMove)) return false;

	float interW = rcInter.right - rcInter.left;
	float interH = rcInter.bottom - rcInter.top;

	//수직충돌이니?
	//if (interW > interH)
	//{
	//	//위
	//	if (rcInter.top == rcHold.top)
	//	{
	//		OffsetRect(&rcMove, 0, -interH);
	//	}
	//	else if (rcInter.bottom == rcHold.bottom)
	//	{
	//		OffsetRect(&rcMove, 0, interH);
	//	}
	//}
	//else
	//{
	//	if (rcInter.left == rcHold.left)
	//	{
	//		OffsetRect(&rcMove, -interW, 0);
	//	}
	//	else if (rcInter.right == rcHold.right)
	//	{
	//		OffsetRect(&rcMove, interW, 0);
	//	}
	//}

	//mrcMove.left = static_cast<float>(rcMove.left);
	//mrcMove.top = static_cast<float>(rcMove.top);
	//mrcMove.right = static_cast<float>(rcMove.right);
	//mrcMove.bottom = static_cast<float>(rcMove.bottom);

	return true;

}


//직선충돌
bool Math::IsLineInLine(Line l1, Line l2, D3DXVECTOR2 * point)
{
	float det = Math::Cross(l1.GetVector(), l2.GetVector());
	
	if (Math::Abs(det) < Epsilon) 
		return false;

	if (point != nullptr)
		*point = l1.start + l1.GetVector() *  Math::Cross((l2.start - l1.start), (l2.end - l2.start)) / det;

	return true;
}

bool Math::IsSegmentLineInLine(Line l1, Line l2, D3DXVECTOR2 * point)
{
	D3DXVECTOR2 p;
	if (!(Math::IsLineInLine(l1, l2, &p)))
		return Math::ParallSegments(l1, l2, &p);

	*point = p;
	return Math::InBoundingRect(*point, l1.start, l1.end) && Math::InBoundingRect(*point, l2.start, l2.end);
}

bool Math::ParallSegments(Line l1, Line l2, D3DXVECTOR2 * point)
{
	D3DXVECTOR2 maxL1 = D3DXVECTOR2(Math::Max(l1.start.x, l1.end.x), Math::Max(l1.start.y, l1.end.y));
	D3DXVECTOR2 minL1 = D3DXVECTOR2(Math::Min(l1.start.x, l1.end.x), Math::Min(l1.start.y, l1.end.y));
	D3DXVECTOR2 maxL2 = D3DXVECTOR2(Math::Max(l2.start.x, l2.end.x), Math::Max(l2.start.y, l2.end.y));
	D3DXVECTOR2 minL2 = D3DXVECTOR2(Math::Min(l2.start.x, l2.end.x), Math::Min(l2.start.y, l2.end.y));
	FloatRect rc1 = FloatRect(minL1.x, minL1.y, maxL1.x, maxL1.y);
	FloatRect rc2 = FloatRect(minL2.x, minL2.y, maxL2.x, maxL2.y);

	//한 직선위에 없거나 두 선분이 겹치지 않는 경우를 우선 걸러낸다. 본문의 1번 관계인 경우이다.
	if (Math::Cross(l1.start, l1.end, l2.start) != 0 || !Math::IsAABBInAABB(rc1, rc2))
		return false;

	//두 선분이 확실히 겹친다면 교차점 하나를 찾는다.
	//if (a < c) p = c;
	//else p = a;
	return true;
}

bool Math::InBoundingRect(D3DXVECTOR2 p, D3DXVECTOR2 a, D3DXVECTOR2 b)
{
	D3DXVECTOR2 ab = b - a;
	D3DXVECTOR2 pa = a - p;
	D3DXVECTOR2 pb = b - p;
	float len1, len2, det, total;

	len1 = D3DXVec2Length(&pa);
	len2 = D3DXVec2Length(&pb);
	det = D3DXVec2Length(&ab);
	total = len1 + len2;

	if (total <= det) return true;
	return false;




	D3DXVECTOR2 size = D3DXVECTOR2(Math::Abs(b.x - a.x), Math::Abs(b.y - a.y));
	D3DXVECTOR2 pos = D3DXVECTOR2(Math::Min(a.x, b.x), Math::Min(a.y, b.y));
	
	if (size.x == 0.f) size.x = 1.f;
	if (size.y == 0.f) size.y = 1.f;

	FloatRect rc(pos, size, Pivot::LEFT_TOP);
	if (Math::IsPointInAABB(rc, p))
		return true;

	return false;
}


