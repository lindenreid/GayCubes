#include <vector>

#include <GLAD/glad/glad.h>

#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

#include <assimp-3.1.1/include/assimp/Importer.hpp>
#include <assimp-3.1.1/include/assimp/scene.h>
#include <assimp-3.1.1/include/assimp/postprocess.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

#include "Renderer.h"
#include "ShaderProgram.h"
#include "Mesh.h"
#include "Color.h"
#include "Texture.h"
#include "Material.h"
#include "Light.h"
#include "SceneLighting.h"

namespace GayCubes
{
	// ------------------------------------------------------------------------
	Renderer::Renderer(const char* path, Material mat)
		: _material(mat)
	{
		loadModel(path);

		for (int i = 0; i < _meshes.size(); i++)
		{
			_meshes[i].bindMesh();
		}
	}

	// ------------------------------------------------------------------------
	void Renderer::loadModel(std::string path)
	{
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			std::cout << "assimp error: " << importer.GetErrorString() << std::endl;
			return;
		}
		_directory = path.substr(0, path.find_last_of('/'));

		processNode(scene->mRootNode, scene);
	}

	// ------------------------------------------------------------------------
	// visiting all children recursively presevers hierarchy; 
	// may want to actually create transform hierarchy some day!
	void Renderer::processNode(aiNode* node, const aiScene* scene)
	{
		// process all node's meshes
		for (unsigned int i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			_meshes.push_back(processMesh(mesh, scene));
		}
		// then visit all children
		for (unsigned int i = 0; i < node->mNumChildren; i++)
		{
			processNode(node->mChildren[i], scene);
		}
	}

	// ------------------------------------------------------------------------
	Mesh Renderer::processMesh(aiMesh* mesh, const aiScene* scene)
	{
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;

		for (unsigned int i = 0; i < mesh->mNumVertices; i++)
		{
			Vertex vertex;
			glm::vec3 vec;
			vec.x = mesh->mVertices[i].x;
			vec.y = mesh->mVertices[i].y;
			vec.z = mesh->mVertices[i].z;
			vertex.Position = vec;
			
			vec.x = mesh->mNormals[i].x;
			vec.y = mesh->mNormals[i].y;
			vec.z = mesh->mNormals[i].z;
			vertex.Normal = vec;

			if (mesh->mTextureCoords[0])
			{
				glm::vec2 vecc;
				vecc.x = mesh->mTextureCoords[0][i].x;
				vecc.y = mesh->mTextureCoords[0][i].y;
				vertex.TexCoords = vecc;
			}
			else
			{
				vertex.TexCoords = glm::vec2(0.0f);
			}
			
			vertices.push_back(vertex);
		}

		for (unsigned int i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			for (unsigned int j = 0; j < face.mNumIndices; j++)
			{
				indices.push_back(face.mIndices[j]);
			}
		}

		return Mesh(vertices, indices);
	}

	// ------------------------------------------------------------------------
	void Renderer::draw(Camera camera, SceneLighting lighting, glm::vec3 position, glm::vec3 scale)
	{
		ShaderProgram shader = _material.Shader;

		shader.useProgram();

		// main light properties
		float l[3];
		float* lightColor = lighting._mainDirectionalLight._color.toArray(l);
		shader.setGlobalVec3Value(lightColor, "directionalLights[0].lightColor");
		shader.setGlobalVec3Value(glm::value_ptr(lighting._mainDirectionalLight._direction), "directionalLights[0].lightDir");
		shader.setGlobalFloatValue(lighting._mainDirectionalLight._strength, "directionalLights[0].lightStrength");

		float* lightColor2 = Color::red.toArray(l);
		shader.setGlobalVec3Value(lightColor2, "directionalLights[1].lightColor");
		glm::vec3 dir = glm::normalize(glm::vec3(0.5f, 0.5f, 0.0f));
		shader.setGlobalVec3Value(glm::value_ptr(dir), "directionalLights[1].lightDir");
		shader.setGlobalFloatValue(1.0f, "directionalLights[1].lightStrength");

		// scene properties
		lightColor = lighting._ambientColor.toArray(l);
		shader.setGlobalVec3Value(lightColor, "scene.ambientColor");
		shader.setGlobalFloatValue(lighting._ambientStrength, "scene.ambientStrength");
		shader.setGlobalVec3Value(glm::value_ptr(camera._position), "scene.viewPos");

		// material properties
		float coral[3] = {1.0f, 1.0f, 1.0f};
		shader.setGlobalVec3Value(coral, "material.albedo");
		shader.setGlobalFloatValue(_material.specStrength, "material.specStrength");

		// transform matrices
		shader.setGlobalMatrix4Value(camera.projection(), "projection");
		shader.setGlobalMatrix4Value(camera.viewMatrix(), "view");
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, position);
		model = glm::scale(model, scale);
		shader.setGlobalMatrix4Value(model, "model");
		glm::mat4 modelIT = glm::inverse(model);
		modelIT = glm::transpose(modelIT);
		shader.setGlobalMatrix4Value(modelIT, "model_inv_trans");

		// textures
		shader.setGlobalIntValue(0, "material.diffuseTex");
		shader.setGlobalIntValue(1, "material.specularTex");
		_material.bindResources();

		// draw verts
		for (int i = 0; i < _meshes.size(); i++)
		{
			_meshes[i].drawMesh();
		}
	}

	// ------------------------------------------------------------------------
	void Renderer::deallocate()
	{
		_material.deallocate();
		for (int i = 0; i < _meshes.size(); i++)
		{
			_meshes[i].deallocate();
		}
	}
}