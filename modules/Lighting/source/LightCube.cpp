//header file
#include "../includes/LightCube.h"

//OpenGL libraries
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//standard libraries
#include <iostream>

LightCube::LightCube(glm::vec3 aPosition, glm::vec3 aColour, float aSideLength, VAO aVao, Shader aShader, glm::vec3 aAmbientStrength, glm::vec3 aDiffuseStrength, glm::vec3 aSpecularStrength) : Cube(aPosition, aColour, aSideLength, aVao, aShader){
	ambientStrength = aAmbientStrength;
	diffuseStrength = aDiffuseStrength;
	specularStrength = aSpecularStrength;
}

//get and set methods

glm::vec3 LightCube::getPosition() {
	return position;
}

glm::vec3 LightCube::getColour() {
	return colour;
}

glm::vec3 LightCube::getAmbientStrength() {
	return ambientStrength;
}

glm::vec3 LightCube::getDiffuseStrength() {
	return diffuseStrength;
}

glm::vec3 LightCube::getSpecularStrength() {
	return specularStrength;
}
