#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 pos;
in vec3 normal;

struct LightStrength{ //各个光的强度  每种光的三个分量应该相同
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    //点光源的衰减常数
    float linear;
    float quadratic;
};

uniform float shininess;
uniform LightStrength lightStrength;
uniform sampler2D diffuse1;
uniform sampler2D specular1;
uniform sampler2D normal1;
const vec3 cameraPos=vec3(0.0f,0.0f,5.0f);
const vec3 lightPos=vec3(4.0f,2.0f,2.0f);
void main()
{
     //全局光
       vec3 ambient=lightStrength.ambient*texture(diffuse1,TexCoords).rgb;
       vec3 lightDir=normalize(lightPos-pos);
       //漫反射光
       vec3 norm=normalize(normal);
       float diff=max(dot(lightDir,norm),0.0);
       vec3 diffuse=diff*texture(diffuse1,TexCoords).rgb;
       //反射高光
       vec3 viewDir=normalize(cameraPos-pos);
       vec3 reflectDir=reflect(-lightDir,norm);
       float spec=pow(max(dot(viewDir,reflectDir),0.0),shininess);
       vec3 specular=lightStrength.specular*spec*texture(specular1,TexCoords).rgb;

        //计算衰减
        float distance=length(pos-lightPos);
        float attenuation=1.0/(1.0+lightStrength.linear*distance+lightStrength.quadratic*distance*distance);


       FragColor=vec4((ambient+diffuse+specular)*attenuation,1.0f);
//       FragColor=vec4((specular)*attenuation,1.0f);
//       FragColor=vec4(texture(normal1,TexCoords).rgb,1.0f);

}