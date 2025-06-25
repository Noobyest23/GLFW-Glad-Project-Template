#include "app.h"

void Application::run() {
	std::cout << "Hello World!\n";

	// Creating the window needs to go BEFORE any code that tries to use opengl functions
	Window window(glm::ivec2(640, 640), "Project Template");
	// Remember that when you create a window its openGL context becomes current
	// So if you create a mesh after this windows creation then the mesh belongs to that window and will only draw on that window
	// you can change which window is current with glfwMakeContextCurrent(window.GetGLFWwindow());
	
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

		
		// === Render Section ===
		window.DrawBegin();
		RenderLoopBegin(query);

		shader.Activate();
		mesh.Draw();

		RenderLoopEnd(query);
		window.DrawEnd();

		MainLoopEnd();

	}

	std::cout << "Goodbye World!\n";
}

#pragma region the stuff you dont care about
Application::Application() {
	
	// Initialize imgui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	(void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	ImGui::StyleColorsDark();

	Settings::Load("settings.cfg");
}

Application::~Application() {
	// Cleanup ImGui
	if (ImGui::GetCurrentContext() != nullptr) {
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}
}

void Application::MainLoopBegin() {
	isQuerying = DevMenu::shouldQuery;

	if (Input::IsKeyJustPressed(GLFW_KEY_F3) and Settings::GetBool("DevMenu")) {
		// Open the DevMenu if F3 is pressed
		DevMenu::SetVisible(not DevMenu::IsVisible());
	}

	frameStart = std::chrono::high_resolution_clock::now();
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
}

void Application::MainLoopEnd() {
	if (Settings::GetInt("TargetFramerate") != 0) {
		float targetMs = 1000.0f / Settings::GetFloat("TargetFramerate");

		// Use a busy wait approach for precision
		// Not great for cpu usage but its better then oversleeping
		while (true) {
			auto now = std::chrono::high_resolution_clock::now();
			float ms = std::chrono::duration<float, std::milli>(now - frameStart).count();
			if (ms >= targetMs)
				break;
		}
	}
}

#pragma endregion