#pragma once
//standard libraries
#include <vector>

//module header files
#include "../../../Game/includes/Wall.h"
#include "../includes/BSPTNode.h"


class BSPT {
private:
	//stores the root node of the BSP Tree
	BSPTNode* root;

public:
	//constructor - creates a BSPT out of a vector of walls
	BSPT(std::vector<Wall> vectorWalls);
	
	//returns whether a point is in a valid position
	bool navigatePoint(glm::vec3 aPoint);
	
	//returns whether a series of points are all in valid position, and if not, what plane they have collided with
	Wall navigatePoints(const std::vector<glm::vec3> aPointVector); //returns a Wall with normal = glm::vec3(0.0f) as true, to represent no collision
};