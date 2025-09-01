#include "../includes/Wall.h"

Wall::Wall(glm::vec3 pointA, glm::vec3 pointB, glm::vec3 pointC, glm::vec3 pointD, glm::vec3 aBounciness, Texture aWallTexture) : Plane(pointA, pointB, pointC, pointD) { //passes all points to Plane constructor
	//assigns resulting input parameters
	bounciness = aBounciness;
	wallTexture = aWallTexture;
}

Wall::Wall(glm::vec3 aNormal) : Plane(aNormal) {
	//runs constructor for Plane(glm::vec3 aNormal)
};

Wall::Wall(const Wall& copyWall) {
	normal = copyWall.normal;
	doProValue = copyWall.doProValue;
	center = copyWall.center;
	for (int i = 0; i < sizeof(vertices) / sizeof(glm::vec3);i++) {
		vertices[i] = copyWall.vertices[i];
	}
	for (int i = 0; i < sizeof(vertexArray) / sizeof(float);i++) {
		vertexArray[i] = copyWall.vertexArray[i];
	}
	for (int i = 0; i < sizeof(indexArray) / sizeof(int);i++) {
		indexArray[i] = copyWall.indexArray[i];
	}
	bounciness = copyWall.bounciness;
	wallTexture = copyWall.wallTexture;
}

Wall::Wall() {
	//does nothing
}

//get and set methods

glm::vec3 Wall::getBounciness() {
	return bounciness;
}

Texture Wall::getWallTexture() {
	return wallTexture;
}