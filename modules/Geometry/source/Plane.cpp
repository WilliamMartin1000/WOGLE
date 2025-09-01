//header file
#include "../includes/Plane.h"

//standard libraries
#include <iostream>

Plane::Plane(glm::vec3 pointA, glm::vec3 pointB, glm::vec3 pointC, glm::vec3 pointD) {
	//initialises the center of the plane
	float meanX, meanY, meanZ;
	meanX = (pointA.x + pointB.x + pointC.x + pointD.x) / 4;
	meanY = (pointA.y + pointB.y + pointC.y + pointD.y) / 4;
	meanZ = (pointA.z + pointB.z + pointC.z + pointD.z) / 4;
	center = glm::vec3(meanX, meanY, meanZ);

	//calculate the normal
	glm::vec3 AtoB = pointB - pointA;
	glm::vec3 AtoC = pointC - pointA;

	normal = glm::cross(AtoB, AtoC);

	//calculate the dot product of the normal and a point on the plane
	doProValue = glm::dot(normal, pointA);
	
	//calculates checking value to ensure all points on plane
	float checkDoProValue = glm::dot(normal, pointD);
	float difference = doProValue - checkDoProValue;

	//assigns difference its absolute value
	if (difference < 0) {
		difference *= -1;
	}

	if (difference < 0.001) { //all points on the plane
		vertices[0] = pointA;
		vertices[1] = pointB;
		vertices[2] = pointC;
		vertices[3] = pointD;
	}
	else { //point D not on Plane ABC
		std::cout << "initialization error: point D not on plane ABC";
	}

	//initialises vertex array
	setVertexArrayVertices();
	setVertexArrayColours(glm::vec3(1.0f, 1.0f, 1.0f));
	setVertexArrayTextures();

	//printInfo(); //used for testing
} 

//used for plane checking algorithms
Plane::Plane(glm::vec3 aNormal) { 
	normal = aNormal;
}

//copy constructor
Plane::Plane(const Plane& copyPlane) {
	normal = copyPlane.normal;
	doProValue = copyPlane.doProValue;
	center = copyPlane.center;
	for (int i = 0; i < sizeof(vertices) / sizeof(glm::vec3);i++) {
		vertices[i] = copyPlane.vertices[i];
	}
	for (int i = 0; i < sizeof(vertexArray) / sizeof(float);i++) {
		vertexArray[i] = copyPlane.vertexArray[i];
	}
	for (int i = 0; i < sizeof(indexArray) / sizeof(int);i++) {
		indexArray[i] = copyPlane.indexArray[i];
	}

}

//default constructor - empty
Plane::Plane() {

};

//initialises vertex values in vertex array
void Plane::setVertexArrayVertices() {
	//relative points for the plane, to be stored in the vertex array
	glm::vec3 relativeVertexArray[numberOfVertices]; 
	for (int i = 0; i < sizeof(relativeVertexArray) / sizeof(glm::vec3); i++) {
		relativeVertexArray[i] = vertices[i] - center;
	}

	for (int i = 0; i < sizeof(relativeVertexArray) / sizeof(glm::vec3); i++) {
		int relativeIndex = i * 8;
		vertexArray[relativeIndex] = relativeVertexArray[i].x;
		vertexArray[relativeIndex + 1] = relativeVertexArray[i].y;
		vertexArray[relativeIndex + 2] = relativeVertexArray[i].z;
	}
}

//initialises colour values in vertex array
void Plane::setVertexArrayColours(glm::vec3 aColour) {
	for (int i = 0; i < sizeof(vertices) / sizeof(glm::vec3); i++) {
		int relativeIndex = (i * 8) + 3;
		vertexArray[relativeIndex] = aColour.x;
		vertexArray[relativeIndex + 1] = aColour.y;
		vertexArray[relativeIndex + 2] = aColour.z;
	}
}

//initialises texture coordinates in vertex array
void Plane::setVertexArrayTextures() {
	vertexArray[6] = 0.0f;
	vertexArray[7] = 0.0f;
	vertexArray[14] = 0.0f;
	vertexArray[15] = 1.0f;
	vertexArray[22] = 1.0f;
	vertexArray[23] = 0.0f;
	vertexArray[30] = 1.0f;
	vertexArray[31] = 1.0f;
}

//returns displacement of a point from a plane
float Plane::pointDisplacement(glm::vec3 aPoint) {
	//use equation for distance from plane to calculate displacement
	float newDistance = glm::dot(normal, aPoint);

	float displacement = (newDistance - doProValue) / glm::length(normal);
	
	return displacement;
};

//use vector mathematics to reflect the normal component of a vector in the plane
glm::vec3 Plane::reflect(glm::vec3 aVector) {

	float normalMagnitude = sqrt(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z);

	glm::vec3 unitNormal = (1 / normalMagnitude) * normal;

	/* 
	broken down steps
	* float cosTheta = glm::dot(normal, aVector) / (inputMagnitude * normalMagnitude);
	float reflectedDistance = cosTheta * inputMagnitude;
	*/

	float reflectedDistance = glm::dot(normal, aVector) / normalMagnitude;

	if (reflectedDistance < 0) {
		reflectedDistance = -reflectedDistance;
	}

	/*
	broken down steps
	glm::vec3 reservedComponent = aVector + reflectedDistance * normal;
	reflectedVector = reservedComponent + reflectedDistance * normal;
	*/

	glm::vec3 reflectedVector = aVector + 2 * reflectedDistance * unitNormal;

	return reflectedVector;
}

void Plane::printInfo() {
	std::cout << "Center: ";
	std::cout << center.x;
	std::cout << " ";
	std::cout << center.y;
	std::cout << " ";
	std::cout << center.z;
	std::cout << "\n";
	std::cout << "Normal: ";
	std::cout << normal.x;
	std::cout << " ";
	std::cout << normal.y;
	std::cout << " ";
	std::cout << normal.z;
	std::cout << "\n";
	std::cout << "vertex Array:\n";
	for (int i = 0; i < 4; i++) {
		std::cout << "position: ";
		for (int j = 0; j < 3; j++) {
			int relativeIndex = j + (8 * i);
			std::cout << vertexArray[relativeIndex];
			std::cout << " ";
		}
		std::cout << "colour: ";
		for (int j = 3; j < 6; j++) {
			int relativeIndex = j + (8 * i);
			std::cout << vertexArray[relativeIndex];
			std::cout << " ";
		}
		std::cout << "texture: ";
		for (int j = 6; j < 8; j++) {
			int relativeIndex = j + (8 * i);
			std::cout << vertexArray[relativeIndex];
			std::cout << " ";
		}
		std::cout << "\n";
	}
	std::cout << "\nvertices:";
	for (int i = 0; i < sizeof(vertices) / sizeof(glm::vec3); i++) {
		std::cout << "\nvertex ";
		std::cout << i;
		std::cout << ": ";
		std::cout << vertices[i].x;
		std::cout << " ";
		std::cout << vertices[i].y;
		std::cout << " ";
		std::cout << vertices[i].z;
		std::cout << "\n";
	}
}

//get and set methods
glm::vec3 Plane::getCenter() {
	return center;
}

glm::vec3 Plane::getNormal() {
	return normal;
}