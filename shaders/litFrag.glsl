#version 460 core

// output 
out vec4 FragColor;

// vertex input
in vec2 texCoord;
in vec3 normal;
in vec3 positionWS;

// material settings
struct Material {
    sampler2D diffuseTex;
    sampler2D specularTex;
    vec3 albedo;
    float specStrength;
};
uniform Material material;

// global vars
struct Light {
    vec3 lightColor;
    float lightStrength;
    vec3 lightDir;
};
uniform Light mainLight;

struct SceneSettings {
    vec3 viewPos;
    vec3 ambientColor;
    float ambientStrength;
};
uniform SceneSettings scene;


void main ()
{
    vec3 albedoTex = texture(material.diffuseTex, texCoord).rgb;
    float specTex = texture(material.specularTex, texCoord).r;
    
    // diffuse lighting 
    vec3 norm = normalize(normal);
    float diff = max(dot(norm, mainLight.lightDir), 0.0f);
    vec4 lighting = vec4(albedoTex, 1) * vec4(diff * mainLight.lightColor * mainLight.lightStrength, 1);

    // ambient lighting
    lighting.rgb += albedoTex.rgb * scene.ambientColor * scene.ambientStrength;

    // specular lighting
    vec3 viewDir = normalize(scene.viewPos - positionWS);
    vec3 reflectDir = reflect(-mainLight.lightDir, norm);
    float spec = specTex * pow(max(dot(viewDir, reflectDir), 0.0f), 32.0f);
    vec3 specular = material.specStrength * spec * mainLight.lightColor;
    lighting.rgb += specular;

    //FragColor = vec4(texCoord, 0, 1);
    //FragColor = vec4(albedoTex, 1);
    //FragColor = vec4(specTex, specTex, specTex, 1.0f);
    FragColor = lighting;
}