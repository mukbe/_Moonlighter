#include "Mukbe.h"
#include "ImageManager.h"


SingletonCpp(ImageManager)

ImageManager::ImageManager()
{
}


ImageManager::~ImageManager()
{
	AllDeleteTexture();
}

bool ImageManager::AddTexture(string key, wstring fileName)
{
	shared_ptr<Texture> temp = FindTexture(key);
	if (temp)
	{
		//LOG->Print("File : %s \n Line : %d \n Already Init this key", __FILE__, __LINE__);

		//LOG->Warning(__FILE__, __LINE__, "Already Init this key");
		return false;
	}


	textures.insert(make_pair(key, shared_ptr<Texture>(new Texture(fileName))));

	return true;
}

bool ImageManager::AddFrameTexture(string key, wstring fileName, UINT frameX, UINT frameY)
{
	shared_ptr<Texture> temp = FindTexture(key);
	if (temp)
	{
		//LOG->Warning(__FILE__, __LINE__, "Already Init this key");
		return false;
	}

	textures.insert(make_pair(key, shared_ptr<Texture>(new Texture(fileName, frameX, frameY))));

	return true;
}

void ImageManager::Render(string key, FloatRect rc, Matrix2D * transform, float alpha, D3DXVECTOR2 offset)
{
	shared_ptr<Texture> temp = FindTexture(key);
	if (temp == nullptr)
	{
		LOG->Warning(__FILE__, __LINE__, "Does not exist Texture");
		return;
	}
	temp->Render(rc, transform, alpha, offset);
}

void ImageManager::FrameRender(string key, FloatRect rc, Matrix2D * transform, UINT frameX, UINT frameY, float alpha, D3DXVECTOR2 offset)
{
	shared_ptr<Texture> temp = FindTexture(key);
	if (temp == nullptr)
	{
		LOG->Warning(__FILE__, __LINE__, "Does not exist Texture");
		return;
	}
	temp->FrameRender(rc, transform, frameX, frameY, alpha, offset);

}

shared_ptr<Texture> ImageManager::FindTexture(string key)
{
	Iter iter = textures.find(key);
	if (iter != textures.end())
	{
		return iter->second;
	}

//	LOG->Warning(__FILE__, __LINE__, "Can not found texrue");

	return nullptr;

}



void ImageManager::DeleteTexture(string key)
{
	Iter iter = textures.begin();

	for (;iter != textures.end(); ++iter)
	{
		if (iter->first == key)
		{
			textures.erase(iter);
			break;
		}
	}

}

void ImageManager::AllDeleteTexture()
{
	Iter iter = textures.begin();

	for (;iter != textures.end(); ++iter)
	{
		if (iter->second.use_count() != 1)
		{
			LOG->Warning(__FILE__, __LINE__, "shared_ptr<Testure> use count != 1");
		}

	}

	textures.clear();
}
