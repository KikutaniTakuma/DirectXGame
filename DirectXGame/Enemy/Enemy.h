#pragma once

#include <Input.h>
#include "Bullet/Bullet.h"
#include <list>
#include "Object/Object.h"

class GameScene;

class Enemy : public Object {
private:
	enum class Phase {
		Approch,
		Leave
	};

public:
	void Initialize(const Vector3& pos, std::shared_ptr<Model> model, uint32_t textureHandle);

	void Update();

	void Draw(const ViewProjection& viewProjection);

private:
	void Attack();

private:
	uint32_t bulletTextureHandle_;

	Input* input_ = nullptr;

	Phase phase_;

	std::chrono::steady_clock::time_point start_;

	static const std::chrono::milliseconds kLifeTime_;

	class Player* player_;

	GameScene* gameScene_ = nullptr;

	std::chrono::milliseconds waitTime_;
	bool isWait;

public:
	inline void SetWaitTime(int32_t waitTime) {
		if (waitTime != 0) {
			isWait = true;
		}
		start_ = std::chrono::steady_clock::now();
		waitTime_ = std::chrono::milliseconds(waitTime);
	}

public:
	void setPlayerPtr(Player* player);

public:
	inline void setGameScene(GameScene* gameScene) {
		gameScene_ = gameScene;
	}
};