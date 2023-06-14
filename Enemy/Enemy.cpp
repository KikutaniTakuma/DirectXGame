#include "Enemy.h"
#include <cassert>
#include "Vector3.h"
#include <algorithm>
#include <numbers>
#include "TextureManager.h"
#include "Player/Player.h"

const std::chrono::milliseconds Enemy::kLifeTime_ = std::chrono::milliseconds(2000);

void Enemy::Initialize(std::shared_ptr<Model> model, uint32_t textureHandle) {
	assert(model);

	textureHandle_ = textureHandle;
	model_ = model;
	worldTransform_.Initialize();
	input_ = Input::GetInstance();
	bullets.resize(0);

	phase_ = Enemy::Phase::Approch;

	worldTransform_.translation_.x= 2.0f;
	worldTransform_.translation_.y = 2.0f;
	worldTransform_.translation_.z = 100.0f;

	bulletTextureHandle_ = TextureManager::Load("./Resources/EnemyBullet.png");

	start_ = std::chrono::steady_clock::now();

	player_ = nullptr;
}


void Enemy::Update() {
	Vector3 move = { 0.0f,0.0f,0.0f };
	const float kEnemyApprochSpeed = 0.2f;
	const float kEnemyLeaveSpeed = kEnemyApprochSpeed / std::numbers::sqrt2_v<float>;

	switch (phase_)
	{
	case Enemy::Phase::Approch:
	default:
		Attack();

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

	for (auto& bullet : bullets) {
		bullet->Update();
	}

	bullets.remove_if([](const std::unique_ptr<Bullet>& bullet) {
		return bullet->getIsDead();
		});

	worldTransform_.UpdateMatrix();
}

void Enemy::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);

	for (auto& bullet : bullets) {
		bullet->Draw(viewProjection);
	}
}

void Enemy::Attack() {
	auto end = std::chrono::steady_clock::now();

	if (std::chrono::duration_cast<std::chrono::milliseconds>(end - start_) >= kLifeTime_) {
		start_ = std::chrono::steady_clock::now();
		bullets.push_back(std::make_unique<Bullet>());

		const float kBulletSpd = 0.5f;
		Vector3 velocity = (player_->getPos() - worldTransform_.translation_).Normalize() * kBulletSpd;

		(*bullets.rbegin())->Initialize(model_, worldTransform_.translation_, velocity, bulletTextureHandle_);
	}
}

void Enemy::setPlayerPtr(Player* player) {
	player_ = player;
}