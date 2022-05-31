#include "ShaderProgram.h"
#include "Mesh.h"
#include "Camera.h"
#include "Texture.h"
#include "Material.h"

namespace GayCubes
{
	Material::Material(ShaderProgram shader, Texture tex1, Texture tex2, float specStrength)
		: Shader(shader),
			tex1(tex1),
			tex2(tex2)
	{
		this->specStrength = specStrength;
		loadTextures();
	}

	void Material::loadTextures()
	{
		tex1.loadTexture();
		tex2.loadTexture();
	}

	void Material::bindResources()
	{
		tex1.bindTexture();
		tex2.bindTexture();
		//glActiveTexture(GL_TEXTURE0);
	}

	void Material::deallocate()
	{
		Shader.deallocateProgram();
	}
}