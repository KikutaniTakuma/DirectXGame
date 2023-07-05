#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "AxisIndicator.h"
#include <cmath>

GameScene::GameScene() :
	playerTextureHandle_(0u),
	enemyTextureHandle_(0),
	enemyBullets(0)
{}

GameScene::~GameScene() {}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	playerTextureHandle_ = TextureManager::Load("./Resources/chocoIceCream.png");

	enemyTextureHandle_ = TextureManager::Load("./Resources/Enemy.png");

	model_ .reset(Model::Create());
	modelObserver = model_;

	worldTransform_.Initialize();
	viewProjection_.Initialize();

	debugCamera_ = std::make_unique<DebugCamera>(1280,720);

	skydome_ = std::make_unique<Skydome>();
	skydome_->Initalize();

	railCamera_ = std::make_unique<RailCamera>();
	railCamera_->Initalize(viewProjection_.translation_, viewProjection_.rotation_);

	player_ = std::make_unique<Player>();

	player_->setParent(&railCamera_->getWorldTransform());

	Vector3 playerPosition(0.0f,0.0f,20.0f);
	player_->Initialize(model_, playerTextureHandle_,playerPosition);


	enemy_ = std::make_unique<Enemy>();

	enemy_->setGameScene(this);

	enemy_->Initialize(model_, enemyTextureHandle_);

	enemy_->setPlayerPtr(player_.get());
}

void GameScene::Update() {
#ifdef _DEBUG
	if (input_->TriggerKey(DIK_F3)) {
		isDebugCameraActive_ = !isDebugCameraActive_;
		AxisIndicator::GetInstance()->SetVisible(isDebugCameraActive_);
	}

#endif

	enemy_->Update();

	for (auto& i : enemyBullets) {
		i->Update();
	}
	enemyBullets.remove_if([](const std::unique_ptr<Bullet>& bullet) {
		return bullet->getIsDead();
		});

	player_->Update();

	railCamera_->Update();

	if (isDebugCameraActive_) {
		debugCamera_->Update();
		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;
		viewProjection_.TransferMatrix();

		AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);
	}
	else {
		viewProjection_.matView = railCamera_->getViewProjection().matView;
		viewProjection_.matProjection = railCamera_->getViewProjection().matProjection;
		viewProjection_.TransferMatrix();
	}

	skydome_->Update();

	//Collision();
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	skydome_->Draw(viewProjection_);
	
	player_->Draw(viewProjection_);

	enemy_->Draw(viewProjection_);

	for (auto& i : enemyBullets) {
		i->Draw(viewProjection_);
	}


	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::Collision() {
	auto CollisionFunc = [](const Vector3& pos1, const Vector3& pos2, const Vector3& size1, const Vector3& size2) {
		if ((std::powf(pos1.x - pos2.x, 2.0f) + std::powf(pos1.y - pos2.y, 2.0f) + std::powf(pos1.z - pos2.z, 2.0f)) <= std::powf(size1.x + size2.x,2.0f)) {
			return true;
		}
		return false;
	};

	if (!player_->getBulletList().empty()) {
		for (auto& playerBullet : player_->getBulletList()) {
			if (CollisionFunc(enemy_->getPos(), playerBullet->getPos(), enemy_->getSize(), playerBullet->getSize())) {
				enemy_->OnCollision();
				playerBullet->OnCollision();
			}

			for (auto& enemyBullet : enemyBullets) {
				if (CollisionFunc(enemyBullet->getPos(), playerBullet->getPos(), enemyBullet->getSize(), playerBullet->getSize())) {
					enemyBullet->OnCollision();
					playerBullet->OnCollision();
				}

				if (CollisionFunc(player_->getPos(), enemyBullet->getPos(), player_->getSize(), enemyBullet->getSize())) {
					player_->OnCollision();
					enemyBullet->OnCollision();
				}
			}
		}
	}

		for (auto& enemyBullet : enemyBullets) {
			if (CollisionFunc(player_->getPos(), enemyBullet->getPos(), player_->getSize(), enemyBullet->getSize())) {
				player_->OnCollision();
				enemyBullet->OnCollision();
			}

			for (auto& playerBullet : player_->getBulletList()) {
				if (CollisionFunc(enemyBullet->getPos(), playerBullet->getPos(), enemyBullet->getSize(), playerBullet->getSize())) {
					enemyBullet->OnCollision();
					playerBullet->OnCollision();
				}

				if (CollisionFunc(enemy_->getPos(), playerBullet->getPos(), enemy_->getSize(), playerBullet->getSize())) {
					enemy_->OnCollision();
					playerBullet->OnCollision();
				}
			}
		}
	

	if (CollisionFunc(enemy_->getPos(), player_->getPos(), enemy_->getSize(), player_->getSize())) {
		player_->OnCollision();
		enemy_->OnCollision();
	}
}

void GameScene::AddBullet(Bullet* bullet) {
	enemyBullets.push_back(std::unique_ptr<Bullet>(bullet));
}
