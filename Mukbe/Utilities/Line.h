#pragma once

class Line
{
public:
	Line();
	Line(D3DXVECTOR2 start, D3DXVECTOR2 end);
	~Line();

	void Render();
	
	D3DXVECTOR2 GetVector()
	{
		return end - start;
	}

	D3DXVECTOR2 start;
	D3DXVECTOR2 end;

};

