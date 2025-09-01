//header files
#include "../includes/KeyTracker.h"

//openGL specific libraries
#include <glad/glad.h>
#include <GLFW/glfw3.h>

KeyTracker::KeyTracker() {
	//initialise all keys to false
	for (int i = 0; i < sizeof(keyStatus) / sizeof(bool); i++) {
		keyStatus[i] = false;
	}
}

void KeyTracker::updateStatus(int key, int action) {
	if (key != GLFW_KEY_UNKNOWN) {
		if (action == GLFW_PRESS) {
			keyStatus[key] = true;
		}
		else if (action == GLFW_RELEASE) {
			keyStatus[key] = false;
		}
	}
}

std::vector<int> KeyTracker::pressedKeys() {
	//vector to store all pressed keys
	std::vector<int> returnVector;

	//iterate through all keys, and if pressed, add to vector
	for (int i = 0; i < sizeof(keyStatus) / sizeof(bool); i++) {
		if (keyStatus[i] == true) {
			returnVector.push_back(i);
		}
	}
	return returnVector;
}