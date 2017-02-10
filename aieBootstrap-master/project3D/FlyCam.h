#pragma once
#include "Camera.h"
#include "Input.h"
#include <iostream>


class FlyCam : public Camera
{
public:
	FlyCam();
	virtual ~FlyCam();

	virtual void Update(float deltaTime, GLFWwindow* window);
	void SetSpeed(float speed);

	void KeyboardMovement(float deltaTime);
	void UpdateMouse(GLFWwindow* window);


private:
	float m_speed;
	vec3 m_up;

	float m_mouseX;
	float m_mouseY;
	float m_pmouseX;
	float m_pmouseY;

};

