#ifndef NAPP_MESH
#define NAPP_MESH

#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>

struct Vertex {
	glm::vec3 position;
	glm::vec2 texcoord;
};

class Mesh {
public:
	Mesh();
	~Mesh();

	void AddVertex(const Vertex& vertex);
	void AddIndex(unsigned int index);

	void Build();
	void Draw() const;

private:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	GLuint vao = 0;
	GLuint vbo = 0;
	GLuint ebo = 0;
	bool built = false;
};




#endif
