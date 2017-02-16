#pragma once
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "../bootstrap/gl_core_4_4.h"

#include <fstream>
#include <string.h>


//using
//----------------------------------------------
using glm::vec2;
using glm::vec3;
using glm::vec4;
using glm::mat2;
using glm::mat3;
using glm::mat4;


//Vertex Struct
//----------------------------------------------
struct Vertex { vec4 position; vec4 colour; };



//Mesh Class
//----------------------------------------------
class Mesh
{
public:
	Mesh();
	~Mesh();

	void StartUp();
	void GenerateGrid(unsigned int rows, unsigned int cols);
	void DrawElements(unsigned int rows, unsigned int cols, const mat4 & projectionViewMatrix);

	std::string LoadShader(const std::string path);

private:

	int m_rows, m_cols;

	unsigned int m_VAO; 
	unsigned int m_VBO; 
	unsigned int m_IBO;

	unsigned int m_programID;

	std::string vertexShaderPath = "Shaders/vertexShader_01.txt";
	std::string fragmentShaderPath = "Shaders/fragmentShader_01.txt";
};

