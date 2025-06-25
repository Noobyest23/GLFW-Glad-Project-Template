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
	//glfwSwapInterval(0); this enables v-sync on the window but framerate limiting already happens so i disabled it
	
	// Initialize imgui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	(void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
}

Window::~Window() {
	// Cleanup ImGui
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();
}

// ====== API Calls ====== //

void Window::DrawBegin() {
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	glad_glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glfwPollEvents();
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	Input::Update();
}

void Window::DrawEnd() {
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
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

// Private Functions STAY OUT... jk //

void Window::FramebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}