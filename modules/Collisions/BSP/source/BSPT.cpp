//header file
#include "../includes/BSPT.h"

//standard libraries
#include <iostream>

//constructor - creates a BSPT out of a vector of walls
BSPT::BSPT(std::vector<Wall> vectorWalls) {
	if (vectorWalls.size() == 0) { //vector is empty
		std::cout << "empty vector";
		root = NULL;
	}
	else {
		//create root node that is first item in vector
		BSPTNode* rootNode = new BSPTNode(vectorWalls[0]);
		root = rootNode;

		for (int i = 1; i < vectorWalls.size(); i++) {
			//formats node to add
			BSPTNode* addNode = new BSPTNode(vectorWalls[i]);
			Plane addPlane = addNode->getNodeWall();
			glm::vec3 addVertices[4];
			for (int i = 0; i < sizeof(addPlane.vertices) / sizeof(glm::vec3); i++) {
				addVertices[i] = addPlane.vertices[i];
			}

			//while loop to ensure node appended correctly
			bool endCheck = false;
			//current node being observed, starts as root node
			BSPTNode* currentNode = root;

			while (endCheck == false) {

				Wall currentWall = currentNode->getNodeWall();

				//checks if plane inFront or behind;
				bool inFrontCheck = false, behindCheck = false;

				for (int i = 0; i < sizeof(currentNode->getNodeWall().vertices) / sizeof(glm::vec3); i++) {
					if (currentWall.pointDisplacement(addVertices[i]) > 0) {
						inFrontCheck = true;
					}
					else if (currentWall.pointDisplacement(addVertices[i]) <= 0) {
						behindCheck = false;
					}
				}

				//decides what path of tree to take depending on whether plane is in front or behind
				if (inFrontCheck == true) {//node in front of wall
					if (currentNode->getInFront() != NULL) { //currentNode not last node in branch
						//update currentNode
						currentNode = currentNode->getInFront();
					}
					else if (currentNode->getInFront() == NULL) { //currentNode last node in branch
						//append addNode
						currentNode->setInFront(addNode);
						endCheck = true;
					}
				}
				else if (behindCheck == true) {//node behind wall
					if (currentNode->getBehind() != NULL) { //currentNode not last node in branch
						//update currentNode
						currentNode = currentNode->getBehind();
					}
					else if (currentNode->getBehind() == NULL) { //currentNode last node in branch
						//append addNode
						currentNode->setBehind(addNode);
						endCheck = true;
					}
				}
			}
		}
	}
}

//returns whether a point is in a valid position
bool BSPT::navigatePoint(glm::vec3 aPoint) {
	if (root == NULL) { //no objects in tree, can't collide
		return true; 
	}
	else {
		BSPTNode* currentNode = root;
		while (true) {
			//currentWall point being checked against
			Plane currentWall = currentNode->getNodeWall();
			
			if (currentWall.pointDisplacement(aPoint) > 0) { //in front
				if (currentNode->getInFront() == NULL) { //last node in branch
					return true;
				}
				else { //not last node in branch
					//update currentNode to next wall to check against
					currentNode = currentNode->getInFront();
				}
			}
			else { //in / behind
				if (currentNode->getBehind() == NULL) { //last node in branch
					return false;
				}
				else { //not last node in branch
					//update currentNode to next wall to check against
					currentNode = currentNode->getBehind();
				}
			}
		}
	}
}

//returns whether a series of points are all in valid position, and if not, what plane they have collided with
Wall BSPT::navigatePoints(const std::vector<glm::vec3> aPointVector) {
	if (root == NULL) {
		//std::cout << "\no collision: no walls\n"; // for testing
		return Wall(glm::vec3(0.0f)); //true, no objects in tree, can't collide
	}
	else {
		for (int i = 0; i < aPointVector.size(); i++) { 
			glm::vec3 currentPoint = aPointVector[i];
			BSPTNode* currentNode = root;

			while (true) { //loop will keep going to the end
				Wall currentWall = currentNode->getNodeWall();
				bool pointInFront;

				//check whether current point is in front or behind current wall
				float currentDisplacement = currentWall.pointDisplacement(currentPoint);
				if (currentDisplacement > 0) { //in front
					pointInFront = true;
				}
				else { //in / behind
					pointInFront = false;
				}

				if (pointInFront == false) {
					if (currentNode->getBehind() == NULL) {  
						//std::cout << "\ncollision: behind a wall\n"; //for testing
						return currentWall; //false
					}
					else {
						currentNode = currentNode->getBehind();
					}
				}
				else {
					if (currentNode->getInFront() == NULL) {
						//std::cout << "\nno collision: in front of a wall\n";
						break;
					}
					else {
						currentNode = currentNode->getInFront();
					}
				}
			}

		}
		//if it has gone through all points and not one is in an invalid position, points in a valid position
		return Wall(glm::vec3(0.0f)); 		
	}
}

//original code for navigatePoints while statement - doesn't work
/*while (true) { //loop will keep going to the end
	Wall currentWall = currentNode->getNodeWall();
	bool pointInFront = false, pointBehind = false;
	for (int i = 0; i < aPointVector.size(); i++) {
		glm::vec3 currentPoint = aPointVector[i];
		float currentDisplacement = currentWall.pointDisplacement(currentPoint);
		if (currentDisplacement > 0) { //in front
			pointInFront = true;
		}
		else { //in / behind
			pointBehind = true;
		}
	}
	//doesn't work
		if (pointInFront == true && pointBehind == true) {
			//std::cout << "\ncollision: some points in front and some points behind\n";
			return currentWall; //false
		}
		else {
	if (pointBehind == true) {
		if (currentNode->getBehind() == NULL) {
			//std::cout << "\ncollision: behind a wall\n";						
			return currentWall; //false
		}
		else {
			currentNode = currentNode->getBehind();
		}	
	}
	else {
		if (currentNode->getInFront() == NULL) {
			//std::cout << "\nno collision: in front of a wall\n";
			return Wall(glm::vec3(0.0f)); //true
		}
		else {
			currentNode = currentNode->getInFront();
		}
	}
}*/