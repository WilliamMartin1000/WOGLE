#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 scale;
uniform mat4 position;
uniform mat4 view;
uniform mat4 projection;

void main()
{ //commenting fixes VAO constructor error
   gl_Position = projection * view * position * scale * vec4(aPos, 1.0);
} //commenting fixes VAO constructor error