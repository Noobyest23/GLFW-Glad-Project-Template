#include "DevMenu.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl3.h"

bool DevMenu::visible = false;
RenderInfo DevMenu::lastQueryInfo;
bool DevMenu::shouldQuery = false;

void DevMenu::Draw() {
	if (!visible) return;

	ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_Always);
	ImGui::SetNextWindowBgAlpha(0.75f); // slightly transparent

	ImGui::Begin("Dev Menu", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoResize);
	ImGui::Text("F3 toggles this menu");
	ImGui::Separator();

	// Add dev options here
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	
	if (ImGui::Button("Query")) {
		shouldQuery = true;
	}

	ImGui::Separator();
	ImGui::Text("Query Info:");
	std::string text = "Triangles Drawn: " + std::to_string(lastQueryInfo.primitivesDrawn);
	ImGui::Text("%s", text.c_str());
	double gpuMs = lastQueryInfo.gpuTime / 1e6;
	ImGui::Text("GPU Time: %.3f ms", gpuMs);

	ImGui::End();
}

void DevMenu::SetVisible(bool value) {
	visible = value;
}

bool DevMenu::IsVisible() {
	return visible;
}

void DevMenu::UpdateRenderInfo(RenderInfo newInfo) {
	lastQueryInfo = newInfo;
}