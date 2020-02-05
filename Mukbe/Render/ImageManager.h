#pragma once
#include <memory>

//�����ϸ� Ű������ �������� �ϸ� ����
//shared_ptr�� ����ϰ� �ʹٸ� shared_ptr<Texture> �� �����ؼ� �����
//����� ���� TextureŬ������ ����ϴ� ����ϰ� ���� => �ڷ��� ���¸� �ٸ���



class ImageManager
{
	SingletonHeader(ImageManager)
	friend class Window;
public:
	bool AddTexture(string key, wstring fileName);
	bool AddFrameTexture(string key, wstring fileName, UINT frameX = 1, UINT frameY = 1);


	void Render(string key, FloatRect rc, Matrix2D* transform, float alpha = 1.f, D3DXVECTOR2 offset = D3DXVECTOR2(0.f, 0.f));
	void FrameRender(string key,FloatRect rc, Matrix2D* transform, UINT frameX = 0, UINT frameY = 0, float alpha = 1.f, D3DXVECTOR2 offset = D3DXVECTOR2(0.f, 0.f));

	void DeleteTexture(string key);

	shared_ptr<Texture> FindTexture(string key);

private:
	typedef unordered_map<string, shared_ptr<Texture>>::iterator  Iter;
	unordered_map<string, shared_ptr<Texture>> textures;

	void AllDeleteTexture();


};

#define _ImageManager ImageManager::Get()
