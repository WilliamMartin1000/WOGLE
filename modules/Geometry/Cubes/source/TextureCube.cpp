//header file
#include "../includes/TextureCube.h"

//OpenGL libraries
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

TextureCube::TextureCube(glm::vec3 aPosition, glm::vec3 aColour, float aSideLength, VAO aVao, Shader aShader, Texture aTexture, Material aMaterial) : Cube(aPosition, aColour, aSideLength, aVao, aShader) {
	updateTransverseInverseModelMatrix();
	texture = aTexture;
	material = aMaterial;
}

void TextureCube::draw(glm::mat4 aViewMatrix, glm::mat4 aProjectionMatrix, LightCube aLightCube, Camera aCamera) {
	//use shader
	shader.use();
	
	//update uniforms
	//uniforms for texture cube data
	shader.updateVec3("colour", colour);
	shader.updateMat4("model", modelMatrix);
	shader.updateMat4("transposeInverseModel", transverseInverseModelMatrix);
	shader.updateFloat("material.shininess", material.getShininess());
	//uniforms for world space matrices
	shader.updateMat4("view", aViewMatrix);
	shader.updateMat4("projection", aProjectionMatrix);
	//uniforms for camera properties
	shader.updateVec3("cameraPosition", aCamera.getCameraPosition());
	//uniforms for light properties
	shader.updateVec3("lightPosition", aLightCube.getPosition());
	shader.updateVec3("lightColour", aLightCube.getColour());
	shader.updateVec3("lightProperties.ambient", aLightCube.getAmbientStrength());
	shader.updateVec3("lightProperties.diffuse", aLightCube.getDiffuseStrength());
	shader.updateVec3("lightProperties.specular", aLightCube.getSpecularStrength());



	//bind the textures
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture.getID());
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, material.getAmbient().getID());
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, material.getDiffuse().getID());
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, material.getSpecular().getID());



	//bind the VAO
	vao.bind();

	//draw the cube (doesn't use an EBO)
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void TextureCube::updatePosition(glm::vec3 aPosition) {
	Cube::updatePosition(aPosition);
	updateTransverseInverseModelMatrix();
}

void TextureCube::updateSideLength(float aSideLength) {
	Cube::updateSideLength(aSideLength);
	updateTransverseInverseModelMatrix();
}

void TextureCube::updateTransverseInverseModelMatrix() {
	transverseInverseModelMatrix = glm::transpose(glm::inverse(modelMatrix));
}