#version 460 core

// output 
out vec4 FragColor;

// vertex input
in vec2 texCoord;
in vec3 normal;
in vec3 positionWS;

// material settings
uniform sampler2D texture1;
uniform sampler2D texture2;
struct Material {
    vec3 albedo;
    float specStrength;
};
uniform Material material;

// global vars
struct Light {
    vec3 lightColor;
    float lightStrength;
    vec3 lightPos;
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
    vec4 tex1 = texture(texture1, texCoord);
    
    // diffuse lighting 
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(mainLight.lightPos - positionWS);
    float diff = max(dot(norm, lightDir), 0.0f);
    vec4 lighting = vec4(diff * mainLight.lightColor * mainLight.lightStrength, 1);

    // ambient lighting
    lighting.rgb += scene.ambientColor * scene.ambientStrength;

    // specular lighting
    vec3 viewDir = normalize(scene.viewPos - positionWS);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 32.0f);
    vec3 specular = material.specStrength * spec * mainLight.lightColor;
    lighting.rgb += specular;

    FragColor = tex1 * lighting;
}