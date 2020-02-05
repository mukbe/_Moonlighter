#pragma once



//3d������������ ���ε�
//2d������������ ������
//�ؽ��ĸ� ���ÿ� �ε��Ͽ� srv�� bitmap���� ������ ����
//�ʿ�ÿ� CS�� ���ε��Ͽ� ��밡���ϰ�
//�� �ؽ��ĸ� �����Ͽ� ���嵵 ����
class Texture
{
	friend class ImageManager;
public:

	static void SaveToFile(wstring fileFullPath, ID3D11ShaderResourceView* srv);

private:
	enum ShaderSlot : short
	{
		None = 0,
		VS = 1,
		HS = 1 << 1,
		DS = 1 << 2,
		GS = 1 << 3,
		PS = 1 << 4,
		CS = 1 << 5,
	};

private:
public:
	Texture(DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM);
	Texture(wstring file, UINT frameX = 1, UINT frameY = 1, DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM);
	~Texture();

	HRESULT SetTexture(wstring file);
	wstring GetFilePath() { return file; }

	int GetWidth() { return width; }
	int GetHeight() { return height; }
	void SetWidth(int val) { width = val; }
	void SetHeight(int val) { height = val; }
	const D3DXVECTOR2& GetFrameSize() { return frameSize; }
	void SetFrameSize(const D3DXVECTOR2& size) { frameSize = size; }
	const D3DXVECTOR2& GetMaxFrame() { return D3DXVECTOR2((float)maxFrameX, (float)maxFrameY); }

	const ID2D1Bitmap* GetBitmap() { return bitmap; }



	DXGI_FORMAT GetFormat() { return format; }

	ID3D11ShaderResourceView* GetSRV() { return srv; }
	ID3D11Texture2D* GetTexture() { return texture; }

	void SetPixel(vector<D3DXCOLOR>& colors, int w, int h);
	void SetPixel32(vector<D3DXCOLOR>& colors, int w, int h);
	void GetPixel(vector<vector<D3DXCOLOR>>& colors);
	void GetPixel(vector<D3DXCOLOR>& colors);
	void GetPixel32(vector<vector<D3DXCOLOR>>& colors);

	void SavePNG(wstring saveFile);
	wstring GetFile()const { return file; }

	//PS���� ���ε�
	void SetShaderResource(UINT slot);
	void SetCSResource(UINT slot);

	//���ε� ����
	void ReleaseResource();


	//void Render(D3DXVECTOR2 size = D3DXVECTOR2(0,0), float alpha = 1.f ,Pivot pivot = Pivot::LEFT_TOP, D3DXVECTOR2 offset = D3DXVECTOR2(0.f,0.f));
	//void FrameRender( UINT frameX = 0, UINT frameY = 0, D3DXVECTOR2 size = D3DXVECTOR2(0, 0), float alpha = 1.f, Pivot pivot = Pivot::LEFT_TOP, D3DXVECTOR2 offset = D3DXVECTOR2(0.f,0.f));
	
	void Render(FloatRect rc, Matrix2D* transform, float alpha = 1.f, D3DXVECTOR2 offset = D3DXVECTOR2(0.f, 0.f));
	void FrameRender(FloatRect rc, Matrix2D* transform, UINT frameX = 0, UINT frameY = 0, float alpha = 1.f, D3DXVECTOR2 offset = D3DXVECTOR2(0.f, 0.f));


	//void AniRender(int x, int y, animation* ani, Pivot pivot = Pivot::LEFT_TOP, bool sizeSet = FALSE);


private:
	void Initialize();
	ID3D11Texture2D* GetReadBuffer();
	const D2D1_RECT_F CalculatePivot(D3DXVECTOR2 size, Pivot pivot);


private:
	wstring file;
	//�̹��� ������ �ʺ����
	int width;
	int height;
	ID2D1Bitmap* bitmap;
	vector<WICRect>	frameInfo;
	int	maxFrameX;
	int	maxFrameY;
	//������ �ϳ��� ���� �ʺ�
	D3DXVECTOR2 frameSize;


	DXGI_FORMAT format;
	ID3D11Texture2D* texture;
	ID3D11ShaderResourceView* srv;

	int lastSlot;
	UINT lastBindFlag;

	int isSlot;
};
