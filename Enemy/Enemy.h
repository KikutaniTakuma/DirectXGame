#pragma once

#include "WorldTransform.h"
#include "Model.h"
#include <memory>
#include <Input.h>
#include "Bullet/Bullet.h"
#include <list>

class Enemy {
private:
	enum class Phase {
		Approch,
		Leave
	};

public:
	void Initialize(std::shared_ptr<Model> model, uint32_t textureHandle);

	void Update();

	void Draw(ViewProjection& viewProjection);

private:
	void Attack();

private:
	uint32_t textureHandle_;

	uint32_t bulletTextureHandle_;

	std::shared_ptr<Model> model_;

	WorldTransform worldTransform_;

	Input* input_ = nullptr;

	std::list<std::unique_ptr<Bullet>> bullets;

	Phase phase_;

	std::chrono::steady_clock::time_point start_;

	static const std::chrono::milliseconds kLifeTime;
};