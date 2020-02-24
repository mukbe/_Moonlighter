#pragma once
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

#include "Mukbe.h"
#ifdef _DEBUG
#pragma comment(lib, "Mukbe.lib")
#else
#pragma comment(lib, "Release/Mukbe.lib")
#endif // _DEBUG

#include <d3dx10math.h>
#include "./Object/LightingSystem.h"
#include "./Object/GameData.h"
#include "./Object/BulletSystem.h"

#include "./Systems/SubSystemManager.h"