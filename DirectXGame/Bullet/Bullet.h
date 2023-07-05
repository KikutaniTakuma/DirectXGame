#pragma once

#include <chrono>
#include "Object/Object.h"

class Bullet : public Object
{
public:
	void Initialize(std::shared_ptr<Model> model, const Vector3& pos, const Vector3& velocity);
	void Initialize(std::shared_ptr<Model> model, const Vector3& pos, const Vector3& velocity, uint32_t textureHandle);

	void Update();

	void Draw(const ViewProjection& viewProjection);

private:
	Vector3 velocity_;

	std::chrono::steady_clock::time_point start_;

	static const std::chrono::milliseconds kLifeTime_;

public:
	inline void OnCollision() override {
		isCollision_ = true;
		isDead_ = true;
	}
};