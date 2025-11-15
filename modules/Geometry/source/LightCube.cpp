//header file
#include "../includes/LightCube.h"

//OpenGL libraries
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//standard libraries
#include <iostream>

LightCube::LightCube(glm::vec3 aPosition, glm::vec3 aColour, float aSideLength, VAO aVao, Shader aShader) {
	std::cout << "here!\n";
	vao = aVao;
	std::cout << "here!\n";
	shader = aShader;
	std::cout << "here!\n";

	updatePosition(aPosition);
	updateSideLength(aSideLength);
	setColour(aColour);
}

void LightCube::draw(glm::mat4 aViewMatrix, glm::mat4 aProjectionMatrix) {
	//calculate addresses of the different attributes to be passed as uniforms
	int scaleLocation = glGetUniformLocation(shader.getID(), "scale");
	int positionLocation = glGetUniformLocation(shader.getID(), "position");
	int viewLocation = glGetUniformLocation(shader.getID(), "view");
	int projectionLocation = glGetUniformLocation(shader.getID(), "projection");
	int colourLocation = glGetUniformLocation(shader.getID(), "colour");

	//use shader
	shader.use();

	//update uniforms
	glUniformMatrix4fv(scaleLocation, 1, GL_FALSE, glm::value_ptr(scaleMatrix));
	glUniformMatrix4fv(positionLocation, 1, GL_FALSE, glm::value_ptr(positionMatrix));
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(aViewMatrix));
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(aProjectionMatrix));
	glUniform3fv(colourLocation, 1, glm::value_ptr(colour));

	//bind the VAO
	vao.bind();

	//draw the cube
	glDrawElements(GL_TRIANGLES, 32, GL_UNSIGNED_INT, 0);
}

void LightCube::updatePosition(glm::vec3 aPosition) {
	position = aPosition;
	positionMatrix = glm::translate(glm::mat4(1.0f), aPosition);
}

void LightCube::updateSideLength(float aSideLength) {
	sideLength = aSideLength;
	scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(sideLength/2));
}

void LightCube::setColour(glm::vec3 aColour) {
	colour = aColour;
}