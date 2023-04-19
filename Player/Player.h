#pragma once

#include "WorldTransform.h"
#include "Model.h"
#include <memory>

class Player {
public:
	void Initialize(std::shared_ptr<Model> model, uint32_t textureHandle);

	void Update();

	void Draw(ViewProjection& viewProjection);


private:
	uint32_t textureHandle_;

	std::shared_ptr<Model> model_;

	WorldTransform worldTransform_;

};