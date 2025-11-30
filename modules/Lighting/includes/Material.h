#pragma once

//OpenGL libraries
#include <glm/glm.hpp>

//GLStructure
#include "../../GLStructure/includes/Texture.h"

class Material {
private:
	Texture ambient;
	Texture diffuse;
	Texture specular;
	float shininess;
public:
	Material(Texture aAmbient, Texture aDiffuse, Texture aSpecular, float aShininess);
	Material();
	Material(const Material& copyMaterial);


	//get and set methods;
	Texture getAmbient();
	Texture getDiffuse();
	Texture getSpecular();
	float getShininess();
};