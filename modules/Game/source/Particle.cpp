//header file
#include "../includes/Particle.h"

//standard libraries
#include <cmath>
#include <iostream>
#include <vector>

//OpenGL libraries
#include <glm/glm.hpp>

//Particle constructor - passes all parameters to Circle Constructor and assigns default values
Particle::Particle(glm::vec3 aCenter, float aRadius, glm::vec3 aColour) : Circle(aCenter, aRadius, aColour) {
	velocity = glm::vec3(0.0f);
	acceleration = glm::vec3(0.0f);
	friction = glm::vec3(0.0f);
	rotationalVelocity = pi;

	directionAngle = 0.0f;
	updateUnitDirection();
}

//method to process user inputs and update attributes
void Particle::processAll(std::vector<int> keysPressed, BSPT* aBSPT, float aTime) {
	processInput(keysPressed, aTime);
	acceleration.z = -1.0f;

	updateFriction();

	updateVelocity(aTime);

	processEnvironmentCollisions(aBSPT, aTime);
}


void Particle::updatePosition(float aTime) {
	
	//calculate a velocity with the z component ignored below a certain value, to deal with constant gravitational acceleration
	float velocityZ = velocity.z;
	if (abs(velocityZ) < 0.2) {
		velocityZ = 0;
	}
	glm::vec3 cutOffVelocity = glm::vec3(velocity.x, velocity.y, velocityZ);

	center += aTime * cutOffVelocity;
	assignVertices();
}

void Particle::updateVelocity(float aTime) {
	velocity += aTime * (acceleration + friction);
}

void Particle::updateSpeed() {
	float vX = velocity.x, vY = velocity.y, vZ = velocity.z;
	speed = sqrt(vX * vX + vY * vY + vZ * vZ);
}

//updates friction
void Particle::updateFriction() {
	updateSpeed();
	if (speed != 0) {
		glm::vec3 velocityDirection = velocity / speed;
		float frictionalValue = 0.5 * speed; //frictional magnitude will be 1/4 of velocity magnitude
		friction = -frictionalValue * velocityDirection;
	}
	else {
		friction = glm::vec3(0.0f);
	}

}

//use trig to calculate the direction vector for the Unit
void Particle::updateUnitDirection() {
	unitDirection.x = cos(directionAngle);
	unitDirection.y = sin(directionAngle);
	unitDirection.z = 0.0f;
}

void Particle::processInput(std::vector<int> keysPressed, float aTime) {
	//flag to store whether a valid key has been pressed
	bool pressFlag = false;
	if ( std::count(keysPressed.begin(), keysPressed.end(), GLFW_KEY_UP) > 0) {
		acceleration = 1.0f * unitDirection;
		pressFlag = true;
	}
	if (std::count(keysPressed.begin(), keysPressed.end(), GLFW_KEY_DOWN) > 0) {
		acceleration = 1.0f * -unitDirection;
		pressFlag = true;
	}
	if (std::count(keysPressed.begin(), keysPressed.end(), GLFW_KEY_LEFT) > 0) {
		directionAngle += rotationalVelocity * aTime;
		updateUnitDirection();
		pressFlag = true;
	}
	if (std::count(keysPressed.begin(), keysPressed.end(), GLFW_KEY_RIGHT) > 0) {
		directionAngle -= rotationalVelocity * aTime;
		updateUnitDirection();
		pressFlag = true;
	}
	if (std::count(keysPressed.begin(), keysPressed.end(), GLFW_KEY_SPACE) > 0) {
		velocity.z = 2.0f;
		pressFlag = true;
	}
	if (std::count(keysPressed.begin(), keysPressed.end(), GLFW_KEY_R) > 0) {
		center = glm::vec3(0.0f, 0.0f, 0.5f);
		velocity = glm::vec3(0.0f);
		acceleration = glm::vec3(0.0f);
		friction = glm::vec3(0.0f);
		directionAngle = 0.0f;
		updateUnitDirection();
	}
	if (pressFlag == false) {
		acceleration = glm::vec3(0.0f);
	}
}

void Particle::processEnvironmentCollisions(BSPT* aBSPT, float aTime) {
	//previous center to return to if collision happens
	glm::vec3 previousCenter = center;
	//update position to where particle would be without walls
	updatePosition(aTime);

	Wall checkWall = aBSPT->navigatePoints(vertices);
	if (checkWall.getNormal() != glm::vec3(0.0f)) { //collided with wall
		//return center to previous position
		center = previousCenter;
		//update velocity with reflected value
		velocity = checkWall.reflect(velocity);
		//dampen velocity with wall bounciness value
		velocity *= checkWall.getBounciness();
	}
}


void Particle::printInfo() {
	std::cout << "\ncenter: ";
	std::cout << center.x;
	std::cout << ", ";
	std::cout << center.y;
	std::cout << ", ";
	std::cout << center.z;
	std::cout << "\nvelocity: ";
	std::cout << velocity.x;
	std::cout << ", ";
	std::cout << velocity.y;
	std::cout << ", ";
	std::cout << velocity.z;
	std::cout << "\nspeed: ";
	std::cout << speed;
	std::cout << "\nacceleration: ";
	std::cout << acceleration.x;
	std::cout << ", ";
	std::cout << acceleration.y;
	std::cout << ", ";
	std::cout << acceleration.z;
	std::cout << "\nfriction: ";
	std::cout << friction.x;
	std::cout << ", ";
	std::cout << friction.y;
	std::cout << ", ";
	std::cout << friction.z;
	std::cout << "\ndirectionAngle: ";
	std::cout << directionAngle;
	std::cout << "\nunitDirection: ";
	std::cout << unitDirection.x;
	std::cout << ", ";
	std::cout << unitDirection.y;
	std::cout << ", ";
	std::cout << unitDirection.z;
	std::cout << "\n";
}

//get and set methods

glm::vec3 Particle::getVelocity() {
	return velocity;
}
glm::vec3 Particle::getAcceleration() {
	return acceleration;
}
float Particle::getDirectionAngle() {
	return directionAngle;
}
glm::vec3 Particle::getUnitDirection() {
	return unitDirection;
}


//legacy updatePosition method, used for asteroids based game
/*void Particle::updatePosition(float aTime) {
	float newX, newY, newZ;
	newX = (center.x + (velocity.x * aTime));
	while (newX > (1.0f + radius)) {
		newX -= (2 + 2 * radius);
	}
	while (newX < -(1.0f + radius)) {
		newX += (2 + 2 * radius);
	}

	newY = (center.y + (velocity.y * aTime));
	while (newY > (1.0f + radius)) {
		newY -= (2 + 2 * radius);
	}
	while (newY < -(1.0f + radius)) {
		newY += (2 + 2 * radius);
	}

	newZ = (center.z + (velocity.z * aTime));
	while (newZ > (1.0f + radius)) {
		newZ -= (2 + 2 * radius);
	}
	while (newZ < (-1.0f + radius)) {
		newZ += (2 + 2 * radius);
	}

	center = glm::vec3(newX, newY, newZ);
}*/