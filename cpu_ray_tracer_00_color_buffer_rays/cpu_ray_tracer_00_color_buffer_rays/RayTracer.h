#pragma once
#include <windows.h>
#include "glmath.h"

class RayTracer
{
public:
	RayTracer();
	~RayTracer();

private:
	BYTE *ColorBuffer;
	BITMAPINFO ColorBufferInfo;
	int Width, LineWidth, Height;

public:
	bool Init();
	void RayTrace(int x, int y, mat4x4 rayMatrix);
	void Resize(int Width, int Height);
	void Destroy();

	void ClearColorBuffer();
	void SwapBuffers(HDC hDC);
};

