#pragma once

#include "WorldTransform.h"
#include "Model.h"
#include <memory>
#include <Input.h>

class Player {
public:
	void Initialize(std::shared_ptr<Model> model, uint32_t textureHandle);

	void Update();

	void Draw(ViewProjection& viewProjection);


private:
	uint32_t textureHandle_;

	std::shared_ptr<Model> model_;

	WorldTransform worldTransform_;

	Input* input_ = nullptr;
};