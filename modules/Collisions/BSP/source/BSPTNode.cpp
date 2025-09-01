//header file
#include "../includes/BSPTNode.h"

BSPTNode::BSPTNode(Wall aWall) {
	nodeWall = aWall;
}

//get and set methods
Wall BSPTNode::getNodeWall() {
	return nodeWall;
}

BSPTNode* BSPTNode::getBehind() {
	return behind;
}
void BSPTNode::setBehind(BSPTNode* aNode) {
	behind = aNode;
}


BSPTNode* BSPTNode::getInFront() {
	return inFront;
}
void BSPTNode::setInFront(BSPTNode* aNode) {
	inFront = aNode;
}