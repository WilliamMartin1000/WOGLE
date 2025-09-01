#pragma once

//module header files
#include "../../Geometry/includes/Circle.h"
#include "../../Collisions/BSP/includes/BSPT.h"

//OpenGL libraries
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Particle : public Circle {
private:
	//position derivative variables
	glm::vec3 velocity;
	float speed;
	glm::vec3 acceleration;
	
	//friction attributes
	glm::vec3 friction;

	//rotation attributes
	float rotationalVelocity;

	//direction attributes
	float directionAngle;
	glm::vec3 unitDirection;

public:
	Particle(glm::vec3 aCenter, float aRadius, glm::vec3 aColour);

	//method to process user inputs and update attributes
	void processAll(std::vector<int> keysPressed, BSPT* aBSPT, float aTime);

	//updating position
	void updatePosition(float aTime);

	//update position derivative attributes
	void updateVelocity(float aTime);
	void updateSpeed();

	//updates friction
	void updateFriction();

	//updating direction attributes
	void updateUnitDirection();

	//decides what to do given an input
	void processInput(std::vector<int> keysPressed, float aTime);

	//processes any collisions with an environment by checking the BSP tree;
	void processEnvironmentCollisions(BSPT* aBSPT, float aTime);

	//prints all attribute values
	void printInfo();

	//get and set methods
	glm::vec3 getVelocity();
	//void setVelocity(); -no longer required
	glm::vec3 getAcceleration();
	//void setAcceleration();  -no longer required
	float getDirectionAngle();
	glm::vec3 getUnitDirection();
};