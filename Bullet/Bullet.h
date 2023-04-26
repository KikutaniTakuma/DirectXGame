#pragma once

#include "WorldTransform.h"
#include "Model.h"
#include <memory>

class Bullet
{
public:
	void Initialize(std::shared_ptr<Model> model, Vector3 pos);

	void Update();

	void Draw(ViewProjection& viewProjection);

private:
	uint32_t textureHandle_;

	std::shared_ptr<Model> model_;

	WorldTransform worldTransform_;

public:
	inline Vector3 getPos() const {
		return worldTransform_.translation_;
	}
};