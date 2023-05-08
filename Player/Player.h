#pragma once

#include "WorldTransform.h"
#include "Model.h"
#include <memory>
#include <Input.h>
#include "Bullet/Bullet.h"
#include <list>

class Player {
public:
	void Initialize(std::shared_ptr<Model> model, uint32_t textureHandle);

	void Update();

	void Draw(ViewProjection& viewProjection);

private:
	void Attack();

private:
	uint32_t textureHandle_;

	std::shared_ptr<Model> model_;

	WorldTransform worldTransform_;

	Input* input_ = nullptr;

	std::list<std::unique_ptr<Bullet>> bullets;

	float rotateY_;

public:
	inline Vector3 getPos() const { return worldTransform_.translation_; }
};