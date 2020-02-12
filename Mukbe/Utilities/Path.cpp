#include "Mukbe.h"
#include "Path.h"
#include <string.h>
#include "String.h"

bool Path::ExistFile(string path)
{
	return ExistFile(String::StringToWString(path));
}

bool Path::ExistFile(wstring path)
{
	DWORD fileValue = GetFileAttributes(path.c_str());

	return fileValue < 0xFFFFFFFF;
}

string Path::Combine(string path1, string path2)
{
	return path1 + path2;
}

wstring Path::Combine(wstring path1, wstring path2)
{
	return path1 + path2;
}

bool Path::ExistDirectory(wstring path)
{
	DWORD attribute = GetFileAttributes(path.c_str());

	BOOL temp = (attribute != INVALID_FILE_ATTRIBUTES &&
		(attribute & FILE_ATTRIBUTE_DIRECTORY));

	return temp == TRUE;
}

string Path::Combine(vector<string> paths)
{
	string temp = "";
	for (string path : paths)
		temp += path;

	return temp;
}

wstring Path::Combine(vector<wstring> paths)
{
	wstring temp = L"";
	for (wstring path : paths)
		temp += path;

	return temp;
}

string Path::GetDirectoryName(string path)
{
	size_t index = path.find_last_of('/');

	return path.substr(0, index + 1);
}

wstring Path::GetDirectoryName(wstring path)
{
	size_t index = path.find_last_of('/');

	return path.substr(0, index + 1);
}

string Path::GetExtension(string path)
{
	size_t index = path.find_last_of('.');

	return path.substr(index + 1, path.length());
}

wstring Path::GetExtension(wstring path)
{
	size_t index = path.find_last_of('.');

	return path.substr(index + 1, path.length());
}

string Path::GetFileName(string path)
{
	size_t index = path.find_last_of('/');

	return path.substr(index + 1, path.length());
}

wstring Path::GetFileName(wstring path)
{
	size_t index = path.find_last_of('/');

	return path.substr(index + 1, path.length());
}

string Path::GetFileNameWithoutExtension(string path)
{
	string fileName = GetFileName(path);

	size_t index = fileName.find_last_of('.');
	return fileName.substr(0, index);
}

wstring Path::GetFileNameWithoutExtension(wstring path)
{
	wstring fileName = GetFileName(path);

	size_t index = fileName.find_last_of('.');
	return fileName.substr(0, index);
}

string Path::GetFilePathWithoutExtension(string path)
{
	size_t index = path.find_last_of('.');
	return path.substr(0, index);
}

wstring Path::GetFilePathWithoutExtension(wstring path)
{
	size_t index = path.find_last_of('.');
	return path.substr(0, index);
}


const WCHAR* Path::ImageFilter = L"Image\0*.png;*.bmp;*.jpg";
const WCHAR* Path::BinModelFilter = L"Binary Model\0*.model";
const WCHAR* Path::FbxModelFilter = L"Fbx Model\0*.fbx;*.obj\0";
const WCHAR* Path::ShaderFilter = L"HLSL file\0*.hlsl";
const WCHAR* Path::MaterialFilter = L"Material file\0*.material";
const WCHAR* Path::MeshFilter = L"Mesh file\0*.mesh";
const WCHAR* Path::AnimationFilter = L"Animation file\0*.anim";
const WCHAR* Path::ColliderFilter = L"Collider file\0*.collider";
const WCHAR* Path::Mp3Filter = L"Mp3 file\0*.mp3";
const WCHAR* Path::JsonFilter = L"Json file\0*.json";

void Path::OpenFileDialog(wstring file, const WCHAR* filter, wstring folder, function<void(wstring)> func, HWND hwnd)
{
	WCHAR name[255];
	wcscpy_s(name, file.c_str());

	wstring tempFolder = folder;
	String::Replace(&tempFolder, L"/", L"\\");
	
	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hwnd;
	ofn.lpstrFilter = filter;
	ofn.lpstrFile = name;
	//ofn.lpstrFileTitle = L"ºÒ·¯¿À±â";
	ofn.nMaxFile = 255;
	ofn.lpstrInitialDir = folder.c_str();
	ofn.Flags = OFN_NOCHANGEDIR;

	if (GetOpenFileName(&ofn) == TRUE)
	{
		if (func != NULL)
		{
			wstring loadName = name;
			String::Replace(&loadName, L"\\", L"/");

			func(loadName);
		}
	}
}

void Path::SaveFileDialog(wstring file, const WCHAR* filter, wstring folder, function<void(wstring)> func, HWND hwnd)
{
	WCHAR name[255];
	wcscpy_s(name, file.c_str());

	wstring tempFolder = folder;
	String::Replace(&tempFolder, L"/", L"\\");

	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hwnd;
	ofn.lpstrFilter = filter;
	ofn.lpstrFile = name;
	//ofn.lpstrFileTitle = L"ÀúÀåÇÏ±â";
	ofn.nMaxFile = 255;
	ofn.lpstrInitialDir = tempFolder.c_str();
	ofn.Flags = OFN_NOCHANGEDIR;

	if (GetSaveFileName(&ofn) == TRUE)
	{
		if (func != NULL)
		{
			wstring loadName = name;
			String::Replace(&loadName, L"\\", L"/");
			
			func(loadName);
		}
	}
}

//FileSearch함수가 사용할 확인용 함수
int Path::isFileOrDir(_wfinddata_t fd)
{
	if (fd.attrib & _A_SUBDIR)
		return 0; // 디렉토리면 0 반환
	else
		return 1; // 그밖의 경우는 "존재하는 파일"이기에 1 반환
}

//들어온 경로에서 모든 폴더를 순회하며 func실행
void Path::FileSearch(WCHAR file_path[], function<void(wstring)> func)
{
	_wfinddata_t fd;
	intptr_t handle;
	int check = 0;
	WCHAR file_path2[_MAX_PATH];

	lstrcat(file_path, L"\\");
	lstrcpy(file_path2, file_path);
	lstrcat(file_path, L"*");

	if ((handle = _wfindfirst(file_path, &fd)) == -1)
	{
		wprintf(L"No such file or directory\n");
		return;
	}

	while (_wfindnext(handle, &fd) == 0)
	{
		WCHAR file_pt[_MAX_PATH];
		lstrcpy(file_pt, file_path2);
		lstrcat(file_pt, fd.name);

		check = isFileOrDir(fd);    //파일인지 디렉토리 인지 식별

		if (check == 0 && fd.name[0] != '.')
		{
			FileSearch(file_pt,func);    //하위 디렉토리 검색 재귀함수
		}
		else if (check == 1 && fd.size != 0 && fd.name[0] != '.')
		{
			func(file_pt);
			wprintf(L"파일명 : %s, 크기:%d\n", file_pt, fd.size);
		}
	}
	_findclose(handle);
}
