//header file
#include "../includes/Shader.h"

//standard libraries
#include <fstream>
#include <sstream>
#include <iostream>

//OpenGL libraries
#include <glad/glad.h>

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	//string storing code 
	std::string vertexCode;
	std::string fragmentCode;
	//files storing shader code
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
		//open files
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);

		//declare variables of stringStream type to store contents of the files 
		std::stringstream vShaderStream, fShaderStream;
		//read content of file stream into variables
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		//close files
		vShaderFile.close();
		fShaderFile.close();

		vertexCode = vShaderStream.str();
		vertexText = vertexCode;
		fragmentCode = fShaderStream.str();


	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	//Success checking variables at end
	int  success;
	char infoLog[512];

	//creating run time vertex shader
	unsigned int vertexShaderID;
	vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderID, 1, &vShaderCode, NULL);
	glCompileShader(vertexShaderID);
	//error checking
	glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShaderID, 512, NULL, infoLog);
		std::cout << "\nERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	//creating run time fragment shader
	unsigned int fragmentShaderID;
	fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderID, 1, &fShaderCode, NULL);
	glCompileShader(fragmentShaderID);
	//error checking
	glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShaderID, 512, NULL, infoLog);
		std::cout << "\nERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	//creating the shader program, storing to ID attribute
	ID = glCreateProgram();
	//attach the shader programs and link
	glAttachShader(ID, vertexShaderID);
	glAttachShader(ID, fragmentShaderID);
	glLinkProgram(ID);

	//check compilation success of the shader Program
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "\nERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	//delete (the now) not needed shaders
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
}

void Shader::use() {
	glUseProgram(ID);
}

//get and set methods

unsigned int Shader::getID() {
	return ID;
}

std::string Shader::getVertexText() {
	return vertexText;
}