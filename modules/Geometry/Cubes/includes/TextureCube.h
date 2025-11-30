#pragma once

//Geometry
#include "./Cube.h"

//Lighitng
#include "../../../Lighting/includes/LightCube.h"
#include "../../../Lighting/includes/Material.h"


//include glStructure
#include "../../../GLStructure/includes/Texture.h"
#include "../../../GLStructure//includes/Camera.h"

class TextureCube : public Cube {
private:
	//Texture
	Texture texture;

	//Material
	Material material;

	//inverse model
	glm::mat4 transverseInverseModelMatrix;

public:
	TextureCube(glm::vec3 aPosition, glm::vec3 aColour, float aSideLength, VAO aVao, Shader aShader, Texture aTexture, Material aMaterial);

	void draw(glm::mat4 aViewMatrix, glm::mat4 aProjectionMatrix, LightCube aLightCube, Camera aCamera);

	void updatePosition(glm::vec3 aPosition);
	void updateSideLength(float aSideLength);
	void updateTransverseInverseModelMatrix();
};

