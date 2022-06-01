#version 460 core

out vec4 FragColor;

#define NUM_DIR_LIGHTS 2
struct Light_Directional {
    vec3 lightColor;
    float lightStrength;
    vec3 lightDir;
};
uniform Light_Directional[NUM_DIR_LIGHTS] directionalLights;

void main ()
{
    FragColor = vec4(directionalLights[0].lightColor, 1);
}