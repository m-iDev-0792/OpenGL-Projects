#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 pos;

uniform sampler2D diffuse1;

void main()
{
    FragColor=texture(diffuse1,TexCoords);
}