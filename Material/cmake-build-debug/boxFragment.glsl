#version 330 core
out vec4 FragColor;

//需要纹理再解除注释
/*in vec2 texCoord;
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float factor;*/

struct Material{ //各个光的颜色 相当于boxColor*lightColor
    vec3 ambientColor;
    vec3 diffuseColor;
    vec3 specularColor;
    float shininess;
};
struct LightStrength{ //各个光的强度  每种光的三个分量应该相同
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform Material material;
uniform LightStrength lightStrength;
uniform vec3 lightPos;
uniform vec3 cameraPos;
in vec3 fragPos;
in vec3 normal;
void main()
{
    //全局光
   vec3 ambient=lightStrength.ambient*material.ambientColor;
   vec3 lightDir=normalize(lightPos-fragPos);
   //漫反射光
   vec3 norm=normalize(normal);
   float diff=max(dot(lightDir,norm),0.0);
   vec3 diffuse=diff*material.diffuseColor;
   //反射高光
   vec3 viewDir=normalize(cameraPos-fragPos);
   vec3 reflectDir=reflect(-lightDir,norm);
   float spec=pow(max(dot(viewDir,reflectDir),0.0),material.shininess);
   vec3 specular=lightStrength.specular*spec*material.specularColor;


   FragColor=vec4((ambient+diffuse+specular),1.0f);
}
