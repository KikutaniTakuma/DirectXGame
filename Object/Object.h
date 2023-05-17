#pragma once

#include "WorldTransform.h"
#include "Model.h"
#include "Vector3.h"
#include <memory>

class Object {
public:
	inline Object() :
		isDead_(true),
		textureHandle_(0u),
		model_(),
		worldTransform_(),
		isCollision_(false)
	{}

public:
	inline const Vector3& getPos() const { return worldTransform_.translation_; }

	inline const Vector3& getSize() const { return worldTransform_.scale_; }

	inline bool getIsDead() const { return isDead_; }

	virtual inline void OnCollision() {
		isCollision_ = true;
	}

protected:
	bool isCollision_;

	bool isDead_;

	uint32_t textureHandle_;

	std::shared_ptr<Model> model_;

	WorldTransform worldTransform_;
};