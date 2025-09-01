#pragma once

class Texture {
private:
	//Texture ID
	unsigned int ID;

public:
	//constructors
	Texture(const char* texturePath);
	Texture(const Texture& copyTexture);
	Texture();

	//get and set methods

	unsigned int getID();

};