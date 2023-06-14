#include "Skydome.h"

void Skydome::Initalize() {
	model_.reset(Model::CreateFromOBJ("skydome", true));
	worldTransform_.Initialize();
	worldTransform_.scale_ = { 100.0f,100.0f,100.0f };
}

void Skydome::Update() {
	worldTransform_.matWorld_ = MakeMatrixAffin(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	worldTransform_.TransferMatrix();
}

void Skydome::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection);
}