#pragma once

//OpenGL libraries
#include <glm/glm.hpp>

class Camera {
private:
	//matrix for camera transformation
	glm::mat4 cameraViewMatrix;
	//position of camera
	glm::vec3 cameraPosition; 
	//vectors for trying to derive view matrix from scratch
	glm::vec3 cameraViewDirection; 
	glm::vec3 cameraVerticalAxis;
	glm::vec3 cameraHorizontalAxis;

public:

	void calculateCameraViewMatrix(glm::vec3 inputPosition, glm::vec3 inputTarget, glm::vec3 upDirection);
	
	//get and set methods
	glm::mat4 getCameraViewMatrix();
	glm::vec3 getCameraPosition();
};

