#pragma once

#include <Input.h>
#include "Bullet/Bullet.h"
#include <list>
#include "Object/Object.h"

class Enemy : public Object {
private:
	enum class Phase {
		Approch,
		Leave
	};

public:
	void Initialize(std::shared_ptr<Model> model, uint32_t textureHandle);

	void Update();

	void Draw(const ViewProjection& viewProjection);

private:
	void Attack();

private:
	uint32_t bulletTextureHandle_;

	Input* input_ = nullptr;

	std::list<std::unique_ptr<Bullet>> bullets;

	Phase phase_;

	std::chrono::steady_clock::time_point start_;

	static const std::chrono::milliseconds kLifeTime_;

	class Player* player_;

public:
	void setPlayerPtr(Player* player);

public:
	const std::list<std::unique_ptr<Bullet>>& getBulletList() const { return bullets; }


};