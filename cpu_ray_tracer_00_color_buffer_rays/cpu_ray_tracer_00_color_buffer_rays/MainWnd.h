#pragma once
#include <windows.h>

class MainWnd
{
public:
	MainWnd();
	~MainWnd();

protected:
	char* WindowName;
	HWND hWnd;
	int Width, Height, x, y, LastX, LastY;

public:
	bool Create(HINSTANCE hInstance, char* WindowName, int Width, int Height);
	void Repaint();
	void Show(bool Maximized = false);
	void MsgLoop();
	void Destroy();

	void OnKeyDown(UINT Key);
	void OnMouseMove(int X, int Y);
	void OnMouseWheel(short zDelta);
	void OnPaint();
	void OnRButtonDown(int X, int Y);
	void OnSize(int Width, int Height);
};

