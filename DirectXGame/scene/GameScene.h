#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <memory>
#include "DebugCamera.h"
#include "RailCamera/RailCamera.h"

#include "Player/Player.h"
#include "Enemy/Enemy.h"
#include "Skydome/Skydome.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private: 
	// メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
	uint32_t playerTextureHandle_;

	uint32_t enemyTextureHandle_;

	std::shared_ptr<Model> model_;

	std::weak_ptr<Model> modelObserver;

	WorldTransform worldTransform_;

	ViewProjection viewProjection_;

	std::unique_ptr<Player> player_;

	std::unique_ptr<Enemy> enemy_;

	std::unique_ptr<DebugCamera> debugCamera_;

	std::unique_ptr<Skydome> skydome_;

	std::unique_ptr<RailCamera> railCamera_;

	// debugCamera有効化フラグ
	bool isDebugCameraActive_ = false;

	// enemyBullet
	std::list<std::unique_ptr<Bullet>> enemyBullets;

private:
	void Collision();

public:
	void AddBullet(Bullet* bullet);
};
