#ifndef _MESH_OBJ
#define _MESH_OBJ

#include <vector>

#include <glm/glm/glm.hpp>

namespace GayCubes
{
	struct Vertex
	{
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec2 TexCoords;
	};

	class Mesh
	{
	public:
		Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
		void bindMesh();
		void drawMesh();
		void deallocate();

	private:
		std::vector<Vertex> _vertices;
		std::vector<unsigned int> _indices;
		unsigned int _VAO, _VBO, _EBO;
	};
}

#endif //_MESH_OBJ

