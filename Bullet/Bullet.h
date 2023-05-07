#pragma once

#include "WorldTransform.h"
#include "Model.h"
#include <memory>
#include <chrono>

class Bullet
{
public:
	void Initialize(std::shared_ptr<Model> model, const Vector3& pos, const Vector3& velocity);

	void Update();

	void Draw(ViewProjection& viewProjection);

private:
	uint32_t textureHandle_;

	std::shared_ptr<Model> model_;

	WorldTransform worldTransform_;

	Vector3 velocity_;

	bool isDead_;

	std::chrono::steady_clock::time_point start_;

	static const std::chrono::milliseconds kLifeTime;

public:
	inline Vector3 getPos() const {
		return worldTransform_.translation_;
	}

	
	inline bool getIsDead() const { return isDead_; }
};