#include "MainWnd.h"
#include "RayTracer.h"
#include "Camera.h"
#include "glmath.h"

MainWnd::MainWnd()
{
	pRayTracer = new RayTracer();
	pCamera = new Camera();
}


MainWnd::~MainWnd()
{
	delete pRayTracer;
	delete pCamera;
}

bool MainWnd::Create(HINSTANCE hInstance, WCHAR* szTitle, WCHAR* szWindowClass, int Width, int Height)
{
	this->Width = Width;
	this->Height = Height;

	DWORD Style = WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	if ((hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr)) == NULL)
	{
		//ErrorLog.Set("CreateWindowEx failed!");
		//TODO: ErrorLog
		return false;
	}

	return pRayTracer->Init();
}

void MainWnd::Repaint()
{
	x = y = 0;
	InvalidateRect(hWnd, NULL, FALSE);
}

void MainWnd::Show(bool Maximized)
{
	RECT dRect, wRect, cRect;

	GetWindowRect(GetDesktopWindow(), &dRect);
	GetWindowRect(hWnd, &wRect);
	GetClientRect(hWnd, &cRect);

	wRect.right += Width - cRect.right;
	wRect.bottom += Height - cRect.bottom;

	wRect.right -= wRect.left;
	wRect.bottom -= wRect.top;

	wRect.left = dRect.right / 2 - wRect.right / 2;
	wRect.top = dRect.bottom / 2 - wRect.bottom / 2;

	MoveWindow(hWnd, wRect.left, wRect.top, wRect.right, wRect.bottom, FALSE);

	ShowWindow(hWnd, Maximized ? SW_SHOWMAXIMIZED : SW_SHOWNORMAL);
}

void MainWnd::MsgLoop(HINSTANCE hInstance, LPWSTR INTRESOURCE)
{
	HACCEL hAccelTable = LoadAccelerators(hInstance, INTRESOURCE);

	MSG msg;

	// 기본 메시지 루프입니다:
	while (GetMessage(&msg, nullptr, 0, 0) > 0)
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}

void MainWnd::Destroy()
{
	pRayTracer->Destroy();

	DestroyWindow(hWnd);
}

void MainWnd::OnKeyDown(UINT Key)
{
}

void MainWnd::OnMouseMove(int X, int Y)
{
}

void MainWnd::OnMouseWheel(short zDelta)
{
}

void MainWnd::OnPaint()
{
	PAINTSTRUCT ps;
	HDC hDC = BeginPaint(hWnd, &ps);

	// TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
	static DWORD Start;
	static bool RayTracing;

	if (x == 0 && y == 0)
	{
		pRayTracer->ClearColorBuffer();
		Start = GetTickCount();
		RayTracing = true;
	}

	DWORD start = GetTickCount();

	while (GetTickCount() - start < 125 && y < Height)
	{
		int x16 = x + 16, y16 = y + 16;

		for (int yy = y; yy < y16; yy++)
		{
			if (yy < Height)
			{
				for (int xx = x; xx < x16; xx++)
				{
					if (xx < Width)
					{
						pRayTracer->RayTrace(xx, yy, pCamera->RayMatrix);
					}
					else
					{
						break;
					}
				}
			}
			else
			{
				break;
			}
		}

		x = x16;

		if (x >= Width)
		{
			x = 0;
			y = y16;
		}
	}

	pRayTracer->SwapBuffers(hDC);

	if (RayTracing)
	{
		if (y >= Height)
		{
			RayTracing = false;
		}

		DWORD End = GetTickCount();

		CString text = "CPU ray tracer 00 - Color buffer, rays";

		text.Append(" - %dx%d", Width, Height);
		text.Append(", Time: %.03f s", (float)(End - Start) * 0.001f);
				
		SetWindowText(hWnd, text);
		
		InvalidateRect(hWnd, NULL, FALSE);
	}

	//
	EndPaint(hWnd, &ps);
}

void MainWnd::OnRButtonDown(int X, int Y)
{
}

void MainWnd::OnSize(int Width, int Height)
{
	this->Width = Width;
	this->Height = Height;

	pRayTracer->Resize(Width, Height);

	Repaint();
}
