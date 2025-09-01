//header file
#include "../includes/Circle.h"

//standard libraries
#include <cmath>
#include <iostream>

Circle::Circle(glm::vec3 aCenter, float aRadius, glm::vec3 aColour) {
	center = aCenter;
	radius = aRadius;
	assignVertexArrayCoordinates();
	assignColours(aColour);
	assignIndexArray();
	assignTextureCoordinates();
	assignVertices();
}

void Circle::assignVertices() {
	vertices.clear();
	for (int i = 0; i < numberOuterVertices; i++) {
		int index = (i + 1) * stride; //+ 1 as first vertex is the center

		float globalX, globalY, globalZ;
		globalX = vertexArray[index] + center.x;
		globalY = vertexArray[index + 1] + center.y;
		globalZ = vertexArray[index + 2] + center.z;

		glm::vec3 currentVertex = glm::vec3(globalX, globalY, globalZ);
		vertices.push_back(currentVertex);
	}
}

void Circle::assignVertexArrayCoordinates() {
	vertexArray[0] = 0.0f, vertexArray[1] = 0.0f, vertexArray[2] = 0.0f;

	for (int i = 0; i < numberOuterVertices; i++) {
		float theta = i * pi / (numberOuterVertices / 2);
		int index = (i + 1) * stride;

		vertexArray[index] = cos(theta) * radius;
		vertexArray[index + 1] = sin(theta) * radius;
		vertexArray[index + 2] = 0.0f; //no depth
	}

}

void Circle::assignColours(glm::vec3 aColour) {
	vertexArray[3] = aColour.x;
	vertexArray[4] = aColour.y;
	vertexArray[5] = aColour.z;

	for (int i = 0; i < numberOuterVertices; i++) {
		int index = (i + 1) * stride;

		vertexArray[index + 3] = aColour.x; //the offput for colour isn't in index, hence + 3, not 0
		vertexArray[index + 4] = aColour.y;
		vertexArray[index + 5] = aColour.z;
	}
}

void Circle::assignTextureCoordinates() {
	vertexArray[6] = 0.5;
	vertexArray[7] = 0.5;
	for (int i = 0; i < numberOuterVertices; i++) {
		float theta = i * pi / (numberOuterVertices / 2);
		int index = (i + 1) * stride;

		vertexArray[index + 6] = 0.5 * (1 + cos(theta));
		vertexArray[index + 7] = 0.5 * (1 + sin(theta));
	}
}

void Circle::assignIndexArray() {
	for (int i = 0; i < numberOuterVertices - 1; i++) {
		int jumpIndex = 3 * (i); //starts at 1, as can ignore 
		indexArray[jumpIndex] = 0;
		indexArray[jumpIndex + 1] = i + 1;
		indexArray[jumpIndex + 2] = i + 2;
	}

	int length = sizeof(indexArray) / sizeof(float); //why a float, not int?
	indexArray[length - 3] = 0;
	indexArray[length - 2] = numberOuterVertices;
	indexArray[length - 1] = 1;
}

//debugging purposes

void Circle::printVertexArray() {
	for (int i = 0; i < sizeof(vertexArray) / (circleStride * sizeof(float)); i++) {
		int index = circleStride * i;
		std::cout << "vertex: ";
		std::cout << i;
		std::cout << " coordinates: ";
		std::cout << vertexArray[index];
		std::cout << ", ";
		std::cout << vertexArray[index + 1];
		std::cout << ", ";
		std::cout << vertexArray[index + 2];
		std::cout << " colour: ";
		std::cout << vertexArray[index + 3];
		std::cout << ", ";
		std::cout << vertexArray[index + 4];
		std::cout << ", ";
		std::cout << vertexArray[index + 5];
		std::cout << " texture coordinates:";
		std::cout << vertexArray[index + 6];
		std::cout << ", ";
		std::cout << vertexArray[index + 7];
		std::cout << "\n";
	}
}

void Circle::printIndexArray() {
	for (int i = 0; i < sizeof(indexArray) / (3 * sizeof(float)); i++) {
		int index = 3 * i;
		std::cout << "triangle: ";
		std::cout << i;
		std::cout << " points: ";
		std::cout << indexArray[index];
		std::cout << " ";
		std::cout << indexArray[index + 1];
		std::cout << " ";
		std::cout << indexArray[index + 2];
		std::cout << "\n";
	}
}

void Circle::printVertices() {
	std::cout << "size: ";
	std::cout << vertices.size();
	std::cout << "\n";
	for (int i = 0; i < vertices.size(); i++) {
		std::cout << "vertex ";
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

glm::vec3 Circle::getCenter() {
	return center;
}

void Circle::setCentre(glm::vec3 aCentre) {
	center = aCentre;
}

float Circle::getRadius() {
	return radius;
}

void Circle::setRadius(float aRadius) {
	radius = aRadius;
	assignVertexArrayCoordinates();
}