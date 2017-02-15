#include "Camera.h"



Camera::Camera()
{

}


Camera::~Camera()
{
}


//Functions
//-----------------------------------------------------------

void Camera::SetPerspective(float fov, float aspectRatio, float near, float far)
{
	projectedTransform = glm::perspective(fov, aspectRatio, near, far);
	UpdateProjectionViewTransform();
}

void Camera::SetLookAt(vec3 & from, vec3 & to, vec3 & up)
{
	viewTransform = glm::lookAt(from, to, up);
	worldTransform = glm::inverse(viewTransform);

	UpdateProjectionViewTransform();
}

void Camera::SetPosition(vec3 & position)
{
	worldTransform[3] = vec4(position, 1);
	viewTransform = glm::inverse(worldTransform);
	UpdateProjectionViewTransform();

}

void Camera::SetRotation(float pitch, float yaw, float roll)
{
	vec3 temp = worldTransform[3].xyz;
	worldTransform = glm::eulerAngleXYZ(pitch, yaw, roll);
	worldTransform[3] = vec4(temp, 1);
	viewTransform = glm::inverse(worldTransform);
	UpdateProjectionViewTransform();
}

void Camera::SetPositionRotation(vec3 pos, float pitch, float yaw, float roll)
{
	worldTransform = glm::eulerAngleXYZ(pitch, yaw, roll);
	worldTransform[3] = vec4(pos, 1);
	viewTransform = glm::inverse(worldTransform);
	UpdateProjectionViewTransform();
}



//Gets
//-----------------------------------------------------------

mat4 Camera::GetWorldTransform()
{
	return worldTransform;
}

mat4 Camera::GetView()
{
	return viewTransform;
}

mat4 Camera::GetProjection()
{
	return projectedTransform;
}

mat4 Camera::GetProjectionView()
{
	return projectedViewTransform;
}

vec3 Camera::GetRow(unsigned int index)
{
	vec3 row = worldTransform[index].xyz;
	return row;
}


//-----------------------------------------------------------

void Camera::UpdateProjectionViewTransform()
{
	projectedViewTransform = (projectedTransform * viewTransform);

}
