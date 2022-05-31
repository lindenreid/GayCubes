#version 330 core

// output 
out vec4 FragColor;

// vertex input
in vec2 texCoord;

// globals
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform vec3 albedo;
uniform vec3 lightColor;
uniform float lightStrength;

void main ()
{
    vec4 tex1 = texture(texture1, texCoord);
    FragColor = tex1 * lightStrength * vec4(lightColor, 1);
}