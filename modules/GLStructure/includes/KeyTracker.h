#pragma once
//helpful sources
// exact syntax https://www.glfw.org/docs/latest/input.html#input_keyboard
// understanding how callback worked and implementation method https://stackoverflow.com/questions/46631814/handling-multiple-keys-input-at-once-with-glfw

//standard libraries
#include <vector>

//the number of key signatures GLFW has
const int numberOfKeys = 349;

class KeyTracker {
private:
	//array storing the status of each key (true = pressed, false = not pressed)
	bool keyStatus[numberOfKeys];
public:
	//default constructor
	KeyTracker();
	//updates keyStatus with new pressed keys
	void updateStatus(int key, int action);
	//returns a vector with all currently pressed keys
	std::vector <int> pressedKeys();
};