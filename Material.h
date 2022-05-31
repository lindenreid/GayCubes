#ifndef _MATERIAL_OBJ
#define _MATERIAL_OBJ

namespace GayCubes
{
	class Material
	{
	public:
		ShaderProgram Shader;
		Texture tex1;
		Texture tex2;
		float specStrength;
		
		Material(ShaderProgram shader, Texture tex1, Texture tex2, float specStrength);
		void bindResources();
		void deallocate();

	private:
		void loadTextures();
	};
}

#endif //_MATERIAL_OBJ
