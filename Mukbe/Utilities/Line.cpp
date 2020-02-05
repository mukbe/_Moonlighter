#include "Mukbe.h"
#include "Line.h"



Line::Line()
	:start(D3DXVECTOR2(0.f,0.f)), end(D3DXVECTOR2(0.f,0.f))
{
}

Line::Line(D3DXVECTOR2 start, D3DXVECTOR2 end)
	:start(start), end(end)
{
}


Line::~Line()
{
}

void Line::Render()
{
	p2DRenderer->DrawLine(start, end,nullptr, DefaultBrush::blue);

}
