#include "Mukbe.h"
#include "ShaderManager.h"
//#include "./ComputeShader/ComputeShader.h"

SingletonCpp(ShaderManager)

ShaderManager::ShaderManager()
{
}

ShaderManager::~ShaderManager()
{
	ShadersIter Iter = shaders.begin();

	for (Iter; Iter != shaders.end(); ++Iter)
	{
		if (Iter->second.use_count() != 1)
		{
			LOG->Warning(__FILE__, __LINE__, "shared_ptr<Shader> use count != 1");
		}
	}

	shaders.clear();
}

shared_ptr<Shader> ShaderManager::CreateShader(string key, wstring fileName, Shader::ShaderType type, string funcName)
{
	shared_ptr<Shader> shader;
	shader = FindShader(key);

	if (shader == nullptr)
	{
		shader = make_shared<Shader>(ShaderPath + fileName, type, funcName);
		shaders.insert(make_pair(key, shader));
	}

	return shader;
}

shared_ptr<Shader> ShaderManager::FindShader(string key)
{
	ShadersIter Iter = shaders.begin();

	for (Iter; Iter != shaders.end(); ++Iter)
	{
		if (key == Iter->first)
			return Iter->second;
	}

	return nullptr;
}

void ShaderManager::BindShader(string key)
{

	FindShader(key)->Render();

}

void ShaderManager::ReleaseShader()
{
	ID3D11DeviceChild* nullshader = {};

	DeviceContext->VSSetShader((ID3D11VertexShader*)nullshader, nullptr, 0);
	DeviceContext->PSSetShader((ID3D11PixelShader*)nullshader, nullptr, 0);
	DeviceContext->HSSetShader((ID3D11HullShader*)nullshader, nullptr, 0);
	DeviceContext->DSSetShader((ID3D11DomainShader*)nullshader, nullptr, 0);
	DeviceContext->GSSetShader((ID3D11GeometryShader*)nullshader, nullptr, 0);
}

//ComputeShader * ShaderManager::CreateComputeShader(string key, wstring fileName, string entryPoint)
//{
//
//	ComputeShader* shader;
//	shader = FindComputeShader(key);
//
//	if (shader == nullptr)
//	{
//		shader = new ComputeShader(ShaderPath + fileName, entryPoint);
//		computeShaders.insert(make_pair(key, shader));
//	}
//
//	return shader;
//}
//
//ComputeShader * ShaderManager::FindComputeShader(string key)
//{
//	ComputeShadersIter Iter = computeShaders.begin();
//
//	for (Iter; Iter != computeShaders.end(); ++Iter)
//	{
//		if (key == Iter->first)
//			return Iter->second;
//	}
//
//	return nullptr;
//}

