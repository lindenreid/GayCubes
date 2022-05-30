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

void main ()
{
    vec4 tex1 = texture(texture1, texCoord);
    vec4 tex2 = texture(texture2, texCoord);
    FragColor = mix(tex1, tex2, 0.2f) * vec4(albedo, 1) * vec4(lightColor, 1);
}