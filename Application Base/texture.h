#ifndef NAPP_TEXTURE
#define NAPP_TEXTURE

#include <iostream>
#include <glad/glad.h>

class Texture {
public:
	Texture(const std::string& filepath);
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

	inline int GetWidth() const { return width; }
	inline int GetHeight() const { return height; }

	GLuint id;
private:
	int width, height, channels;
	std::string filepath;
};



#endif
