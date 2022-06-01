#ifndef _MATERIAL_OBJ
#define _MATERIAL_OBJ

namespace GayCubes
{
	class Material
	{
	public:
		ShaderProgram Shader;
		Texture tex_albedo;
		Texture tex_spec;
		float specStrength;
		
		Material(ShaderProgram shader, Texture albedoTex, Texture specTex, float specStrength);
		void bindResources();
		void deallocate();

	private:
		void loadTextures();
	};
}

#endif //_MATERIAL_OBJ
