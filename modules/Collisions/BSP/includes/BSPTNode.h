#pragma once

//module header files
#include "../../../Game/includes/Wall.h"

class BSPTNode {

private:
	//Wall used for plane in BPST
	Wall nodeWall;

	//Pointers for branches of the tree
	BSPTNode* behind = NULL;
	BSPTNode* inFront = NULL;

public:
	BSPTNode(Wall aWall);

	//get and set methods
	Wall getNodeWall();

	BSPTNode* getBehind();
	void setBehind(BSPTNode* aNode);

	BSPTNode* getInFront();
	void setInFront(BSPTNode* aNode);
};
