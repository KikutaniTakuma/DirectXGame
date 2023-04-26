#include "Bullet.h"
#include <cassert>
#include <algorithm>
#include "Vector3.h"

void Bullet::Initialize(std::shared_ptr<Model> model, Vector3 pos) {
	assert(model);

	textureHandle_ = TextureManager::Load("./Resources/Poop.png");
	model_ = model;
	worldTransform_.Initialize();
	worldTransform_.translation_ = pos;
}

void Bullet::Update() {
	Vector3 move = { 0.0f,0.0f,0.0f };

	const float kPlayerSpeed = 0.2f;

	move.z = kPlayerSpeed;

	const float kMoveLimitX = 34.0f;
	const float kMoveLimitY = 19.0f;

	worldTransform_.translation_ += move;

	worldTransform_.translation_.x = std::clamp(worldTransform_.translation_.x, -kMoveLimitX, kMoveLimitX);
	worldTransform_.translation_.y = std::clamp(worldTransform_.translation_.y, -kMoveLimitY, kMoveLimitY);

	worldTransform_.matWorld_ = MakeMatrixAffin(Vector3(1.0f, 1.0f, 1.0f), Vector3(), worldTransform_.translation_);

	worldTransform_.TransferMatrix();
}

void Bullet::Draw(ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}