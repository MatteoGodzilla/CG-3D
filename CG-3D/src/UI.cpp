#include "UI.hpp"

UI::UI(GLFWwindow* window) {
	//Init ImGui
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
}

void UI::hierarchy(double deltaTime, Object* root, LightManager* lightMan) {
	//Begin ImGui Frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGui::SetNextWindowPos(ImVec2(0,0), ImGuiCond_Always);
	ImVec2 size = ImGui::GetMainViewport()->Size;
	size.x /= 4;
	ImGui::SetNextWindowSize(size, ImGuiCond_Once);
	ImGui::Begin("Hierarchy", nullptr);
	hierarchyObjectUI(root, true);
	hierarchyLightUI(lightMan);
	ImGui::End();

	ImGui::ShowDemoWindow();

	//Render ImGui Frame
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UI::hierarchyObjectUI(Object* obj, bool isRoot){
	ImGui::PushID(obj);
	if (ImGui::TreeNode(obj->name.c_str())) {
		if (!isRoot) {
			if (ImGui::TreeNode("Transform")) {
				Transform t = obj->getTransform();
				float worldPositionAsArray[] = { t.worldPosition.x, t.worldPosition.y, t.worldPosition.z };
				float worldScaleAsArray[] = { t.worldScale.x, t.worldScale.y, t.worldScale.z };
				bool modifiedTransform = false;
				if (ImGui::DragFloat3("World Position", worldPositionAsArray, 0.1, -10, 10)) {
					t.worldPosition = glm::vec3(worldPositionAsArray[0], worldPositionAsArray[1], worldPositionAsArray[2]);
					modifiedTransform = true;
				}
				if (ImGui::DragFloat3("World Scale", worldScaleAsArray, 0.1, -10, 10)) {
					t.worldScale = glm::vec3(worldScaleAsArray[0], worldScaleAsArray[1], worldScaleAsArray[2]);
					modifiedTransform = true;
				}
				if (modifiedTransform) {
					obj->setTransformAll(t);
					obj->updateCollisionBox();
				}
				ImGui::TreePop();
			}
			if (ImGui::TreeNode("Material")) {
				Material m = obj->getMaterial();
				float baseColorAsArray[] = {m.baseColor.r, m.baseColor.g, m.baseColor.b, m.baseColor.a};
				float ambientColorAsArray[] = {m.ambientColor.r, m.ambientColor.g, m.ambientColor.b, m.ambientColor.a};
				float diffuseColorAsArray[] = {m.diffuseColor.r, m.diffuseColor.g, m.diffuseColor.b, m.diffuseColor.a};
				float specularColorAsArray[] = { m.specularColor.r, m.specularColor.g, m.specularColor.b, m.specularColor.a };
				bool modifiedMaterial = false;
				if (ImGui::ColorEdit4("Base color", baseColorAsArray, 0)) {
					m.baseColor = glm::vec4(baseColorAsArray[0], baseColorAsArray[1], baseColorAsArray[2], baseColorAsArray[3]);
					modifiedMaterial = true;
				}
				if (ImGui::ColorEdit4("Ambient color", ambientColorAsArray, 0)) {
					m.ambientColor = glm::vec4(ambientColorAsArray[0], ambientColorAsArray[1], ambientColorAsArray[2], ambientColorAsArray[3]);
					modifiedMaterial = true;
				}
				if (ImGui::ColorEdit4("Diffuse color", diffuseColorAsArray, 0)) {
					m.diffuseColor = glm::vec4(diffuseColorAsArray[0], diffuseColorAsArray[1], diffuseColorAsArray[2], diffuseColorAsArray[3]);
					modifiedMaterial = true;
				}
				if (ImGui::ColorEdit4("Specular color", specularColorAsArray, 0)) {
					m.specularColor = glm::vec4(specularColorAsArray[0], specularColorAsArray[1], specularColorAsArray[2], specularColorAsArray[3]);
					modifiedMaterial = true;
				}
				
				if (ImGui::BeginCombo("Material Type", MaterialTypeToCString(m.type))) {
					for (int i = 0; i < Material::MAT_TYPE_COUNT; i++) {
						bool isSelected = (i == m.type);
						if (ImGui::Selectable(MaterialTypeToCString((Material::MaterialType)i), &isSelected)) {
							m.type = ((Material::MaterialType)i);
							modifiedMaterial = true;
						}
					}
					ImGui::EndCombo();
				}

				if (m.texture != nullptr) {
					if (ImGui::TreeNode("Texture")) {
						ImGui::Image(m.texture->texId, ImVec2(60, 60));
						ImGui::TreePop();
					}
				}

				if (modifiedMaterial) {
					obj->setMaterialAll(m);
				}

				ImGui::TreePop();
			}
		}

		if (ImGui::TreeNode("Children")) {
			for (auto* child : obj->getChildren()) {
				hierarchyObjectUI(child, false);
			}
			ImGui::TreePop();
		}
		ImGui::TreePop();
	}
	ImGui::PopID();
}

const char* UI::MaterialTypeToCString(Material::MaterialType type) {
	switch (type) {
	case Material::UNLIT: return "Unlit";
	case Material::UNLIT_TEXTURE: return "Unlit texture";
	case Material::UNLIT_CUBEMAP: return "Unlit cubemap";
	case Material::GOURAD: return "Gourad";
	case Material::PHONG: return "Phong";
	case Material::BLINN_PHONG: return "Blinn-Phong";
	default: return "<INVALID>";
	}
}

void UI::hierarchyLightUI(LightManager* lightMan) {
	for (int i = 0; i < LIGHT_COUNT; i++) {
		ImGui::PushID(lightMan + i);
		std::string name = "Light ";
		name.append(std::to_string(i));
		if (ImGui::TreeNode(name.c_str())) {
			PointLight light = lightMan->getLight(i);
			float positionAsArray[] = { light.position.x, light.position.y, light.position.z };
			float colorAsArray[] = { light.color.r, light.color.g, light.color.b, light.color.a };
			bool modified = false;
			if (ImGui::DragFloat3("Position", positionAsArray, 0.1)) {
				light.position = glm::vec3(positionAsArray[0], positionAsArray[1], positionAsArray[2]);
				modified = true;
			}

			if (ImGui::ColorEdit4("Color", colorAsArray)) {
				light.color = glm::vec4(colorAsArray[0], colorAsArray[1], colorAsArray[2], colorAsArray[3]);
				modified = true;
			}
			
			if (modified) {
				lightMan->setLight(i, light);
			}

			ImGui::TreePop();
		}
		ImGui::PopID();
	}
}