#include "app.h"

void Application::run() {
	std::cout << "Hello World!\n";

	// Creating the window needs to go BEFORE any code that tries to use opengl functions
	Window window(glm::ivec2(640, 640), "Project Template");

	Input::Init(window.GetGLFWwindow());

	Mesh mesh;

	// Add a simple quad
	mesh.AddVertex({ glm::vec3(-0.75f, -0.75f, 0.0f), glm::vec2(0.0f, 0.0f) });
	mesh.AddVertex({ glm::vec3(0.75f, -0.75f, 0.0f), glm::vec2(1.0f, 0.0f) });
	mesh.AddVertex({ glm::vec3(0.75f,  0.75f, 0.0f), glm::vec2(1.0f, 1.0f) });
	mesh.AddVertex({ glm::vec3(-0.75f,  0.75f, 0.0f), glm::vec2(0.0f, 1.0f) });

	mesh.AddIndex(0); mesh.AddIndex(1); mesh.AddIndex(2);
	mesh.AddIndex(2); mesh.AddIndex(3); mesh.AddIndex(0);

	mesh.Build();

	Shader shader("vert.glsl", "frag.glsl");
	Texture texture("big guy.png");

	shader.Activate();
	texture.Bind(0);
	shader.SetInt("u_Texture", 0);

	Query query;

	while (not glfwWindowShouldClose(window.GetGLFWwindow())) {
		MainLoopBegin();

		// === Main Update Logic ===
		
		if (Input::IsKeyPressed(GLFW_KEY_ESCAPE)) {
			// Close the app if ESC is pressed
			glfwSetWindowShouldClose(window.GetGLFWwindow(), true);
		}

		RenderLoopBegin(query);
		// === Render Section ===

		shader.Activate();
		mesh.Draw();
		
		RenderLoopEnd(query);

		// Swap frame buffers
		glfwSwapBuffers(window.GetGLFWwindow());
	}

	std::cout << "Goodbye World!\n";
}

#pragma region the stuff you dont care about
Application::Application() {
	//Initialize glfw
	if (!glfwInit()) {
		std::cout << "Glfw initialization failed!\n";
	}

	//Tell glfw what openGl version we are using
	//version 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	Settings::Load("settings.cfg");

	//We do a bit of configuring
	glfwSwapInterval(0);
}

Application::~Application() {
	glfwTerminate();
}

void Application::MainLoopBegin() {
	isQuerying = DevMenu::shouldQuery;
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	glad_glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glfwPollEvents();
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	Input::Update();

	if (Input::IsKeyJustPressed(GLFW_KEY_F3) and Settings::GetBool("DevMenu")) {
		// Open the DevMenu if F3 is pressed
		DevMenu::SetVisible(not DevMenu::IsVisible());
	}
}

void Application::RenderLoopBegin(Query& query) const {
	if (isQuerying)
		query.BeginQuery();
}

void Application::RenderLoopEnd(Query& query) const {
	if (isQuerying) {
		
		query.EndQuery();

		DevMenu::UpdateRenderInfo(query.GetResult());

		DevMenu::shouldQuery = false;
	}


	DevMenu::Draw();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

#pragma endregion