#include "ShaderProgram.h"
#include "Mesh.h"
#include "Camera.h"
#include "Texture.h"
#include "Material.h"

namespace GayCubes
{
	Material::Material(ShaderProgram shader, Texture albedoTex, Texture specTex, float specStrength)
		: Shader(shader),
			tex_albedo(albedoTex),
			tex_spec(specTex)
	{
		this->specStrength = specStrength;
	}

	void Material::bindResources()
	{
		tex_albedo.bindTexture();
		tex_spec.bindTexture();
	}

	void Material::deallocate()
	{
		Shader.deallocateProgram();
	}
}