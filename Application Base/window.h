#ifndef NAPP_WINDOW
#define NAPP_WINDOW

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include "settings.h"
#include "input.h"
#include "app.h"

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl3.h"

class Window {
public:

	Window(glm::ivec2 size, std::string name);

	~Window();

	void DrawBegin();
	void DrawEnd();

	void Resize(glm::ivec2 size);
	glm::ivec2 getSize();

	void Rename(std::string name);
	std::string getName();

	GLFWwindow* GetGLFWwindow();

	void SwitchThisToMainWindow();

	void ChangeClearColor(glm::vec4 new_color);

private:

	glm::vec4 clearColor = glm::vec4(0.07f, 0.13f, 0.17f, 1.0f);

	GLFWwindow* window;

	bool ownesImGuiContext = false;

	static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);

};


#endif
