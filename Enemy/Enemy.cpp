#include "Enemy.h"
#include <cassert>
#include "Vector3.h"
#include <algorithm>
#include <numbers>

void Enemy::Initialize(std::shared_ptr<Model> model, uint32_t textureHandle) {
	assert(model);

	textureHandle_ = textureHandle;
	model_ = model;
	worldTransform_.Initialize();
	input_ = Input::GetInstance();
	bullets.resize(0);

	phase_ = Enemy::Phase::Approch;

	worldTransform_.translation_.y = 2.0f;
	worldTransform_.translation_.z = 100.0f;
}

void Enemy::Update() {
	Vector3 move = { 0.0f,0.0f,0.0f };
	const float kEnemyApprochSpeed = 0.5f;
	const float kEnemyLeaveSpeed = kEnemyApprochSpeed / std::numbers::sqrt2_v<float>;

	switch (phase_)
	{
	case Enemy::Phase::Approch:
	default:

		move.z = -kEnemyApprochSpeed;

		worldTransform_.translation_ += move;

		if (worldTransform_.translation_.z < 0.0f) {
			phase_ = Enemy::Phase::Leave;
		}


		break;
	case Enemy::Phase::Leave:
		move.z = -kEnemyLeaveSpeed;
		move.x = -kEnemyLeaveSpeed;

		worldTransform_.translation_ += move;

		break;
	}

	worldTransform_.matWorld_ = MakeMatrixAffin(Vector3(1.0f, 1.0f, 1.0f), worldTransform_.rotation_, worldTransform_.translation_);

	worldTransform_.TransferMatrix();
}

void Enemy::Draw(ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);

	for (auto& bullet : bullets) {
		bullet->Draw(viewProjection);
	}
}