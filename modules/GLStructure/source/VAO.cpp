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
std::string subString(std::string aString, int startIndex, int endIndex) {
    if (aString[startIndex] == NULL) {
        std::cout << "\nstartIndex out of bounds\n";
        return 0;
    }
    else if (aString[endIndex] == NULL) {
        std::cout << "\nendIndex out of bounds\n";
        return 0;
    }
    else {
        std::string returnString;
        for (int i = startIndex; i <= endIndex; i++) {
            returnString += aString[i];
        }
        return returnString;
    }
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

        for (int j = 0; currentLine[j] != NULL; j++) {
            //This part fails for strings that = "{" or "}", adding comments resolves this -need to fix
            if (currentLine[j + 5] != NULL) {
                std::string potentialWord = subString(currentLine, j, j + 5);

                if (potentialWord == "layout") {
                    //now string confirmed to be a vertex attribute
                    //find location of vector size
                    for (int k = 0; currentLine[k] != NULL; k++) {
                        if (currentLine[k] == '=') {
                            //only works for locations from 0  to 9.
                            std::string currentLocationString;
                            currentLocationString += currentLine[k + 1];
                            locationOrder.push_back(stoi(currentLocationString));
                            break;
                        }
                    }
                    for (int k = 0; currentLine[k] != NULL; k++) {
                        if (currentLine[k] == 'v') {
                            //only works for sizes from 0  to 9.
                            std::string currentAttributeSizeString;
                            currentAttributeSizeString += currentLine[k + 3];
                            int currentAttributeSizeInt = stoi(currentAttributeSizeString);
                            attributeSize.push_back(currentAttributeSizeInt);
                            numberOfFloats += currentAttributeSizeInt;
                            //break;
                        }
                    }

                }
                else {
                    //nothing
                }
            }
            else {
                //std::cout << "\nfail j + 5 check\n";
                break;
            }
        }
    }

    //locationOrder or attributeSize
    int index = 0;
    int currentJump = 0;
    while (currentJump < numberOfFloats) {
        //debugging purposes
        /* std::cout << locationOrder[index];
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