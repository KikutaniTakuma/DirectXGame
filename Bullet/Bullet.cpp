#include "Bullet.h"
#include <cassert>
#include <algorithm>
#include "Vector3.h"

const std::chrono::milliseconds Bullet::kLifeTime_ = std::chrono::milliseconds(5000);

void Bullet::Initialize(std::shared_ptr<Model> model, const Vector3& pos, const Vector3& velocity) {
	assert(model);

	textureHandle_ = TextureManager::Load("./Resources/Bullet.png");
	model_ = model;
	worldTransform_.Initialize();
	worldTransform_.translation_ = pos;
	velocity_ = velocity;

	isDead_ = false;
	start_ = std::chrono::steady_clock::now();
}

void Bullet::Initialize(std::shared_ptr<Model> model, const Vector3& pos, const Vector3& velocity, uint32_t textureHandle) {
	assert(model);

	textureHandle_ = textureHandle;
	model_ = model;
	worldTransform_.Initialize();
	worldTransform_.translation_ = pos;
	velocity_ = velocity;

	isDead_ = false;
	start_ = std::chrono::steady_clock::now();
}

void Bullet::Update() {
	auto end = std::chrono::steady_clock::now();

	if (std::chrono::duration_cast<std::chrono::milliseconds>(end - start_) >= kLifeTime_) {
		isDead_ = true;
	}

	if (!isDead_) {
		worldTransform_.translation_ += velocity_;

		worldTransform_.matWorld_ =
		    MakeMatrixAffin(Vector3(1.0f, 1.0f, 1.0f), Vector3(), worldTransform_.translation_);

		worldTransform_.TransferMatrix();
	}
}

void Bullet::Draw(const ViewProjection& viewProjection) {
	if (!isDead_) {
		model_->Draw(worldTransform_, viewProjection, textureHandle_);
	}
}