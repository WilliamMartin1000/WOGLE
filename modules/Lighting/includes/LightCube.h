#pragma once

//OpenGL libraries
#include <glm/glm.hpp>

//Geometry libraries
#include "../../Geometry/Cubes/includes/Cube.h"

//GLStructure libraries
#include "../../GLStructure/includes/VAO.h"
#include "../../GLStructure/includes/Shader.h"

class LightCube : public Cube{
private:
	//light attributes
	glm::vec3 ambientStrength;
	glm::vec3 diffuseStrength;
	glm::vec3 specularStrength;


public:
	LightCube(glm::vec3 aPosition, glm::vec3 aColour, float aSideLength, VAO aVao, Shader aShader, glm::vec3 aAmbientStrength, glm::vec3 aDiffuseStrength, glm::vec3 aSpecularStrength);

	//get and set methods
	glm::vec3 getPosition();
	glm::vec3 getColour();
	glm::vec3 getAmbientStrength();
	glm::vec3 getDiffuseStrength();
	glm::vec3 getSpecularStrength();
};