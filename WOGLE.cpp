//standard libraries
#include <iostream>
#include <cmath>
#include <vector>

//openGL specific libraries
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <config.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
//STB library set up
#include <stb_image.h>

//header files for core GL infrastructure modules
#include "./modules/GLStructure/includes/Shader.h"
#include "./modules/GLStructure/includes/Texture.h"
#include "./modules/GLStructure/includes/Camera.h"
#include "./modules/GLStructure/includes/VAO.h"
#include "./modules/GLStructure/includes/KeyTracker.h"

//header files for geometry modules
#include "./modules/Geometry/includes/Circle.h"
#include "./modules/Geometry/includes/Plane.h"
#include "./modules/Geometry/Cubes/includes/CubeData.h"
#include "./modules/Geometry/Cubes/includes/Cube.h"
#include "./modules/Geometry/Cubes/includes/TextureCube.h"

//lighting
#include "./modules/Lighting/includes/LightCube.h"


//header files for collisions modules
#include "./modules/Collisions/BSP/includes/BSPT.h"

//header files for game object modules
#include "./modules/Game/includes/Particle.h"
#include "./modules/Game/includes/Wall.h"

//header file containing constants
#include "CONSTANTS.h"

//definitions
#define CLEAR "\033[0H"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

void processInput(GLFWwindow* window);

void renderWall(std::vector<Wall> aWallVector,  Shader aShader, VAO aVAO, glm::mat4 aViewMatrix);


KeyTracker globalKeyTracker = KeyTracker();

int main() {
    //ensures all textures are loaded in the correct way
    stbi_set_flip_vertically_on_load(true);

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(1000, 1000, "This is the window name", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    //glViewport(0, 0, 800, 600);                                                                                             
    glfwMakeContextCurrent(window);

    //we declare callback functions before window loop is made
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    Shader shaderOne("resources/shaders/original/originalVertexShader.glsl", "resources/shaders/original/originalFragmentShader.glsl");
    Particle particleOne(glm::vec3(0.0f, 0.0f, 1.0f), 0.1f, glm::vec3(1.0f, 1.0f, 1.0f));
    Camera cameraOne;

    //file paths cannot begin with "./" to be used for the fstream file reading method
    Texture textureBrickWall("resources/media/image/brickWallTexture.jpg");
    Texture textureUnit("resources/media/image/unitTestingTexture.png");
    Texture textureFloor("resources/media/image/floorTexture.jpg");
    Texture textureContainer("resources/media/image/containerTexture.png");
    Texture textureSpecularContainer("resources/media/image/containerSpecularTexture.png");
    Texture textureWhite("resources/media/image/whiteTexture.png");

    //cubes
    CubeData cubeData;

    //create and initialise LightCube
    Shader lightCubeShader("resources/shaders/light cube/lightCubeVertexShader.glsl", "resources/shaders/light cube/lightCubeFragmentShader.glsl");
    VAO lightCubeVAO(lightCubeShader);
    lightCubeVAO.bind();
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeData.LightCubeVertices), cubeData.LightCubeVertices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeData.LightCubeIndices), cubeData.LightCubeIndices, GL_STATIC_DRAW);
    LightCube lightCube(glm::vec3(0.5f, 0.5f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), 0.25f, lightCubeVAO, lightCubeShader, glm::vec3(0.4f), glm::vec3(0.6f), glm::vec3(1.0f));

    //create an intialise TextureCube
    Shader textureCubeShader("resources/shaders/texture cube/textureCubeVertexShader.glsl", "resources/shaders/texture cube/textureCubeFragmentShader.glsl");
    VAO textureCubeVAO(textureCubeShader);

    textureCubeVAO.bind();
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeData.cubeVertices), cubeData.cubeVertices, GL_STATIC_DRAW);
    Material textureMaterial(textureWhite, textureWhite, textureSpecularContainer, 1.0f);
    TextureCube textureCube(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 0.5f, textureCubeVAO, textureCubeShader, textureContainer, textureMaterial);

    std::vector<Wall> wallVector;
    //left
    Wall wallOne(glm::vec3(-1.0f, -1.0f, 0.0f), glm::vec3(-1.0f, 1.0f, 0.0f), glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), textureBrickWall);
    //right
    Wall wallTwo(glm::vec3(1.0f, -1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, -1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), textureBrickWall);
    //top
    Wall wallThree(glm::vec3(-1.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), textureBrickWall);
    //bottom
    Wall wallFour(glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec3(1.0f, -1.0f, 1.0f), glm::vec3(-1.0f, -1.0f, 0.0f), glm::vec3(1.0f, -1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), textureBrickWall);
    //floor 
    Wall floor(glm::vec3(-1.0f, -1.0f, 0.0f), glm::vec3(1.0f, -1.0f, 0.0f), glm::vec3(-1.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f), textureFloor);

    wallVector.push_back(wallOne);
    wallVector.push_back(wallTwo);
    wallVector.push_back(wallThree);
    wallVector.push_back(wallFour);
    wallVector.push_back(floor);

    BSPT* bspt = new BSPT(wallVector);

    VAO vaoOne(shaderOne);
    vaoOne.bind();
    glBufferData(GL_ARRAY_BUFFER, sizeof(particleOne.vertexArray), particleOne.vertexArray, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(particleOne.indexArray), particleOne.indexArray, GL_STATIC_DRAW);

    VAO vaoTwo(shaderOne);



    shaderOne.use();
    int textureOneLocation = glGetUniformLocation(shaderOne.getID(), "textureOne");
    glUniform1i(textureOneLocation, 0);


    glm::mat4 modelMatrix = glm::mat4(1.0f), viewMatrix = glm::mat4(1.0f), projectionMatrix = glm::mat4(1.0f);


    float currentFrameTime = 0.0f, lastFrameTime = 0.0f, deltaTime = 0.0f;

    glEnable(GL_DEPTH_TEST);


    while (!glfwWindowShouldClose(window))
    {
        currentFrameTime = glfwGetTime();
        deltaTime = currentFrameTime - lastFrameTime;
        lastFrameTime = currentFrameTime;

        //changes colour of screen
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        processInput(window);
        particleOne.processAll(globalKeyTracker.pressedKeys(), bspt, deltaTime);

        glm::vec3 scaledUnitDirection = particleOne.getUnitDirection();
        scaledUnitDirection *= 0.25;

        //calculate the camera target, position and vertical direction
        float particleRotation = particleOne.getDirectionAngle();
        glm::vec3 position = particleOne.getCenter() + glm::vec3(0.0f, 0.0f, 0.5f) - scaledUnitDirection - scaledUnitDirection - scaledUnitDirection;
        glm::vec3 target = particleOne.getCenter() + scaledUnitDirection;
        glm::vec3 vertical = glm::vec3(0.0f, 0.0f, 1.0f);

        cameraOne.calculateCameraViewMatrix(position, target, vertical);

        //calculate rotational matrix values
        modelMatrix = glm::mat4(1.0f);
        modelMatrix = glm::translate(modelMatrix, particleOne.getCenter());
        modelMatrix = glm::rotate(modelMatrix, particleOne.getDirectionAngle(), glm::vec3(0.0f, 0.0f, 1.0f));

        //calculate the view matrix
        viewMatrix = glm::mat4(1.0f);

        viewMatrix = cameraOne.getCameraViewMatrix();

        //calculates the projection matrix
        projectionMatrix = glm::perspective(pi / 4, 800.0f / 800.0f, 0.1f, 100.0f);

        //get addresses of shader uniforms

        int modelLocation = glGetUniformLocation(shaderOne.getID(), "model");
        int viewLocation = glGetUniformLocation(shaderOne.getID(), "view");
        int projectionLocation = glGetUniformLocation(shaderOne.getID(), "projection");

        shaderOne.use();
        //must use shader program before updating uniform, as update applied to currently used shader program
        glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));
        glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));
        glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

        //assigning texture values
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureUnit.getID());

        vaoOne.bind();

        glDrawElements(GL_TRIANGLES, 3 * numberOuterVertices, GL_UNSIGNED_INT, 0);

        renderWall(wallVector, shaderOne, vaoTwo, viewMatrix);

        lightCube.draw(viewMatrix, projectionMatrix);

        
        textureCube.draw(viewMatrix, projectionMatrix, lightCube, cameraOne);

        glfwSwapBuffers(window);
        glfwPollEvents();
        //std::cout << CLEAR;
    }
    glfwTerminate();

    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    globalKeyTracker.updateStatus(key, action);
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

void renderWall(std::vector<Wall> aWallVector, Shader aShader, VAO aVAO, glm::mat4 aViewMatrix) {


    aVAO.bind();
    glm::mat4 modelMatrix = glm::mat4(1.0f), viewMatrix = glm::mat4(1.0f), projectionMatrix = glm::mat4(1.0f);
    for (int i = 0; i < aWallVector.size(); i++) {
        Wall currentWall = aWallVector[i];

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, currentWall.getWallTexture().getID());

        glBufferData(GL_ARRAY_BUFFER, sizeof(currentWall.vertexArray), currentWall.vertexArray, GL_DYNAMIC_DRAW);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(currentWall.indexArray), currentWall.indexArray, GL_DYNAMIC_DRAW);

        modelMatrix = glm::mat4(1.0f);
        modelMatrix = glm::translate(modelMatrix, currentWall.getCenter());

        //calculate the view matrix
        viewMatrix = glm::mat4(1.0f);
        viewMatrix = aViewMatrix;

        //calculates the projection matrix
        projectionMatrix = glm::perspective(pi / 4, 800.0f / 800.0f, 0.1f, 100.0f);

        int modelLocation = glGetUniformLocation(aShader.getID(), "model");
        int viewLocation = glGetUniformLocation(aShader.getID(), "view");
        int projectionLocation = glGetUniformLocation(aShader.getID(), "projection");



        aShader.use();

        glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));
        glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));
        glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
}