#pragma once

//standard libraries
#include <vector>

//OpenGL libraries
#include <glm/glm.hpp>

//module header files
#include "../../../CONSTANTS.h"

const int numberOuterVertices = 20; //used to determine no. vertexes of circle
const int circleStride = 8; //number of values storing attribute data for each vertex

class Circle {
protected:
	///stride for VBO
	const int stride = circleStride; //number of values storing attribute data for each vertex 
	//mathematical attributes
	float radius;
	glm::vec3 center;
	//vector of points of circle
	std::vector <glm::vec3> vertices;

	//initialise texture coordinates
	void assignTextureCoordinates();
	//intialise index array 
	void assignIndexArray();
	//update vertex coordinates
	void assignVertexArrayCoordinates();

	//initialise vertices
	void assignVertices();

public:
	//array storing vertex data
	float vertexArray[circleStride * (1 + numberOuterVertices)];
	//array storing index data
	int indexArray[3 * (numberOuterVertices)];

	Circle(glm::vec3 aCenter, float aRadius, glm::vec3 aColour);

	//update colour attributes in vertexArray
	void assignColours(glm::vec3 aColour);
	
	//debugging purposes
	void printVertexArray();
	void printIndexArray();
	void printVertices();

	//get and set methods
	glm::vec3 getCenter();
	void setCentre(glm::vec3 aCenter);
	float getRadius();
	void setRadius(float aRadius);
};