#version 330 core
out vec4 FragColor;

//需要纹理再解除注释
in vec2 texCoord;

struct Material{ //各个光的颜色 相当于boxColor*lightColor
    sampler2D diffuseTex;
    sampler2D specularTex;
    float shininess;
};
struct Light{ //各个光的强度  每种光的三个分量应该相同
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;


    //聚光灯的参数
    float innerCos;
    float outerCos;
    vec3 spotDirection;

    //点光源的衰减常数
    float linear;
    float quadratic;
};
uniform Material material;
uniform Light light;
uniform vec3 lightPos;
uniform vec3 cameraPos;
in vec3 fragPos;
in vec3 normal;
void main()
{

    //全局光
   vec3 ambient=light.ambient*texture(material.diffuseTex,texCoord).rgb;
   vec3 lightDir=normalize(lightPos-fragPos);
   //漫反射光
   vec3 norm=normalize(normal);
   float diff=max(dot(lightDir,norm),0.0);
   vec3 diffuse=diff*texture(material.diffuseTex,texCoord).rgb;
   //反射高光
   vec3 viewDir=normalize(cameraPos-fragPos);
   vec3 reflectDir=reflect(-lightDir,norm);
   float spec=pow(max(dot(viewDir,reflectDir),0.0),material.shininess);
   vec3 specular=light.specular*spec*texture(material.specularTex,texCoord).rgb;

    //聚光灯强度计算
    float cutOffCos=dot(-lightDir,light.spotDirection);
    float intensity=clamp((cutOffCos-light.outerCos)/(light.innerCos-light.outerCos),0.0,1.0);
    //计算衰减
    float distance=length(lightPos-fragPos);
    float attenuation=1/(1.0+light.linear*distance+light.quadratic*distance*distance);


   FragColor=vec4((ambient+(diffuse+specular)*intensity)*attenuation,1.0f);
}
