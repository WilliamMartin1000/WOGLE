#include "../includes/Camera.h"

//standard libraries
#include <cmath>
#include <iostream>

//OpenGL libraries
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//header file containing constants
//#include "../../../CONSTANTS.h"

void Camera::calculateCameraViewMatrix(glm::vec3 inputPosition, glm::vec3 inputTarget, glm::vec3 upDirection) {
	cameraPosition = inputPosition;
	cameraViewMatrix = glm::lookAt(cameraPosition, inputTarget, upDirection);
}

//get and set methods

glm::mat4 Camera::getCameraViewMatrix() {
	return cameraViewMatrix;
}

glm::vec3 Camera::getCameraPosition() {
	return cameraPosition;
}