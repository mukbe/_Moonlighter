#include "stdafx.h"
#include "Window.h"
#include "../Program.h"

Program* Window::program = nullptr;
bool Window::bUseImguiUI = true;

WPARAM Window::Run()
{
	MSG msg = { 0 };

	//=========Init Manager=================================
	CreateManagers();
	Window::bUseImguiUI = false;
	//=====================================================

	program = new Program();
	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			Time::Get()->Update();
			Keyboard::Get()->Update();
			CameraManager::Get()->Update();

			//imgui UI���� ���콺 ������ ���� ȭ�鿡�� Ű�����ϰ� ���콺 ���� �Ⱥ��� => imgui�� ������ ���ؼ�
			if (ImGui::IsAnyWindowFocused() == false && ImGui::IsAnyWindowHovered() == false)
			{
				Mouse::Get()->Update();
			}
			SoundManager::Get()->Update();
			program->PreUpdate();
			program->Update(Time::Tick());
			program->PostUpdate();

			{//imgui Update
				ImGui_ImplDX11_NewFrame();
				ImGui_ImplWin32_NewFrame();
				ImGui::NewFrame();
			}

			{//������ ����

				//������Ʈ��				D2D
				//����Ʈ					D3D
				//���ӿ� ����� UI		D2D
				//������ Imgui			D3D


				//TODO Program Class�� ó���ϰ� �ٸ� �̸����� �ο� Render ���� d2d���� �������� ������ ������ ó��
				//d3d���� ��ƼŬ�� �������� ó����(ComputeShader �����;ߵ�)

				//�⺻���� Draw�� d2d
				p2DRenderer->BeginDraw();
				{
					program->Render();
				}
				p2DRenderer->EndDraw();

				//����Ʈó���� d3d
				pRenderer->BeginDrawWithoutClear();
				{

					//==============================�ٲ�� �ȵ�=====================================================
					//����Ÿ���� ���ε��� Ǯ���ٶ� d3d�� �׷��� �������� ���ۿ� �׷�����
					//���� �ٽ� ���ε��� ���ָ� ������ۿ� ���ݱ��� �׷��� �ȼ������� ����

					program->PostRender();

					//=============================================================================================

					p2DRenderer->BeginDrawWithoutClear();
					{
						//d2d�� �׸� UI�� ���⼭ �������ؾ���
						program->GameUIRender();
					}
					p2DRenderer->EndDraw();


					if (Keyboard::Get()->Down(VK_F8))
					{
						Window::bUseImguiUI = !Window::bUseImguiUI;
					}

					if (bUseImguiUI)
					{
						program->ImguiRender();
						LOG->ImShowData();

						static bool bImguiWin = true;
						ImGui::ShowDemoWindow(&bImguiWin);
					}

					ImGui::Render();
					ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
				}
				pRenderer->EndDraw();
			}
		}
	}
	SafeDelete(program);

	//================Release Manager==============================
	DeletaManagers();
	//=============================================================

	return msg.wParam;
}

Window::Window()
{
	D3DDesc desc;
	DxRenderer::GetDesc(&desc);

	WNDCLASSEX wndClass;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wndClass.hIconSm = wndClass.hIcon;
	wndClass.hInstance = desc.Instance;
	wndClass.lpfnWndProc = (WNDPROC)WndProc;
	wndClass.lpszClassName = desc.AppName.c_str();
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wndClass.cbSize = sizeof(WNDCLASSEX);

	WORD wHr = RegisterClassEx(&wndClass);
	assert(wHr != 0);

	if (desc.bFullScreen == true)
	{
		DEVMODE devMode = { 0 };
		devMode.dmSize = sizeof(DEVMODE);
		devMode.dmPelsWidth = (DWORD)desc.Width;
		devMode.dmPelsHeight = (DWORD)desc.Height;
		devMode.dmBitsPerPel = 32;
		devMode.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		ChangeDisplaySettings(&devMode, CDS_FULLSCREEN);
	}

	desc.Handle = CreateWindowEx
	(
		WS_EX_APPWINDOW
		, desc.AppName.c_str()
		, desc.AppName.c_str()
		, WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_OVERLAPPEDWINDOW
		, CW_USEDEFAULT
		, CW_USEDEFAULT
		, CW_USEDEFAULT
		, CW_USEDEFAULT
		, NULL
		, (HMENU)NULL
		, desc.Instance
		, NULL
	);
	assert(desc.Handle != NULL);
	DxRenderer::SetDesc(desc);


	RECT rect = { 0, 0, (LONG)desc.Width, (LONG)desc.Height };

	UINT centerX = (GetSystemMetrics(SM_CXSCREEN) - (UINT)desc.Width) / 2;
	UINT centerY = (GetSystemMetrics(SM_CYSCREEN) - (UINT)desc.Height) / 2;

	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);
	MoveWindow
	(
		desc.Handle
		, centerX, centerY
		, rect.right - rect.left, rect.bottom - rect.top
		, TRUE
	);
	ShowWindow(desc.Handle, SW_SHOWNORMAL);
	SetForegroundWindow(desc.Handle);
	SetFocus(desc.Handle);

	ShowCursor(true);
}

Window::~Window()
{
	D3DDesc desc;
	DxRenderer::GetDesc(&desc);

	if (desc.bFullScreen == true)
		ChangeDisplaySettings(NULL, 0);

	DestroyWindow(desc.Handle);

	UnregisterClass(desc.AppName.c_str(), desc.Instance);
}

LRESULT CALLBACK Window::WndProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{

	Mouse::Get()->InputProc(message, wParam, lParam);
	
	//imgui_win32 ����� �ּ�ó�� �Ǿ��ִ°� Ǯ���־�� �ν���
	if (ImGui_ImplWin32_WndProcHandler(handle, message, wParam, lParam))
		return true;

	if (message == WM_SIZE)
	{
		ImGui_ImplDX11_InvalidateDeviceObjects();
		{
			if (program != NULL)
			{
				float width = (float)LOWORD(lParam);
				float height = (float)HIWORD(lParam);

				if (pRenderer != NULL)

					//TODO
					//pRenderer->ResizeScreen(width, height);
					program->ResizeScreen();
			}
		}
		ImGui_ImplDX11_CreateDeviceObjects();
	}


	if (message == WM_CLOSE || message == WM_DESTROY)
	{
		PostQuitMessage(0);

		return 0;
	}

	return DefWindowProc(handle, message, wParam, lParam);
}

void Window::CreateManagers()
{
	Logging::Create();
	LOG->Init();

	DxRenderer::Create();
	pRenderer->CreateDevice();
	pRenderer->CreateSwapChain();
	D2DRenderer::Create();
	p2DRenderer->Create2DBuffer();
	ImageManager::Create();

	Keyboard::Create();
	Mouse::Create();
	CameraManager::Create();
	SoundManager::Create();

	Time::Create();
	Time::Get()->Start();
	BufferManager::Create();
	ShaderManager::Create();

	EffectManager::Create();
	SceneManager::Create();

	{//Imgui Init
		D3DDesc desc;
		DxRenderer::GetDesc(&desc);

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		ImGui_ImplWin32_Init(desc.Handle);
		ImGui_ImplDX11_Init(Device, DeviceContext);
		ImGui::StyleColorsDark();
	}
}

void Window::DeletaManagers()
{
	ImGui_ImplDX11_Shutdown();

	SceneManager::Delete();
	EffectManager::Delete();

	ShaderManager::Delete();
	BufferManager::Delete();
	Time::Delete();

	SoundManager::Delete();
	CameraManager::Delete();
	Mouse::Delete();
	Keyboard::Delete();

	_ImageManager->AllDeleteTexture();
	ImageManager::Delete();
	D2DRenderer::Delete();
	pRenderer->Delete();
	LOG->Release();
	Logging::Delete();

}

