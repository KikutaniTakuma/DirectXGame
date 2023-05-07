#include "ImGuiManager.h"
#include "Enemy.h"
#include <cassert>
#include "Vector3.h"
#include <algorithm>

void Enemy::Initialize(std::shared_ptr<Model> model, uint32_t textureHandle) {
	assert(model);

	textureHandle_ = textureHandle;
	model_ = model;
	worldTransform_.Initialize();
	input_ = Input::GetInstance();
	bullets.resize(0);

	worldTransform_.translation_.y = 10.0f;
	worldTransform_.translation_.z = 100.0f;
}

void Enemy::Update() {
	Vector3 move = { 0.0f,0.0f,0.0f };

	const float kPlayerSpeed = 0.5f;

	move.z = -kPlayerSpeed;

	worldTransform_.translation_ += move;

	worldTransform_.matWorld_ = MakeMatrixAffin(Vector3(1.0f, 1.0f, 1.0f), worldTransform_.rotation_, worldTransform_.translation_);

	worldTransform_.TransferMatrix();

	ImGui::Begin("Player Position");
	ImGui::Text("x : %.02f, y : %.02f, z : %.02f", worldTransform_.translation_.x, worldTransform_.translation_.y, worldTransform_.translation_.z);
	ImGui::End();
}

void Enemy::Draw(ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);

	for (auto& bullet : bullets) {
		bullet->Draw(viewProjection);
	}
}