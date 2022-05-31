#version 460 core

out vec4 FragColor;

struct Light {
    vec3 lightColor;
    float lightStrength;
    vec3 lightPos;
};
uniform Light mainLight;

void main ()
{
    FragColor = vec4(mainLight.lightColor, 1);
}