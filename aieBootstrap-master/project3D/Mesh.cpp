#include "Mesh.h"
#include <iostream>

Mesh::Mesh()
{
	StartUp();
}


Mesh::~Mesh()
{
}

void Mesh::StartUp()
{
	//Create Shaders
	//----------------------------------------------
	/*
	//const char* vsSource = "#version 410\n \ layout(location=0) in vec4 position; \ layout(location=1) in vec4 colour; \ out vec4 vColour; \ uniform mat4 projectionViewWorldMatrix; \ void main() { vColour = colour; gl_Position = projectionViewWorldMatrix * position; }";
	const char* vsSource = 
		"#version 410\n \
		layout(location=0) in vec4 position; \
		layout(location=1) in vec4 colour; \
		out vec4 vColour; \
		uniform mat4 projectionViewWorldMatrix; \
		\
		uniform float time; \
		uniform float heightScale; \
		void main() { vColour = colour; vec4 P = position; \
		P.y += sin( time + position.x/3 ) * heightScale; \
		gl_Position = projectionViewWorldMatrix * P; }";


	const char* fsSource = "#version 410\n \ in vec4 vColour; \ out vec4 fragColor; \ void main() { fragColor = vColour; }";
	*/
	
	std::string a = LoadShader(vertexShaderPath);
	std::string b = LoadShader(fragmentShaderPath);

	const char* vsSource = a.c_str();
	const char* fsSource = b.c_str();

	std::cout << a << "\n" << b;
	

	int success = GL_FALSE;
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vertexShader, 1, (const char**)&vsSource, 0);
	glCompileShader(vertexShader);
	glShaderSource(fragmentShader, 1, (const char**)&fsSource, 0); 
	glCompileShader(fragmentShader); 

	
	//glBindAttribLocation();

	m_programID = glCreateProgram(); 
	glAttachShader(m_programID, vertexShader); 
	glAttachShader(m_programID, fragmentShader); 
	glLinkProgram(m_programID); 

	glGetProgramiv(m_programID, GL_LINK_STATUS, &success); 
	if (success == GL_FALSE) 
	{ 
		int infoLogLength = 0; 
		glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &infoLogLength); 
		char* infoLog = new char[infoLogLength]; 
		glGetProgramInfoLog(m_programID, infoLogLength, 0, infoLog); 
		printf("Error: Failed to link shader program!\n"); 
		printf("%s\n", infoLog); 
		delete[] infoLog; 
	} 

	glDeleteShader(fragmentShader); 
	glDeleteShader(vertexShader);
}

void Mesh::GenerateGrid(unsigned int rows, unsigned int cols)
{

	//Creating Vertexs
	//----------------------------------------------
	Vertex* aoVertices = new Vertex[rows * cols];
	for (unsigned int r = 0; r < rows; ++r)
	{
		for (unsigned int c = 0; c < cols; ++c)
		{
			aoVertices[r * cols + c].position = vec4((float)c - cols/2.0f, -0.1f , (float)r - rows/2.0f, 1);
			// create some arbitrary colour based off something 
			// that might not be related to tiling a texture 
			vec3 colour = vec3(r / (float)rows, 1, c / (float)cols); //vec3(sinf((c / (float)(cols - 1)) * (r / (float)(rows - 1))));
			aoVertices[r * cols + c].colour = vec4(colour, 1);
		}
	}


	//Creating Indices
	//----------------------------------------------
	unsigned int* auiIndices = new unsigned int[(rows - 1) * (cols - 1) * 6];

	unsigned int index = 0;
	for (unsigned int r = 0; r < (rows - 1); ++r)
	{
		for (unsigned int c = 0; c < (cols - 1); ++c)
		{
			//triangle 1 (0,0) -> (1,0) -> (1,1)
			auiIndices[index++] = r * cols + c;
			auiIndices[index++] = (r + 1) * cols + c;
			auiIndices[index++] = (r + 1) * cols + (c + 1);

			//triangle 2 (0,0) -> (1,1) -> (0,1)
			auiIndices[index++] = r * cols + c;
			auiIndices[index++] = (r + 1) * cols + (c + 1);
			auiIndices[index++] = r * cols + (c + 1);
		}
	}

	//Creating Vertex buffer, indices buffer, Vertex Array
	//--------------------------------------------------------------------------------------------
	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_IBO);

	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	//bind and fill Vertex buffer
	//----------------------------------------------
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, (rows * cols) * sizeof(Vertex), aoVertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(vec4)));

	//dont need
	//glBindBuffer(GL_ARRAY_BUFFER, 0);

	//bind and fill indices buffer
	//----------------------------------------------
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (rows - 1) * (cols - 1) * 6 * sizeof(unsigned int), auiIndices, GL_STATIC_DRAW);

	//dont need
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//bind Vertex Array Object
	//--------------------------------------------------------------------------------------------

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//Delete objects
	//----------------------------------------------
	delete[] auiIndices;
	delete[] aoVertices;
}



void Mesh::DrawElements(unsigned int rows, unsigned int cols, const mat4 & projectionViewMatrix)
{
	//Draw Elements
	//----------------------------------------------

	static float m_time = 0;
	m_time +=.1f;
	static float m_heightScale = 2;


	glUseProgram(m_programID);
	unsigned int ProjectionViewUniform = glGetUniformLocation(m_programID, "projectionViewWorldMatrix");
	glUniformMatrix4fv(ProjectionViewUniform, 1, false, glm::value_ptr(projectionViewMatrix));

	unsigned int time = glGetUniformLocation(m_programID, "time");
	glUniform1f(time, m_time);

	unsigned int heightScale = glGetUniformLocation(m_programID, "heightScale");
	glUniform1f(heightScale, m_heightScale);


	glBindVertexArray(m_VAO);
	unsigned int indexCount = (rows - 1) * (cols - 1) * 6;
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
}

std::string Mesh::LoadShader(const std::string path)
{
	std::string line;
	std::string output;

	std::ifstream myFile;
	myFile.open(path);

	if (myFile.is_open())
	{
		while (!myFile.eof())
		{
			std::getline(myFile, line);
			output += line + '\n';
		}
	}
	myFile.close();

	return output;
}

