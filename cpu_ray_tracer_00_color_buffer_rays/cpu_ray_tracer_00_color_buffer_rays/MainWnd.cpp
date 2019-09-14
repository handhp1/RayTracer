#include "MainWnd.h"
#include "RayTracer.h"
#include "Camera.h"
#include "glmath.h"
#include "cstring.h"

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

bool MainWnd::Create(HINSTANCE hInstance, char * WindowName, int Width, int Height)
{
	return false;
}

void MainWnd::Repaint()
{
}

void MainWnd::Show(bool Maximized)
{
}

void MainWnd::MsgLoop()
{
}

void MainWnd::Destroy()
{
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

		CString text = "Test";// WindowName;

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
}
