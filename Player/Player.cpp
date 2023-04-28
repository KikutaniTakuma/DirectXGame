#include "ImGuiManager.h"
#include "Player.h"
#include <cassert>
#include "Vector3.h"
#include <algorithm>

void Player::Initialize(std::shared_ptr<Model> model, uint32_t textureHandle) { 
	assert(model);

	textureHandle_ = textureHandle;
	model_ = model;
	worldTransform_.Initialize();
	input_ = Input::GetInstance();
	bullets.resize(0);
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

	Attack();

	const float kMoveLimitX = 34.0f;
	const float kMoveLimitY = 19.0f;

	worldTransform_.translation_ += move;

	worldTransform_.translation_.x = std::clamp(worldTransform_.translation_.x, -kMoveLimitX, kMoveLimitX);
	worldTransform_.translation_.y = std::clamp(worldTransform_.translation_.y, -kMoveLimitY, kMoveLimitY);

	worldTransform_.matWorld_ = MakeMatrixAffin(Vector3(1.0f, 1.0f, 1.0f), Vector3(), worldTransform_.translation_);

	worldTransform_.TransferMatrix();

	ImGui::Begin("Player Position");
	ImGui::Text("x : %.02f, y : %.02f, z : %.02f", worldTransform_.translation_.x, worldTransform_.translation_.y, worldTransform_.translation_.z);
	ImGui::End();
}

void Player::Draw(ViewProjection& viewProjection) { 
	model_->Draw(worldTransform_, viewProjection, textureHandle_);

	for (auto& bullet : bullets) {
		bullet->Draw(viewProjection);
	}
}

void Player::Attack() {
	if (input_->TriggerKey(DIK_SPACE)) {
		bullets.push_back(std::make_unique<Bullet>());
		(*(bullets.rbegin()))->Initialize(model_, worldTransform_.translation_);
	}


	for (auto bullet = bullets.begin(); bullet != bullets.end(); bullet++) {
		(*bullet)->Update();
		if ((*bullet)->getPos().z >= 50.0f) {
			auto tmp = bullet;
			if (tmp == bullets.begin()) {
				tmp->reset();
				bullets.erase(tmp);
				bullet = bullets.begin();
				if (bullets.empty()) {
					break;
				}
				continue;
			}
			else {
				bullet--;
			}
			tmp->reset();
			bullets.erase(tmp);
		}
	}
}