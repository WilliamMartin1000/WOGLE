#version 330 core

//uniform passing information
uniform vec3 colour;

//data to be passed to the next stage
out vec4 fragColour;

void main()
{
    //calculating the colour for the fragment
    fragColour = vec4(colour, 1.0f);
}
