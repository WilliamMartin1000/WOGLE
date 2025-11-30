#pragma once

//OpenGL libraries
#include <glm/glm.hpp>

//GLStrucutre libraries
#include "../../../GLStructure/includes/VAO.h"
#include "../../../GLStructure/includes/Shader.h"


class Cube {
protected:
	glm::vec3 position;
	float sideLength;

	//attribute storing the uniform data to be passed to a shader
	glm::mat4 positionMatrix;
	glm::mat4 scaleMatrix;
	glm::mat4 modelMatrix;
	glm::vec3 colour;

	//VAO for drawing
	VAO vao;
	Shader shader;

public:
	Cube(glm::vec3 aPosition, glm::vec3 aColour, float aSideLength, VAO aVao, Shader aShader);

	void draw(glm::mat4 aViewMatrix, glm::mat4 aProjectionMatrix);

	void updatePosition(glm::vec3 aPosition);
	void updateSideLength(float aSideLength);
	void updateModelMatrix();
	void setColour(glm::vec3 aColour);
};