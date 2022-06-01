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
struct Light_Directional {
    vec3 lightColor;
    float lightStrength;
    vec3 lightDir;
};

#define NUM_DIR_LIGHTS 2
struct SceneSettings {
    vec3 viewPos;
    vec3 ambientColor;
    float ambientStrength;
};
uniform SceneSettings scene;
uniform Light_Directional[NUM_DIR_LIGHTS] directionalLights;

vec3 DirectionalLightContribution (
    vec3 albedoTex,
    vec3 normal,
    float specTex,
    Light_Directional light
) {
    // diffuse lighting
    float diff = max(dot(normal, light.lightDir), 0.0f);
    vec3 lighting = albedoTex * diff * light.lightColor * light.lightStrength;

    // specular lighting
    vec3 viewDir = normalize(scene.viewPos - positionWS);
    vec3 reflectDir = reflect(-light.lightDir, normal);
    float spec = specTex * pow(max(dot(viewDir, reflectDir), 0.0f), 32.0f);
    vec3 specular = material.specStrength * spec * light.lightColor;
    lighting.rgb += specular;

    return lighting;
}


void main ()
{
    // texture inputs
    vec3 albedoTex = texture(material.diffuseTex, texCoord).rgb;
    float specTex = texture(material.specularTex, texCoord).r;
    
    // normal inputs
    vec3 norm = normalize(normal);
    
    vec3 color = vec3(0,0,0);
    // directional lights 
    for(int i = 0; i < NUM_DIR_LIGHTS; i++)
    {
        color += DirectionalLightContribution(albedoTex, norm, specTex, directionalLights[i]);
    }

    // scene ambient lighting
    color.rgb += albedoTex.rgb * scene.ambientColor * scene.ambientStrength;

    //FragColor = vec4(texCoord, 0, 1);
    //FragColor = vec4(albedoTex, 1);
    //FragColor = vec4(specTex, specTex, specTex, 1.0f);
    FragColor = vec4(color, 1);
}