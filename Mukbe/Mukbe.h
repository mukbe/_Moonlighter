#pragma once


#define WIN32_LEAN_AND_MEAN          
#define _HAS_STD_BYTE 0

#include <windows.h>
#include <assert.h>

//STL
#include <string>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <functional>
#include <type_traits>

using namespace std;

//Direct3D
#include <dxgi1_2.h>
#include <d3dcommon.h>
#include <d3dcompiler.h>
#include <d3d11shader.h>
#include <d3d11.h>
#include <d3dx10math.h>
#include <d3dx11async.h>

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")

//다이렉트2D 라이브러리
#pragma comment(lib, "d2d1.lib")
#include <d2d1_1.h>
#include <d2d1helper.h>

//다이렉트 Write 라이브러리 (텍스트)
#pragma comment(lib, "dwrite.lib")
#include <dwrite.h>

//WIC 라이브러리
#pragma comment(lib, "WindowsCodecs.lib")
#include <wincodec.h>

//#define DEBUGMODE


//ImGui
#include <imgui.h>
#include <imguiDx11.h>
#include <imguiWin32.h>

#ifdef _DEBUG
#pragma comment(lib, "imgui.lib")
#else
#pragma comment(lib, "ImGui_Release.lib")
#endif // _DEBUG


//Json Cpp
#include <json/json.h>
#pragma comment(lib, "jsoncpp.lib")
//#pragma warning(disable:4996)

//DirectXTex
#include <DirectXTex.h>
#pragma comment(lib, "directxtex.lib")

//FMOD
#include <fmod/fmod.hpp>
#pragma comment(lib, "fmod/fmodex_vc.lib")

//#if defined(_DEBUG)
//#define _CRTDBG_MAP_ALLOC
//#define new new(_NORMAL_BLOCK,__FILE__,__LINE__)
//#endif



#include "EnumHelper.h"


#include "./Utilities/FloatRect.h"

const wstring ShaderPath = L"./Shaders/";
const wstring ResourcePath = L"../_Resources/";
const wstring LibPath = L"../_Libraries/";

#include "DefineHeader.h"
#include "./System/DxRenderer.h"
#include "./System/D2DRenderer.h"
#include "ModuleHeader.h"

#include "./Render/WorldBuffer.h"

#include "./System/Object/GameObject.h"








