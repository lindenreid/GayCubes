#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

uniform bool offset;

out vec4 vertexColor;

void main ()
{
	gl_Position = vec4(aPos, 1.0); // assumes input is in NDC lmfao

	if(offset){
		vertexColor = vec4(aColor, 1.0); // sets vertex color to input vertex color
	} else {
		vertexColor = vec4(1,0,0,1);
	}
}