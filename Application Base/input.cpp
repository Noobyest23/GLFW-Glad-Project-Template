#include "Input.h"

GLFWwindow* Input::s_Window = nullptr;
std::unordered_map<int, bool> Input::s_CurrentKeys;
std::unordered_map<int, bool> Input::s_PreviousKeys;

void Input::Init(GLFWwindow* window) {
	s_Window = window;
}

void Input::Update() {
	s_PreviousKeys = s_CurrentKeys;

	// Update current key state
	for (int key = GLFW_KEY_SPACE; key <= GLFW_KEY_LAST; key++) {
		s_CurrentKeys[key] = glfwGetKey(s_Window, key) == GLFW_PRESS;
	}
}

bool Input::IsKeyPressed(int key) {
	return glfwGetKey(s_Window, key) == GLFW_PRESS;
}

bool Input::IsKeyJustPressed(int key) {
	return s_CurrentKeys[key] && !s_PreviousKeys[key];
}

bool Input::IsMouseButtonPressed(int button) {
	return glfwGetMouseButton(s_Window, button) == GLFW_PRESS;
}

void Input::GetMousePosition(double& x, double& y) {
	glfwGetCursorPos(s_Window, &x, &y);
}
