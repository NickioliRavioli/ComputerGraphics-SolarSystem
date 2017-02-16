#include "FlyCam.h"



FlyCam::FlyCam()
{
	m_moveSpeed = 10;
	m_mouseSpeed = .006f; 
	
	m_up = vec3(0, 1, 0);

	m_mouseX = aie::Input::getInstance()->getMouseX();
	m_mouseY = aie::Input::getInstance()->getMouseY();
	m_pmouseX = m_mouseX;
	m_pmouseY = m_mouseY;
	m_pitch = 0;
	m_yaw = 0;

	deltaX = 0;
	deltaY = 0;

	m_windowName = GetForegroundWindow();
}


FlyCam::~FlyCam()
{
}



//--------------------------------------------------------------
bool FlyCam::IsWindowInFocus()
{
	if (m_windowName == GetForegroundWindow())
		return true;
	return false;
}



//--------------------------------------------------------------
void FlyCam::Update(float deltaTime, GLFWwindow* window)
{
	glfwGetWindowSize(window, &windowWidth, &windowHeight);

	if (IsWindowInFocus())
	{
		KeyboardMovement(deltaTime);
		UpdateMouse(window);
	}




}

void FlyCam::SetSpeed(float speed)
{
	m_moveSpeed = speed;
}



//--------------------------------------------------------------
void FlyCam::KeyboardMovement(float deltaTime)
{
	vec3 forward = GetRow(2);
	vec3 left = GetRow(0);
	vec3 up = GetRow(1);
	vec3 position = GetRow(3);

	if (aie::Input::getInstance()->isKeyDown(aie::INPUT_KEY_LEFT_SHIFT))
		m_moveSpeed = 20;
	else
		m_moveSpeed = 10;

	if (aie::Input::getInstance()->isKeyDown(aie::INPUT_KEY_W))
		position -= forward * deltaTime * m_moveSpeed;
	if (aie::Input::getInstance()->isKeyDown(aie::INPUT_KEY_S))
		position += forward * deltaTime * m_moveSpeed;
	if (aie::Input::getInstance()->isKeyDown(aie::INPUT_KEY_A))
		position -= left * deltaTime * m_moveSpeed;
	if (aie::Input::getInstance()->isKeyDown(aie::INPUT_KEY_D))
		position += left * deltaTime * m_moveSpeed;
	if (aie::Input::getInstance()->isKeyDown(aie::INPUT_KEY_SPACE))
		position += m_up * deltaTime * m_moveSpeed;
	if (aie::Input::getInstance()->isKeyDown(aie::INPUT_KEY_LEFT_CONTROL))
		position -= m_up * deltaTime * m_moveSpeed;
	SetPosition(position);
}

void FlyCam::UpdateMouse(GLFWwindow* window)
{
	mat4 currentTransform = GetWorldTransform();
	currentTransform[3] = vec4(0, 0, 0, 1);

	/*
	m_pmouseX = m_mouseX;
	m_pmouseY = m_mouseY;

	glfwGetCursorPos(window, &m_mouseX, &m_mouseY);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	*/


	m_pmouseX = windowWidth / 2;
	m_pmouseY = windowHeight / 2;

	glfwGetCursorPos(window, &m_mouseX, &m_mouseY);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	glfwSetCursorPos(window, windowWidth / 2, windowHeight / 2);


	static float deltaX = 0;
	static float deltaY = 0;

	deltaX = m_mouseX - m_pmouseX;
	deltaY = m_mouseY - m_pmouseY;
	
	//limit the mouse delta
	deltaX = fmin(30.0f, fmax(deltaX, -30.0f));
	deltaY = fmin(30.0f, fmax(deltaY, -30.0f));

	m_yaw += deltaX;
	m_pitch += deltaY;

	mat4 rotation = glm::rotate((float)-deltaX * m_mouseSpeed, m_up); // rotate around Vec3(0,1,0)
	rotation *= glm::rotate((float)-deltaY * m_mouseSpeed, GetRow(0)); // rotate around left

	currentTransform = rotation * currentTransform;
	currentTransform[3] = vec4(GetRow(3), 1);
	worldTransform = currentTransform;

	
	//std::cout << "window W&H " << windowWidth << " " << windowHeight << "\n";
	//std::cout << "mousePos " << m_mouseX << " " << m_mouseY << "\n";
	//std::cout << "Yaw Pitch " << m_yaw << " " << m_pitch << "\n";

}





