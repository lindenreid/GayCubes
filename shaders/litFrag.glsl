#version 330 core

// output 
out vec4 FragColor;

// vertex input
in vec2 texCoord;
in vec3 normal;
in vec3 positionWS;

// globals
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform vec3 albedo;
uniform vec3 lightColor;
uniform float lightStrength;
uniform vec3 lightPos;

void main ()
{
    vec4 tex1 = texture(texture1, texCoord);
    
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPos - positionWS);
    float diff = max(dot(norm, lightDir), 0.0f);
    vec4 diffuse = vec4(diff * lightColor, 1);

    FragColor = tex1 * diffuse;
}