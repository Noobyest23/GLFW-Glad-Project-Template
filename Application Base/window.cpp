#include "window.h"

Window::Window(glm::ivec2 size, std::string name) {
	//Initialize glfw
	if (!glfwInit()) {
		std::cout << "Glfw initialization failed!\n";
	}

	//Tell glfw what openGl version we are using
	//version 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Create the Glfw window
	window = glfwCreateWindow(size.x, size.y, name.c_str(), NULL, NULL);
	if (!window)
	{
		std::cout << "Window or OpenGL context creation failed\n";
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);



	//Initialize glad AFTER the window becomes current
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Glad initialization failed\n";
	}
	//Specifiy the opengl viewport
	glViewport(0, 0, size.x, size.y);

	// Configurations
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	if (Settings::GetBool("3D")) {
		glEnable(GL_DEPTH_TEST);
	}
	glfwSwapInterval(0); //framerate limiting already happens
	
	// ImGui can only be initialized once and only supports a single window.
	// Consecutive windows will not support im gui
	if (not has_main_window) {
		has_main_window = true;
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 330");
		ownesImGuiContext = true;
	}

}

Window::~Window() {
	if (ownesImGuiContext) {
		has_main_window = false;
	}
	glfwDestroyWindow(window);
	glfwTerminate();
}

// ====== API Calls ====== //

void Window::DrawBegin() {
	glfwMakeContextCurrent(window);
	glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
	glad_glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	if (ownesImGuiContext) {
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		glfwPollEvents();
		Input::Update();
	}
}

void Window::DrawEnd() {
	if (ownesImGuiContext) {
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
	glfwSwapBuffers(window);
}

void Window::Resize(glm::ivec2 size) {
	glfwSetWindowSize(window, size.x, size.y);
}

glm::ivec2 Window::getSize() {
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	return glm::ivec2(width, height);
}

void Window::Rename(std::string name) {
	glfwSetWindowTitle(window, name.c_str());
}

std::string Window::getName() {
	std::string name = glfwGetWindowTitle(window);
	return name;
}

GLFWwindow* Window::GetGLFWwindow() {
	return window;
}

void Window::SwitchThisToMainWindow() {
	if (not ownesImGuiContext) {
		if (has_main_window) {
			std::cout << "A main window already exists, delete that one and then switch\n";
		}
		else {
			ownesImGuiContext = true;
			has_main_window = true;
		}
	}
	else {
		std::cout << "Im already the main window!\n";
	}
}

void Window::ChangeClearColor(glm::vec4 newColor) {
	clearColor = newColor;
}

// Private Functions STAY OUT... jk //

void Window::FramebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}