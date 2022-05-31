#ifndef _RENDERER_OBJ
#define _RENDERER_OBJ

#include <vector>

#include <assimp-3.1.1/include/assimp/Importer.hpp>
#include <assimp-3.1.1/include/assimp/scene.h>
#include <assimp-3.1.1/include/assimp/postprocess.h>

#include "ShaderProgram.h"
#include "Mesh.h"
#include "Camera.h"
#include "Texture.h"
#include "Material.h"

namespace GayCubes
{
	class Renderer
	{
	public:
		Renderer(const char *path, Material mat);
		void draw(Camera camera, float* lightColor);
		void deallocate();

	private:
		Material _material;
		std::vector<Mesh> _meshes;
		std::string _directory;

		void loadModel(std::string path);
		void processNode(aiNode *node, const aiScene *scene);
		Mesh processMesh(aiMesh *mesh, const aiScene *scene);
		std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
	};
}

#endif //_RENDERER_OBJ

