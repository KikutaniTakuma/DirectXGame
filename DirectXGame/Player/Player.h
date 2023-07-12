#pragma once

#include <Input.h>
#include "Bullet/Bullet.h"
#include <list>
#include "Object/Object.h"
#include "Sprite.h"

class Player final : public Object{ 
public:
	void Initialize(std::shared_ptr<Model> model, uint32_t textureHandle, const Vector3& pos);

	void Update();

	void Draw(const ViewProjection& viewProjection);

	void DrawUI();

private:
	void Attack();

private:
	Input* input_ = nullptr;

	std::list<std::unique_ptr<Bullet>> bullets;

	float rotateY_;

	WorldTransform worldTransform3DReticle_;

	std::unique_ptr<Sprite> sprite2DReticle_;

public:
	const std::list<std::unique_ptr<Bullet>>& getBulletList() const { return bullets; }

	inline void setParent(const WorldTransform* parent) {
		worldTransform_.parent_ = parent;
	}
};