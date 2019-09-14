#include "Camera.h"



Camera::Camera()
{
}


Camera::~Camera()
{
}

void Camera::CalculateRayMatrix()
{
}

void Camera::Look(const vec3 & Position, const vec3 & Reference, bool RotateAroundReference)
{
}

bool Camera::OnKeyDown(UINT nChar)
{
	return false;
}

void Camera::OnMouseMove(int dx, int dy)
{
}

void Camera::OnMouseWheel(short zDelta)
{
}

void Camera::Resize(int Width, int Height)
{
	VPin[0] = 1.0f / (float)Width;
	VPin[5] = 1.0f / (float)Height;

	float tany = tan(45.0f / 360.0f * (float)M_PI), aspect = (float)Width / (float)Height;

	Pin[0] = tany * aspect;
	Pin[5] = tany;
	Pin[10] = 0.0f;
	Pin[14] = -1.0f;

	CalculateRayMatrix();
}