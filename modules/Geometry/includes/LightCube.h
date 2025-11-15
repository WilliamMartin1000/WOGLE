#pragma once

//OpenGL libraries
#include <glm/glm.hpp>

//GLStrucutre libraries
#include "../../GLStructure/includes/VAO.h"

class LightCube {
private:
	glm::vec3 position;
	float sideLength;

	//attribute storing the uniform data to be passed to a shader
	glm::mat4 positionMatrix;
	glm::mat4 scaleMatrix;
	glm::vec3 colour;

	//VAO for drawing
	VAO vao;
	Shader shader;

public:
	LightCube(glm::vec3 aPosition, glm::vec3 aColour, float aSideLength, VAO aVao, Shader aShader);

	void draw(glm::mat4 aViewMatrix, glm::mat4 aProjectionMatrix);

	void updatePosition(glm::vec3 aPosition);
	void updateSideLength(float aSideLength);
	void setColour(glm::vec3 aColour);
};