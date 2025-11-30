#version 330 core
//layout values
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;

//world space uniforms
uniform mat4 model;
uniform mat4 transposeInverseModel;
uniform mat4 view;
uniform mat4 projection;

//information to be passed out next time
out vec3 fragPosition;
out vec2 texCoord;
out vec3 normal;

void main()
{
   gl_Position = projection * view * model * vec4(aPos, 1.0);
   fragPosition = vec3(model * vec4(aPos, 1));
   texCoord = aTexCoord;
   normal = mat3(transposeInverseModel) * aNormal;
}
