#include "FlyCam.h"



FlyCam::FlyCam()
{
	m_speed = 50;
	m_up = vec3(0, 1, 0);
}


FlyCam::~FlyCam()
{
}



//--------------------------------------------------------------
void FlyCam::Update(float deltaTime, GLFWwindow* window)
{
	KeyboardMovement(deltaTime);
	UpdateMouse(window);
	
}

void FlyCam::SetSpeed(float speed)
{
	m_speed = speed;
}



//--------------------------------------------------------------
void FlyCam::KeyboardMovement(float deltaTime)
{
	vec3 forward = GetRow(2);
	vec3 left = GetRow(0);
	vec3 up = GetRow(1);
	vec3 position = GetRow(3);

	if (aie::Input::getInstance()->isKeyDown(aie::INPUT_KEY_W))
	{
		position -= forward * deltaTime * m_speed;
	}
	if (aie::Input::getInstance()->isKeyDown(aie::INPUT_KEY_S))
	{
		position += forward * deltaTime * m_speed;
	}
	if (aie::Input::getInstance()->isKeyDown(aie::INPUT_KEY_A))
	{
		position -= left * deltaTime * m_speed;
	}
	if (aie::Input::getInstance()->isKeyDown(aie::INPUT_KEY_D))
	{
		position += left * deltaTime * m_speed;
	}
	if (aie::Input::getInstance()->isKeyDown(aie::INPUT_KEY_SPACE))
	{
		position += m_up * deltaTime * m_speed;
	}
	if (aie::Input::getInstance()->isKeyDown(aie::INPUT_KEY_LEFT_CONTROL))
	{
		position -= m_up * deltaTime * m_speed;
	}
	SetPosition(position);
}

void FlyCam::UpdateMouse(GLFWwindow* window)
{
	m_pmouseX = m_mouseX;
	m_pmouseY = m_mouseY;

	m_mouseX = aie::Input::getInstance()->getMouseX();
	m_mouseY = aie::Input::getInstance()->getMouseY();

	std::cout << m_mouseX - m_pmouseX << " " << m_mouseY- m_pmouseY << "\n";

}


