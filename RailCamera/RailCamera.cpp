#include "RailCamera/RailCamera.h"
#include "ImGuiManager.h"
#include <numbers>

void RailCamera::Initalize(const Vector3& translation, const Vector3& rotate) {
	worldTransform_.translation_ = translation;
	worldTransform_.rotation_ = rotate;
	viewProjection_.farZ = 1000.0f;
	viewProjection_.Initialize();
}

void RailCamera::Update() {
	worldTransform_.rotation_.y += std::numbers::pi_v<float> / 360.0f;

	worldTransform_.matWorld_ = MakeMatrixAffin(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

	viewProjection_.matView = MakeMatrixInverse(worldTransform_.matWorld_);

	ImGui::Begin("Camera");

	ImGui::DragFloat3("Translation", &worldTransform_.translation_.x, 0.01f);
	ImGui::DragFloat3("Rotate", &worldTransform_.rotation_.x, 0.01f);

	ImGui::End();
}