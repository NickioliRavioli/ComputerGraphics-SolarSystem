#pragma once
#include "tiny_obj_loader.h"
#include "../bootstrap/gl_core_4_4.h"
#include <string.h>

struct OpenGLInfo { unsigned int m_VAO; unsigned int m_VBO; unsigned int m_faceCount; };

struct OBJVertex { float x, y, z; float nx, ny, nz; float u, v; };

class ObjLoader
{
public:
	ObjLoader();
	ObjLoader(std::string objectPath);
	~ObjLoader();

	void load(std::string objectPath);
	void CreateOpenGLBuffers(tinyobj::attrib_t& attribs, std::vector<tinyobj::shape_t>& shapes);
	void DrawObj();

private:
	std::vector<OpenGLInfo> m_glInfo;

	std::string m_objectPath;
};

