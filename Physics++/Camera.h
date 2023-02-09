#pragma once

#ifndef  _H_CAMERA_
#define _H_CAMERA_

#include "matrices.h"
#include "Geometry3D.h"

#endif

class Camera
{
public:
	Camera();
	inline virtual ~Camera() { }

	mat4 GetWorldMatrix();
	mat4 GetViewMatrix(); // View = inverse of world matrix
	mat4 GetProjectionMatrix();
	void SetProjection(const mat4& projection);
	void SetWorld(const mat4& view);
	float GetAstpect();
	bool IsOrthographic();
	bool IsPerspective();
	bool IsOrthoNormal();
	void OrthoNormalize();
	void Resize(int width, int height);
	void Perspective(float fov, float aspect, float zNear, float zFar);
	void Orthographic(float width, float height, float zNear, float zFar);
	Frustum GetFrustum();

protected:
	float m_nFOV;
	float m_nAspect;
	float m_nNear;
	float m_nFar;
	float m_nWidth;
	float m_nHeight;
	mat4 m_matWorld;
	mat4 m_matProj;
	int  m_nProjectionMode; // 0 = Perspective; 1 = Ortho; 2 = User
};

class OrbitCamera : public Camera
{
protected:
	vec3 target;
	vec2 panSpeed;
	float zoomDistance;
	vec2 zoomDistanceLimit; // x = min; y = max
	float zoomSpeed;
	vec2 rotationSpeed;
	vec2 yRotationLimit; // x = min; y = max
	vec2 currentRotation;

	float ClampAngle(float angle, float min, float max);

public:
	OrbitCamera();
	inline virtual ~OrbitCamera() { }

	void Rotate(const vec2& deltaRotation, float deltaTime);
	void Zoom(float deltaZoom, float deltaTime);
	void Pan(const vec2& deltaPan, float deltaTime);
	void Update(float deltaTime);
};