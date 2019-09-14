#include "RayTracer.h"


RayTracer::RayTracer()
{
	ColorBuffer = NULL;
}


RayTracer::~RayTracer()
{
}

bool RayTracer::Init()
{
	return true;
}

void RayTracer::RayTrace(int x, int y, mat4x4 rayMatrix)
{
	if (ColorBuffer != NULL)
	{
		vec4 rayDir = vec4((float)x + 0.5f, (float)y + 0.5f, 0.0f, 1.0f);
		vec3 Ray = normalize(*(vec3*)&(rayMatrix * rayDir));

		BYTE *colorbuffer = (LineWidth * y + x) * 3 + ColorBuffer;

		// gradation 
		colorbuffer[2] = Ray.r <= 0.0f ? 0 : Ray.r >= 1.0 ? 255 : (BYTE)(Ray.r * 255);
		colorbuffer[1] = Ray.g <= 0.0f ? 0 : Ray.g >= 1.0 ? 255 : (BYTE)(Ray.g * 255);
		colorbuffer[0] = Ray.b <= 0.0f ? 0 : Ray.b >= 1.0 ? 255 : (BYTE)(Ray.b * 255);
	}
}

void RayTracer::Resize(int Width, int Height)
{
	this->Width = Width;
	this->Height = Height;

	if (ColorBuffer != NULL)
	{
		delete[] ColorBuffer;
		ColorBuffer = NULL;
	}

	if (Width > 0 && Height > 0)
	{
		LineWidth = Width;

		int WidthMod4 = Width % 4;

		if (WidthMod4 > 0)
		{
			LineWidth += 4 - WidthMod4;
		}

		ColorBuffer = new BYTE[LineWidth * Height * 3];

		memset(&ColorBufferInfo, 0, sizeof(BITMAPINFOHEADER));
		ColorBufferInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		ColorBufferInfo.bmiHeader.biPlanes = 1;
		ColorBufferInfo.bmiHeader.biBitCount = 24;
		ColorBufferInfo.bmiHeader.biCompression = BI_RGB;
		ColorBufferInfo.bmiHeader.biWidth = LineWidth;
		ColorBufferInfo.bmiHeader.biHeight = Height;
	}
}

void RayTracer::Destroy()
{
	if (ColorBuffer != NULL)
	{
		delete[] ColorBuffer;
		ColorBuffer = NULL;
	}
}

void RayTracer::ClearColorBuffer()
{
	if (ColorBuffer != NULL)
	{
		memset(ColorBuffer, 0, LineWidth * Height * 3);
	}
}

void RayTracer::SwapBuffers(HDC hDC)
{
	if (ColorBuffer != NULL)
	{
		StretchDIBits(hDC, 0, 0, Width, Height, 0, 0, Width, Height, ColorBuffer, &ColorBufferInfo, DIB_RGB_COLORS, SRCCOPY);
	}
}
