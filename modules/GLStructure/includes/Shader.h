#pragma once
//Class structure copied from Learn OpenGL https://learnopengl.com/Getting-started/Shaders

//standard libraries
#include <string>

class Shader
{
private:
	//stores the contents of the shader file in text
	std::string vertexText;
	//ID for shader
	unsigned int ID;

public:

	Shader(const char* vertexPath, const char* fragmentPath);
	Shader();
	Shader(const Shader& copyShader); //copy constructor

	void use();

	//get and set methods

	unsigned int getID();

	std::string getVertexText();


};