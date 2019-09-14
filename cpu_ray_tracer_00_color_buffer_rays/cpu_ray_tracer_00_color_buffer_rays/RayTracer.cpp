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
}

void RayTracer::Destroy()
{
}

void RayTracer::ClearColorBuffer()
{
}

void RayTracer::SwapBuffers(HDC hDC)
{
}
