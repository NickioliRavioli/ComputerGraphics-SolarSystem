#pragma once
#include "Camera.h"
class FlyCam : public Camera
{
public:
	FlyCam();
	virtual ~FlyCam();

	//virtual void Update(float deltaTime);
	//void SetSpeed(float speed);

private:
	float speed;
	vec3 up;


};

