//header file
#include "../includes/Cube.h"

//OpenGL libraries
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//standard libraries
#include <iostream>

Cube::Cube(glm::vec3 aPosition, glm::vec3 aColour, float aSideLength, VAO aVao, Shader aShader) {
	vao = aVao;
	shader = aShader;

	//assign initial values of position and side length so as not to break update methods
	position = aPosition;
	positionMatrix = glm::translate(glm::mat4(1.0f), aPosition);
	sideLength = aSideLength;
	scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(sideLength / 2));
	updateModelMatrix();

	setColour(aColour);
}

void Cube::draw(glm::mat4 aViewMatrix, glm::mat4 aProjectionMatrix) {
	//use shader
	shader.use();
	//update the uniforms
	//world space uniforms
	shader.updateMat4("model", modelMatrix);
	shader.updateMat4("view", aViewMatrix);
	shader.updateMat4("projection", aProjectionMatrix);
	//colour uniform
	shader.updateVec3("colour", colour);

	//bind the VAO
	vao.bind();

	//draw the cube
	glDrawElements(GL_TRIANGLES, 32, GL_UNSIGNED_INT, 0);
}

void Cube::updatePosition(glm::vec3 aPosition) {
	position = aPosition;
	positionMatrix = glm::translate(glm::mat4(1.0f), aPosition);
	updateModelMatrix();
}

void Cube::updateSideLength(float aSideLength) {
	sideLength = aSideLength;
	scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(sideLength / 2));
	updateModelMatrix();
}

void Cube::updateModelMatrix() {
	modelMatrix = positionMatrix * scaleMatrix;
}

void Cube::setColour(glm::vec3 aColour) {
	colour = aColour;
}