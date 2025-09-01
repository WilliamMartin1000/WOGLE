#pragma once

//module header files
#include "../../Geometry/includes/Plane.h"
#include "../../GLStructure/includes/Texture.h"
#include <glm/glm.hpp>

class Wall : public Plane {
private:
	//vectoring storing the bounciness of the wall in what direction
	glm::vec3 bounciness;
	
	Texture wallTexture;

public:
	//constructor for 4 points of wall, bounciness and texture
	Wall(glm::vec3 pointA, glm::vec3 pointB, glm::vec3 pointC, glm::vec3 pointD, glm::vec3 aBounciness, Texture aWallTexture);
	//constructor for just normal (used for collision checking)
	Wall(glm::vec3 aNormal);
	//copy constructor
	Wall(const Wall& copyWall);
	//default constructor - does nothing
	Wall();

	//get and set methods
	glm::vec3 getBounciness();
	Texture getWallTexture();
};