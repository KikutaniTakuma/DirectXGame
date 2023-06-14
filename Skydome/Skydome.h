#pragma once
#include "WorldTransform.h"
#include "Model.h"
#include <memory>

class Skydome {
public:
	void Initalize();

	void Update();

	void Draw(const ViewProjection& viewProjection);

private:
	WorldTransform worldTransform_;

	std::unique_ptr<Model> model_;
};