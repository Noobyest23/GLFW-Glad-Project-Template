#ifndef NAPP_INPUT
#define NAPP_INPUT

#include <GLFW/glfw3.h>
#include <unordered_map>

class Input {
public:
	static void Init(GLFWwindow* window);
	static void Update();

	static bool IsKeyPressed(int key);
	static bool IsKeyJustPressed(int key);
	static bool IsMouseButtonPressed(int button);
	static void GetMousePosition(double& x, double& y);

private:
	static GLFWwindow* s_Window;
	static std::unordered_map<int, bool> s_CurrentKeys;
	static std::unordered_map<int, bool> s_PreviousKeys;
};


#endif
