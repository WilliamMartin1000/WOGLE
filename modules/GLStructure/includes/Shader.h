#pragma once
//Class structure copied from Learn OpenGL https://learnopengl.com/Getting-started/Shaders

//standard libraries
#include <string>

//OpenGL libraries
#include <glm/glm.hpp>


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

	//update uniforms
	void updateVec3(std::string vecName, glm::vec3 vecValue);
	void updateMat4(std::string matName, glm::mat4 matValue);
	void updateFloat(std::string floatName, float floatValue);

	//get and set methods

	unsigned int getID();

	std::string getVertexText();


};