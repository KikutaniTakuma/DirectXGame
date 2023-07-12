#include "ImGuiManager.h"
#include "Player.h"
#include <cassert>
#include "Vector3.h"
#include <algorithm>
#include <numbers>

void Player::Initialize(std::shared_ptr<Model> model, uint32_t textureHandle, const Vector3& pos) {
	assert(model);

	textureHandle_ = textureHandle;
	model_ = model;
	worldTransform_.Initialize();
	worldTransform_.translation_ = pos;
	input_ = Input::GetInstance();
	bullets.resize(0);

	rotateY_ = std::numbers::pi_v<float> / 60.0f;

	worldTransform3DReticle_.Initialize();

	uint32_t textureReticle = TextureManager::Load("./Resources/Nerai.png");

	sprite2DReticle_.reset(Sprite::Create(textureReticle, Vector2(1280.0f * 0.5f, 720.0f * 0.5f), Vector4(1.0f,1.0f,1.0f,1.0f), { 0.5f,0.5f }));


}

void Player::Update() { 
	Vector3 move = { 0.0f,0.0f,0.0f };

	const float kPlayerSpeed = 0.2f;

	if (input_->PushKey(DIK_LEFT)) {
		move.x -= kPlayerSpeed;
	}
	if (input_->PushKey(DIK_RIGHT)) {
		move.x += kPlayerSpeed;
	}
	if (input_->PushKey(DIK_UP)) {
		move.y += kPlayerSpeed;
	}
	if (input_->PushKey(DIK_DOWN)) {
		move.y -= kPlayerSpeed;
	}

	if (input_->PushKey(DIK_D)) {
		worldTransform_.rotation_.y += rotateY_;
	}
	if (input_->PushKey(DIK_A)) {
		worldTransform_.rotation_.y -= rotateY_;
	}

	const float kMoveLimitX = 34.0f;
	const float kMoveLimitY = 19.0f;

	worldTransform_.translation_ += move;

	worldTransform_.translation_.x = std::clamp(worldTransform_.translation_.x, -kMoveLimitX, kMoveLimitX);
	worldTransform_.translation_.y = std::clamp(worldTransform_.translation_.y, -kMoveLimitY, kMoveLimitY);
	worldTransform_.matWorld_.Affin(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

	static constexpr float kDistancePlayerTo3DReticle = 50.0f;
	Vector3 offset = { 0.0f,0.0f,kDistancePlayerTo3DReticle };

	worldTransform3DReticle_.translation_ = worldTransform_.translation_ + offset;

	Attack();

	ImGui::Begin("Player Position");
	ImGui::Text("x : %.02f, y : %.02f, z : %.02f", worldTransform_.translation_.x, worldTransform_.translation_.y, worldTransform_.translation_.z);
	ImGui::End();

	worldTransform3DReticle_.UpdateMatrix();
	worldTransform_.UpdateMatrix();
}

void Player::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);

	for (auto& bullet : bullets) {
		bullet->Draw(viewProjection);
	}

	Vector3 reticlePostision = worldTransform3DReticle_.translation_;

	reticlePostision *= viewProjection.matView * viewProjection.matProjection *
		MakeMatrixViewPort(0.0f, 0.0f, static_cast<float>(WinApp::kWindowWidth), static_cast<float>(WinApp::kWindowHeight), 0.0f, 1.0f);
	sprite2DReticle_->SetPosition({ reticlePostision.x, reticlePostision.y });
}

void Player::DrawUI() {
	sprite2DReticle_->Draw();
}

void Player::Attack() {
	if (input_->TriggerKey(DIK_SPACE)) {
		bullets.push_back(std::make_unique<Bullet>());

		static constexpr float kBulletSpd = 1.0f;
		Vector3 velocity(0.0f, 0.0f, kBulletSpd);

		velocity = worldTransform3DReticle_.translation_ - worldTransform_.translation_;
		velocity = velocity.Normalize() * kBulletSpd;

		velocity *= MakeMatrixRotateY(worldTransform_.parent_->rotation_.y);


		(*bullets.rbegin())->Initialize(model_, worldTransform_.translation_ * worldTransform_.parent_->matWorld_, velocity);
	}


	for (auto& bullet : bullets) {
		bullet->Update();
	}

	bullets.remove_if([](const std::unique_ptr<Bullet>& bullet) { 
		return bullet->getIsDead();
	});
}