#version 330 core
out vec4 FragColor;

//需要纹理再解除注释
/*in vec2 texCoord;
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float factor;*/
uniform vec3 lightColor;
uniform float ambientStrength;
uniform float specularStrength;
uniform vec3 lightPos;
uniform vec3 cameraPos;
in vec3 fragPos;
in vec3 normal;
void main()
{
   vec3 boxColor=vec3(0.925f,0.472f,0.308f);
   vec3 ambient=ambientStrength*lightColor;
   vec3 lightDir=normalize(lightPos-fragPos);
   //漫反射光
   vec3 norm=normalize(normal);
   float diff=max(dot(lightDir,norm),0.0);
   vec3 diffuse=diff*lightColor;
   //反射高光
   vec3 viewDir=normalize(cameraPos-fragPos);
   vec3 reflectDir=reflect(-lightDir,norm);
   float spec=pow(max(dot(viewDir,reflectDir),0.0),32);
   vec3 specular=specularStrength*spec*lightColor;


   FragColor=vec4((ambient+diffuse+specular)*boxColor,1.0f);
}
