#pragma once

//OpenGL libraries
#include <glm/glm.hpp>

//constant for number of vertices on the plane
const int numberOfVertices = 4;

class Plane {
protected:
	//mathematical value attributes
	glm::vec3 normal;
	float doProValue;
	
	//center of plane
	glm::vec3 center;

	//initialises/sets values of the different arrays
	void setVertexArrayVertices();
	void setVertexArrayColours(glm::vec3 aColour);
	void setVertexArrayTextures();

public:
	//array of corners of plane
	glm::vec3 vertices[4];
	//array storing vertex data
	float vertexArray[numberOfVertices * 8];
	//array storing index data
	int indexArray[6] =
	{ 0, 1, 2,
	 1, 2, 3 }; //as a quad will always be the same
	
	//constructor for 4 points of wall and texture
	Plane(glm::vec3 pointA, glm::vec3 pointB, glm::vec3 pointC, glm::vec3 pointD);
	//constructor for just normal (used for collision checking)
	Plane(glm::vec3 aNormal);
	//copy constructor
	Plane(const Plane& copyPlane);
	//default constructor - does nothing
	Plane(); 

	//returns true if point in front
	float pointDisplacement(glm::vec3 aPoint);
	//returns vector with component normal to plane reflected
	glm::vec3 reflect(glm::vec3 aVector);

	//debugging purposes
	void printInfo();

	//get and set methods
	glm::vec3 getCenter();

	glm::vec3 getNormal();
};