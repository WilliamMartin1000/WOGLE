#pragma once

//module header files
#include "Shader.h"

class VAO {
private:
    //ID attributes
    unsigned int VAOID;
    unsigned int VBOID;
    unsigned int EBOID;

public:
    VAO(Shader aShader); //requires comments in shader files not to break
    VAO(); //default
    VAO(const VAO& copyVAO); //copy constructor

    void bind();
};

//Original code
//vertex buffer object, stores vertex data in GPU for faster processing
/*unsigned int VBOID;
glGenBuffers(1, &VBOID);
unsigned int VAOID;
glGenVertexArrays(1, &VAOID);
unsigned int EBOID;
glGenBuffers(1, &EBOID);
glBindVertexArray(VAOID);
glBindBuffer(GL_ARRAY_BUFFER, VBOID);
//glBufferData(GL_ARRAY_BUFFER, sizeof(planeOne.vertexArray), planeOne.vertexArray, GL_STATIC_DRAW);
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOID);
//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(planeOne.indexArray), planeOne.indexArray, GL_STATIC_DRAW);
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
glEnableVertexAttribArray(0);
glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
glEnableVertexAttribArray(1);
glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
glEnableVertexAttribArray(2);*/