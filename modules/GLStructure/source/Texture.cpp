//header file
#include "../includes/Texture.h"

//standard libraries
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

//OpenGL libraries
#include <glad/glad.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"



Texture::Texture(const char* texturePath) {
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    unsigned char* imageData = stbi_load(texturePath, &width, &height, &nrChannels, 0);

    if (imageData) //image loaded correctly
    {
        if (nrChannels == 3) { //image has 3 colour channels, RGB
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
        }
        else if (nrChannels == 4) { //image has 4 colour channels, RGBA (in this case, the 4th is transparency)
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
        }
        //generate the mipmap for the texture
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else //image did not load correctly
    {
        //output error message
        std::cout << "Failed to load texture\nReason: " << std::endl;
        std::cout << stbi_failure_reason();
        std::cout << std::endl;
    }

    //free up image data
    stbi_image_free(imageData);
}

//copy constructor
Texture::Texture(const Texture& copyTexture) {
    ID = copyTexture.ID;
}

//default constructor - empty
//should set ID to a set value, 0, that stores missingTexture texture
Texture::Texture() {

}

//get and set methods

unsigned int Texture::getID() {
    return ID;
}
