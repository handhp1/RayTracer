#include "MainWnd.h"



MainWnd::MainWnd()
{
}


MainWnd::~MainWnd()
{
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
	HDC hdc = BeginPaint(hWnd, &ps);
	// TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
	EndPaint(hWnd, &ps);
}

void MainWnd::OnRButtonDown(int X, int Y)
{
}

void MainWnd::OnSize(int Width, int Height)
{
}
