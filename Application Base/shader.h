#ifndef NAPP_SHADER
#define NAPP_SHADER

#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <glm/glm.hpp>

class Shader {
public:

	Shader(std::string vert_filepath, std::string frag_filepath);
	~Shader();

	void Activate();

	GLuint id;

	// Functions too set shader uniforms
	void SetFloat(const std::string& name, float value) const;
	void SetInt(const std::string& name, int value) const;
	void SetVec2(const std::string& name, const glm::vec2& value) const;
	void SetVec3(const std::string& name, const glm::vec3& value) const;
	void SetVec4(const std::string& name, const glm::vec4& value) const;
	void SetMat4(const std::string& name, const glm::mat4& matrix) const;

private:

	void CompileErrors(unsigned int shader, const char* type);
};


#endif // !NAPP_SHADER

