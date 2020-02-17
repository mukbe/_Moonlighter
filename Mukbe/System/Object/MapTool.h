#pragma once
class Tile;
class MapTool
{
	friend class SceneBase;
public:	
	static D3DXVECTOR2 tileSize;
	static D3DXVECTOR2 tileMaxIndex;

	static void Load(wstring file) {}
	static D3DXVECTOR2 PositionToIndex(D3DXVECTOR2 position);
	static D3DXVECTOR2 IndexToPosition(D3DXVECTOR2 index);
public:
	MapTool();
	~MapTool();

	void Init();
	void Release();
	void Update();
	void Render();
	void ImguiRender();

	Tile* GetTileAsIndex(D3DXVECTOR2 index);
	Tile* GetTileAsPosition(D3DXVECTOR2 position);
	vector<Tile*> GetTiles() { return tiles; }
private:
	vector<Tile*> tiles;
};

