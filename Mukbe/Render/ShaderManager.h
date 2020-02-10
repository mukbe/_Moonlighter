#pragma once

class ShaderManager
{
	SingletonHeader(ShaderManager)
public:
	shared_ptr<Shader> CreateShader(string key, wstring fileName, Shader::ShaderType type = Shader::ShaderType::Default, string funcName = "");
	shared_ptr<Shader> FindShader(string key);
	void BindShader(string key);
	void ReleaseShader();

	shared_ptr<class ComputeShader> CreateComputeShader(string key, wstring fileName, string entryPoint);
	shared_ptr<ComputeShader> FindComputeShader(string key);
private:
	typedef map<string, shared_ptr<Shader>> ShadersContain;
	typedef map<string, shared_ptr<Shader>>::iterator ShadersIter;
	typedef map<string, shared_ptr<ComputeShader>> ComputeShadersContain;
	typedef map<string, shared_ptr<ComputeShader>>::iterator ComputeShadersIter;

private:
	ShadersContain shaders;
	ComputeShadersContain computeShaders;
};

#define Shaders ShaderManager::Get()