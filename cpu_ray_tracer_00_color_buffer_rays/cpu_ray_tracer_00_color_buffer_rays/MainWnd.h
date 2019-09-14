#pragma once
#include <windows.h>
#include "cstring.h"

class RayTracer;
class Camera;

class MainWnd
{
public:
	MainWnd();
	~MainWnd();

protected:
	CString WindowName;
	HWND hWnd;
	int Width, Height, x, y, LastX, LastY;

	RayTracer* pRayTracer;
	Camera* pCamera;

public:
	bool Create(HINSTANCE hInstance, WCHAR* szTitle, WCHAR* szWindowClass, int Width, int Height);
	void Repaint();
	void Show(bool Maximized = false);
	void MsgLoop(HINSTANCE hInstance, LPWSTR INTRESOURCE);
	void Destroy();

	void OnKeyDown(UINT Key);
	void OnMouseMove(int X, int Y);
	void OnMouseWheel(short zDelta);
	void OnPaint();
	void OnRButtonDown(int X, int Y);
	void OnSize(int Width, int Height);
};

