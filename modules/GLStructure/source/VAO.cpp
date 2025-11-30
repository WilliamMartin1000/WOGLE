//header file
#include "../includes/VAO.h"

//standard libraries
#include <vector>
#include <iostream>
#include <string>

//OpenGL libraries
#include <glad/glad.h>


//string manipulation operations
std::string deleteCharacters(std::string aString, char deleteChar) {
    std::string newString;
    for (int i = 0; aString[i] != NULL; i++) {
        if (aString[i] != deleteChar) {
            newString += aString[i];
        }
    }
    return newString;
}

//only works for location and attribute size values less than 10
VAO::VAO(Shader aShader) {
    glGenVertexArrays(1, &VAOID);
    glGenBuffers(1, &VBOID);
    glGenBuffers(1, &EBOID);


    glBindVertexArray(VAOID);
    glBindBuffer(GL_ARRAY_BUFFER, VBOID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOID);


    std::string vertexCodeRaw = aShader.getVertexText();
    std::vector <std::string> vertexCode;
    //required so vector not out of range
    vertexCode.push_back("");

    int currentIndex = 0;

    for (int i = 0; vertexCodeRaw[i] != NULL; i++) {
        if (vertexCodeRaw[i] == '\n') {
            vertexCode.push_back("");
            //i++;
            currentIndex++;
        }
        else {
            vertexCode[currentIndex] += vertexCodeRaw[i];
        }
    }

    int numberOfFloats = 0;
    std::vector <int> locationOrder;
    std::vector <int> attributeSize;



    for (int i = 0; i < vertexCode.size(); i++) {
        std::string currentLine = vertexCode[i];
        currentLine = deleteCharacters(currentLine, ' ');
        
        //make sure not a comment
        if (currentLine.size() > 2) {
            if (currentLine.substr(0, 2) == "//") {
                continue;
            }
        }
        
        //check if it is a layout variable
        if (currentLine.find("layout") != std::string::npos) {
            //find the current location
            int currentLocationIndex = currentLine.find("location") + 9;
            std::string currentLocationString = currentLine.substr(currentLocationIndex, 1);
            int currentLocationValue = std::stoi(currentLocationString);
            locationOrder.push_back(currentLocationValue);
            
            //find the vector size
            int currentAttributeSizeIndex = currentLine.find("vec") + 3;
            std::string currentAttributeSizeString = currentLine.substr(currentAttributeSizeIndex, 1);
            int currentAttributeSizeValue = std::stoi(currentAttributeSizeString);
            attributeSize.push_back(currentAttributeSizeValue);
            numberOfFloats += currentAttributeSizeValue;
        }
    }

    //locationOrder or attributeSize
    int index = 0;
    int currentJump = 0;
    while (currentJump < numberOfFloats) {
        //debugging purposes
         /*std::cout << locationOrder[index];
         std::cout << attributeSize[index];
         std::cout << numberOfFloats;
         std::cout << currentJump;
         std::cout << "\n";*/
        glVertexAttribPointer(locationOrder[index], attributeSize[index], GL_FLOAT, GL_FALSE, numberOfFloats * sizeof(float), (void*)(currentJump * sizeof(float)));
        glEnableVertexAttribArray(locationOrder[index]);
        currentJump += attributeSize[index];
        index++;
    }
}

VAO::VAO() {

}

VAO::VAO(const VAO& copyVAO) {
    VAOID = copyVAO.VAOID;
    VBOID = copyVAO.VBOID;
    EBOID = copyVAO.EBOID;
}

void VAO::bind() {
    glBindVertexArray(VAOID);
}