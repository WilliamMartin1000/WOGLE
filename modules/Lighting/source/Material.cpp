//header file
#include "../includes/Material.h"

Material::Material(Texture aAmbient, Texture aDiffuse, Texture aSpecular, float aShininess) {
	ambient = aAmbient;
	diffuse = aDiffuse;
	specular = aSpecular;
	shininess = aShininess;
}

Material::Material() {
	//nothing
}

Material::Material(const Material& copyMaterial) {
	ambient = copyMaterial.ambient;
	diffuse = copyMaterial.diffuse;
	specular = copyMaterial.specular;
	shininess = copyMaterial.shininess;
}

// get and set methods
Texture Material::getAmbient() {
	return ambient;
}
Texture Material::getDiffuse() {
	return diffuse;
}
Texture Material::getSpecular() {
	return specular;
}
float Material::getShininess() {
	return shininess;
}