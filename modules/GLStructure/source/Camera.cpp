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
	cameraViewMatrix = glm::lookAt(inputPosition, inputTarget, upDirection);
	
	//original plan to carry out glm::lookat operations myself
	
	/*cameraPosition = inputPosition;
	glm::vec3 cameraTarget = inputTarget;
	cameraViewMatrix = glm::mat4(1.0f);*/

	//because we want to move backwards, we do vector from target to position, as opposed to camera to target
	/*cameraViewDirection = cameraPosition - cameraTarget; 
	float xChange = cameraPosition.x - cameraTarget.x;
	float yChange = cameraPosition.y - cameraTarget.y;
	float zChange = cameraPosition.z - cameraTarget.z;
	float hypotenuse = sqrt(xChange * xChange + yChange * yChange + zChange * zChange);*/

	//calculating angles
	/*float xTheta, yTheta, zTheta;
	xTheta = asin(xChange / hypotenuse);
	yTheta = asin(yChange / hypotenuse);
	zTheta = asin(zChange / hypotenuse);*/

	/*cameraViewDirection = glm::normalize(cameraViewDirection);
	cameraVerticalAxis = glm::normalize(glm::cross(cameraViewDirection, glm::vec3(0.0f, 1.0f, 0.0f)));
	cameraHorizontalAxis = glm::normalize(glm::cross(cameraViewDirection, cameraVerticalAxis));*/

	//apply correct rotations to the matrix
	/*cameraViewMatrix = glm::translate(cameraViewMatrix, -cameraPosition);
	//cameraViewMatrix = glm::rotate(cameraViewMatrix, 2 * pi - zTheta, glm::vec3(0.0f, 0.0f, 1.0f));
	cameraViewMatrix = glm::rotate(cameraViewMatrix, 2 * pi - xTheta, glm::vec3(0.0f, 1.0f, 0.0f));
	cameraViewMatrix = glm::rotate(cameraViewMatrix, 2 * pi - yTheta, glm::vec3(1.0f, 0.0f, 0.0f));*/

	//try to assign lookat values manually to matrix - pointless
	/*glm::mat4 axisMatrix = glm::mat4(1.0f);
	axisMatrix[0][0] = cameraHorizontalAxis.x;
	axisMatrix[1][0] = cameraHorizontalAxis.y;
	axisMatrix[2][0] = cameraHorizontalAxis.z;
	axisMatrix[0][1] = cameraVerticalAxis.x;
	axisMatrix[1][1] = cameraVerticalAxis.y;
	axisMatrix[2][1] = cameraVerticalAxis.z;
	axisMatrix[0][2] = cameraViewDirection.x;
	axisMatrix[1][2] = cameraViewDirection.y;
	axisMatrix[2][2] = cameraViewDirection.z;*/

	/*cameraViewMatrix = glm::mat4(1.0f);
	cameraViewMatrix = glm::translate(cameraViewMatrix, -cameraPosition);
	cameraViewMatrix = axisMatrix * cameraViewMatrix;*/

	//debugging purposes
	/*
	std::cout << "\nxTheta: ";
	std::cout << xTheta;
	std::cout << "\nyTheta: ";
	std::cout << yTheta;
	std::cout << "\nzTheta: ";
	std::cout << zTheta;
	std::cout << "\ncameraViewMatrix:";
	for (int i = 0; i < 4; i++) {
		std::cout << "\n";
		for (int y = 0; y < 4; y++) {
			std::cout << cameraViewMatrix[y][i];
			std::cout << " ";
		}
	}
	*/
}

//get and set methods

glm::mat4 Camera::getCameraViewMatrix() {
	return cameraViewMatrix;
}