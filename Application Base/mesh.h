#ifndef NAPP_MESH
#define NAPP_MESH

#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> // for translate, rotate, scale
#include <glm/gtc/type_ptr.hpp>         // for value_ptr

#include "shader.h"

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

	void SetShader(Shader* shader);
	glm::mat4 GetModelMatrix() const;

	glm::vec3 position = glm::vec3(0);
	glm::vec3 rotation = glm::vec3(0);
	glm::vec3 scale = glm::vec3(1.0f);


private:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	Shader* shader;

	GLuint vao = 0;
	GLuint vbo = 0;
	GLuint ebo = 0;
	bool built = false;
};




#endif
