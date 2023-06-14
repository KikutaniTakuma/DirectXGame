#pragma once
#include "WorldTransform.h"
#include "ViewProjection.h"

class RailCamera {
public:
	void Initalize(const Vector3& translation, const Vector3& rotate);

	void Update();

	inline const WorldTransform& getWorldTransform() const {
		return worldTransform_;
	}

	inline const ViewProjection& getViewProjection() const {
		return viewProjection_;
	}

private:
	WorldTransform worldTransform_;

	ViewProjection viewProjection_;
};