#version 330 core
out vec4 FragColor;
in vec2 texCoord;
uniform sampler2D colorTex;
void main()
{
   vec3 temp=texture(colorTex,texCoord).rgb;
   FragColor=vec4(texture(colorTex,texCoord).rgb,1.0f);
}