#pragma once
#include <memory>

//가능하면 키값으로 렌더링을 하면 좋음
//shared_ptr을 사용하고 싶다면 shared_ptr<Texture> 를 선언해서 사용함
//기능은 전에 Texture클래스를 사용하는 방식하고 같다 => 자료형 형태만 다른것



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
