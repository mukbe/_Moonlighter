#pragma once

class Tile : public GameObject
{
public:
	Tile(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	virtual~Tile();

	//초기화
	virtual void Init();
	//메모리 해제
	virtual void Release();
	//메인 루틴
	virtual void Update(float tick);

	virtual void Render();

	void SetTileMapTexture(string key = "");
private:
	shared_ptr<Texture> texture;

	string imageKey;

};

