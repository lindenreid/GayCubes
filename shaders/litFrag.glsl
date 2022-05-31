#version 330 core

// output 
out vec4 FragColor;

// vertex input
in vec2 texCoord;
in vec3 normal;
in vec3 positionWS;

// material settings
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform vec3 albedo;
uniform float specStrength;

// global vars
uniform vec3 lightColor;
uniform float lightStrength;
uniform vec3 lightPos;

uniform vec3 viewPos;

uniform vec3 ambientColor;
uniform float ambientStrength;

void main ()
{
    vec4 tex1 = texture(texture1, texCoord);
    
    // diffuse lighting 
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPos - positionWS);
    float diff = max(dot(norm, lightDir), 0.0f);
    vec4 lighting = vec4(diff * lightColor, 1);

    // ambient lighting
    lighting.rgb += ambientColor * ambientStrength;

    // specular lighting
    vec3 viewDir = normalize(viewPos - positionWS);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 32.0f);
    vec3 specular = specStrength * spec * lightColor;
    lighting.rgb += specular;

    FragColor = tex1 * lighting;
}