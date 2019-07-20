#pragma once
#include <windows.h>
#include "glmath.h"

class Camera
{
public:
	Camera();
	~Camera();

public:
	vec3 X, Y, Z, Reference, Position;
	mat4x4 Vin, Pin, VPin, RayMatrix;

public:
	void CalculateRayMatrix();
	void Look(const vec3 &Position, const vec3 &Reference, bool RotateAroundReference = false);
	
	bool OnKeyDown(UINT nChar);
	void OnMouseMove(int dx, int dy);
	void OnMouseWheel(short zDelta);
};

