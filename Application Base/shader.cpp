#include "shader.h"

Shader::Shader(std::string vert_filepath, std::string frag_filepath) {

	std::string vert_src;
	std::string frag_src;

	std::ifstream in_v(vert_filepath, std::ios::binary);
	if (in_v)
	{
		in_v.seekg(0, std::ios::end);
		vert_src.resize(in_v.tellg());
		in_v.seekg(0, std::ios::beg);
		in_v.read(&vert_src[0], vert_src.size());
		in_v.close();
	}
	std::ifstream in_f(frag_filepath, std::ios::binary);
	if (in_f)
	{
		in_f.seekg(0, std::ios::end);
		frag_src.resize(in_f.tellg());
		in_f.seekg(0, std::ios::beg);
		in_f.read(&frag_src[0], frag_src.size());
		in_f.close();
	}

	const char* vertexSource = vert_src.c_str();
	const char* fragmentSource = frag_src.c_str();

	// Create Vertex Shader Object and get its reference
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// Attach Vertex Shader source to the Vertex Shader Object
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	// Compile the Vertex Shader into machine code
	glCompileShader(vertexShader);
	CompileErrors(vertexShader, "VERTEX");

	// Create Fragment Shader Object and get its reference
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// Attach Fragment Shader source to the Fragment Shader Object
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	// Compile the Vertex Shader into machine code
	glCompileShader(fragmentShader);
	CompileErrors(fragmentShader, "FRAGMENT");

	// Create Shader Program Object and get its reference
	id = glCreateProgram();

	// Attach the Vertex and Fragment Shaders to the Shader Program
	glAttachShader(id, vertexShader);
	glAttachShader(id, fragmentShader);
	// Wrap-up/Link all the shaders together into the Shader Program
	glLinkProgram(id);
	CompileErrors(id, "PROGRAM");

	// Delete the now useless Vertex and Fragment Shader objects
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

}

Shader::~Shader() {
	glDeleteProgram(id);
}

void Shader::Activate() {
	glUseProgram(id);
}

void Shader::CompileErrors(unsigned int shader, const char* type) {
	GLint hasCompiled;
	char infoLog[1024];
	if (type != "PROGRAM") {
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE) {
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER COMPILATION ERROR FOR:" << type << "\n" << std::endl;
			std::cout << infoLog;
		}
	}
	else {
		glGetProgramiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE) {
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER LINKING ERROR FOR:" << type << "\n" << std::endl;
			std::cout << infoLog;
		}
	}
}

void Shader::SetFloat(const std::string& name, float value) const {
	glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::SetInt(const std::string& name, int value) const {
	glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::SetVec2(const std::string& name, const glm::vec2& value) const {
	glUniform2fv(glGetUniformLocation(id, name.c_str()), 1, &value[0]);
}

void Shader::SetVec3(const std::string& name, const glm::vec3& value) const {
	glUniform3fv(glGetUniformLocation(id, name.c_str()), 1, &value[0]);
}

void Shader::SetVec4(const std::string& name, const glm::vec4& value) const {
	glUniform4fv(glGetUniformLocation(id, name.c_str()), 1, &value[0]);
}

void Shader::SetMat4(const std::string& name, const glm::mat4& matrix) const {
	glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &matrix[0][0]);
}