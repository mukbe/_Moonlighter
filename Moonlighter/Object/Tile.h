#pragma once

class Tile : public GameObject
{
public:
	Tile(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	virtual~Tile();

	//�ʱ�ȭ
	virtual void Init();
	//�޸� ����
	virtual void Release();
	//���� ��ƾ
	virtual void Update(float tick);

	virtual void Render();

	void SetTileMapTexture(string key = "");
private:
	shared_ptr<Texture> texture;

	string imageKey;

};

