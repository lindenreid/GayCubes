#ifndef _RENDERER_OBJ
#define _RENDERER_OBJ

#include <vector>

#include <assimp-3.1.1/include/assimp/Importer.hpp>
#include <assimp-3.1.1/include/assimp/scene.h>
#include <assimp-3.1.1/include/assimp/postprocess.h>

#include <glm/glm/glm.hpp>

#include "ShaderProgram.h"
#include "Mesh.h"
#include "Camera.h"
#include "Texture.h"
#include "Material.h"
#include "SceneLighting.h"

namespace GayCubes
{
	class Renderer
	{
	public:
		Renderer(const char *path, Material mat);
		// TODO: store positional information in a Transform
		void draw(Camera camera, SceneLighting lighting, glm::vec3 position, glm::vec3 scale);
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

