#include "UI.hpp"

UI::UI(GLFWwindow* window) {
	//Init ImGui
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	//activeBoidGraph = NULL;
	//activeBoidCount = 0;
	//flockCenter = { 0.0, 0.0 };
	//flockSpeed = { 0.0, 0.0 };
	//playerPos = { 0.0, 0.0 };
	//playerSpeed = { 0.0, 0.0 };
}

//This is required by ImGui in order to convert any possible data source into a float value, 
//so that it can be used by ImGui to create the plot 
float plotFunc(void* data, int index) {
	std::deque<size_t>* dataAsDeque = (std::deque<size_t>*)data;
	return (float)dataAsDeque->at(index);
}

void UI::render(double deltaTime) {
	//Begin ImGui Frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGui::ShowDemoWindow();

	//Options window
	/*
	
	ImGui::Begin("Options", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::SliderFloat("Camera Size", &orthoSize, 10, 100);
	ImGui::SliderFloat("Max Player Speed", &maxPlayerSpeed, 0, 5);
	ImGui::End();

	ImGui::Begin("Simulation Parameters", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::Checkbox("Enable collisions player-active", &simulationParams.collisionsPlayerActive);
	ImGui::Checkbox("Enable collisions active-active", &simulationParams.collisionsActiveActive);
	ImGui::Checkbox("Enable collisions active-inactive", &simulationParams.collisionsActiveInactive);

	ImGui::NewLine();
	ImGui::SliderFloat("Player Collision radius", &simulationParams.playerSize, 0, 16);
	ImGui::SliderFloat("Boid Collision radius", &simulationParams.boidSize, 0, 16);
	ImGui::SliderFloat("Boid Avoid radius", &simulationParams.boidAvoidRadius, 0, 16);
	ImGui::SliderFloat("Player-Boid Activate radius", &simulationParams.boidActivateRadius, 0, 16);

	ImGui::NewLine();
	ImGui::SliderFloat("Rule 1 (position) strength", &simulationParams.strengthRule1, 0, 10);
	ImGui::SliderFloat("Rule 2 (avoidance) strength", &simulationParams.strengthRule2, 0, 10);
	ImGui::SliderFloat("Rule 3 (velocity) strength", &simulationParams.strengthRule3, 0, 10);
	ImGui::SliderFloat("Drag strength", &simulationParams.speedReduction, 0, 1);
	ImGui::SliderFloat("Speed Clamp", &simulationParams.speedClamp, 1, 100);
	ImGui::End();

	//Performance window
	ImGui::Begin("Performance", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::LabelText("DeltaTime | Framerate", "%f | %f", deltaTime, 1.0 / deltaTime);
	if (activeBoidGraph != NULL) {
		//This is the ugliest line of code in the entire project
		ImGui::PlotLines("Active Boid Count", plotFunc, (void*)activeBoidGraph, (int)activeBoidGraph->size(),
			0, std::to_string(activeBoidCount).c_str(), 0, FLT_MAX, ImVec2(200, 50));
	}
	ImGui::SliderInt("History Size", &historySize, 1, 1000);
	ImGui::SliderFloat("Time Between Updates", &timeBetweenUpdates, 0.1f, 10.0f);
	ImGui::End();

	//Controls overlay
	auto bottomLeft = ImGui::GetMainViewport()->Size;
	bottomLeft.x = 0;
	ImGui::SetNextWindowPos(bottomLeft, ImGuiCond_Always, ImVec2(0, 1));
	ImGui::Begin("Controls", NULL,
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_AlwaysAutoResize |
		ImGuiWindowFlags_NoBackground |
		ImGuiWindowFlags_NoTitleBar |
		ImGuiWindowFlags_NoMove
	);
	ImGui::Text("Moving mouse with Left button: turn the player in the direction of the mouse");
	ImGui::Text("Spacebar: boost player in the pointing direction");
	ImGui::Text("CTRL: slow down player");
	ImGui::End();

	//Debug Overlay
	auto bottomRight = ImGui::GetMainViewport()->Size;
	ImGui::SetNextWindowPos(bottomRight, ImGuiCond_Always, ImVec2(1, 1));
	ImGui::Begin("Debug", NULL,
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_AlwaysAutoResize |
		ImGuiWindowFlags_NoBackground |
		ImGuiWindowFlags_NoTitleBar |
		ImGuiWindowFlags_NoMove
	);
	ImGui::LabelText("Player Position", "(%f, %f)", playerPos.x, playerPos.y);
	ImGui::LabelText("Player Speed", "(%f, %f)", playerSpeed.x, playerSpeed.y);
	ImGui::LabelText("Flock Center", "(%f, %f)", flockCenter.x, flockCenter.y);
	ImGui::LabelText("Flock speed", "(%f, %f)", flockSpeed.x, flockSpeed.y);
	ImGui::End();
	*/

	//Render ImGui Frame
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

//---GETTERS---
/*
float UI::getCameraSize() {
	return orthoSize;
}

int UI::getHistorySize() {
	return historySize;
}

double UI::getTimeBetweenUpdates() {
	return timeBetweenUpdates;
}

float UI::getMaxPlayerSpeed() {
	return maxPlayerSpeed;
}
*/