#pragma once

#include "Mesh.h"
#include "FlyCam.h"
#include "Application.h"
#include <glm/mat4x4.hpp>
#include "ObjLoader.h"

class Application3D : public aie::Application {
public:

	Application3D();
	virtual ~Application3D();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	Camera* nicksFlyCam;
	int a;

	Mesh* m_mesh;
	ObjLoader* m_object;

};