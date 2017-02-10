#pragma once

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "../dependencies/glfw/include/GLFW/glfw3.h"

using glm::vec2;
using glm::vec3;
using glm::vec4;
using glm::mat4;

class Camera
{
public:
	Camera();
	virtual ~Camera();

	virtual void Update(float deltaTime, GLFWwindow *window) = 0;
	void SetPerspective(float fov, float aspectRatio, float near, float far);
	void SetLookAt(vec3 & from, vec3 & to, vec3 & up);
	void SetPosition(vec3 & position);
	void SetPositionRotation(vec3 pos, float pitch, float yaw, float roll);

	mat4 GetWorldTransform();
	mat4 GetView();
	mat4 GetProjection();
	mat4 GetProjectionView();
	vec3 GetRow(unsigned int index);

	void UpdateProjectionViewTransform();


protected:
	mat4 worldTransform;
	mat4 viewTransform;
	mat4 projectedTransform;
	mat4 projectedViewTransform;
};

