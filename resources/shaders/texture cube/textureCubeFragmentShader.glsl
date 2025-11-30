#version 330 core

//struct for material
struct Material{
    sampler2D ambient;
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct LightProperties{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

//information passed in from earlier stage
in vec3 fragPosition;
in vec2 texCoord;
in vec3 normal;

//uniform passing object information
uniform sampler2D textureOne;
uniform vec3 colour;
uniform Material material;

//uniform passing camera information
uniform vec3 cameraPosition;

//uniform passing in light information
uniform vec3 lightColour;
uniform vec3 lightPosition;
uniform LightProperties lightProperties;


//data to be passed to the next stage
out vec4 fragColour;

void main()
{
    //caluclate ambient value
    vec3 ambientResult = vec3(texture(material.ambient, texCoord)) * lightProperties.ambient;


    //calculate diffuse lighting
    vec3 norm = normalize(normal);
    vec3 lightDirection = normalize(lightPosition - fragPosition);
    float alignment = max(dot(norm, lightDirection), 0.0f); //ensures that alighment > 0
    vec3 diffuseResult = alignment * vec3(texture(material.diffuse, texCoord))* lightProperties.diffuse;

    //calculate specular lighting
    vec3 viewDirection = normalize(cameraPosition - fragPosition);
    vec3 reflectedLightDirection = reflect(-lightDirection, norm);
    float spec = pow(max(dot(viewDirection, reflectedLightDirection),0.0f), material.shininess);
    
    vec3 specularResult = lightProperties.specular * vec3(texture(material.specular, texCoord)) *  spec;


    //combine them all together
    vec3 result = (specularResult + ambientResult + diffuseResult) * colour * lightColour;


    //calculating the colour for the fragment
    fragColour =  vec4(result, 1.0f)* texture(textureOne, texCoord);
}
