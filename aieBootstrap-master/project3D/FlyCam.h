#pragma once
#define _USE_MATH_DEFINES

#include "Camera.h"
#include "Input.h"
#include <iostream>
#include <math.h>


class FlyCam : public Camera
{
public:
	FlyCam();
	virtual ~FlyCam();

	virtual void Update(float deltaTime, GLFWwindow* window);
	void SetSpeed(float speed);

	void KeyboardMovement(float deltaTime);
	void UpdateMouse(GLFWwindow* window);
	void MouseMovement(float deltaTime);

private:
	float m_moveSpeed;
	float m_mouseSpeed;

	vec3 m_up;

	double m_mouseX;
	double m_mouseY;
	double m_pmouseX;
	double m_pmouseY;

	float deltaX;
	float deltaY;

	float m_pitch;
	float m_yaw;


	int windowHeight;
	int windowWidth;
};

