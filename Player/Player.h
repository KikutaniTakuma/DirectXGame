#pragma once

#include <Input.h>
#include "Bullet/Bullet.h"
#include <list>
#include "Object/Object.h"

class Player final : public Object{ 
public:
	void Initialize(std::shared_ptr<Model> model, uint32_t textureHandle);

	void Update();

	void Draw(const ViewProjection& viewProjection);

private:
	void Attack();

private:
	Input* input_ = nullptr;

	std::list<std::unique_ptr<Bullet>> bullets;

	float rotateY_;

public:
	const std::list<std::unique_ptr<Bullet>>& getBulletList() const { return bullets; }
};