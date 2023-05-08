#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "AxisIndicator.h"

GameScene::GameScene() :
	playerTextureHandle_(0u),
	enemyTextureHandle_(0)
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

	player_ = std::make_unique<Player>();

	player_->Initialize(model_, playerTextureHandle_);

	enemy_ = std::make_unique<Enemy>();

	enemy_->Initialize(model_, enemyTextureHandle_);

	enemy_->setPlayerPtr(player_.get());

	debugCamera_ = std::make_unique<DebugCamera>(1280,720);
}

void GameScene::Update() {
#ifdef _DEBUG
	if (input_->TriggerKey(DIK_F3)) {
		if (!isDebugCameraActive_) {
			isDebugCameraActive_ = true;
			AxisIndicator::GetInstance()->SetVisible(true);
		}
		else if (isDebugCameraActive_) {
			isDebugCameraActive_ = false;
			AxisIndicator::GetInstance()->SetVisible(false);
		}
	}

#endif

	player_->Update();

	enemy_->Update();

	if (debugCamera_) {
		debugCamera_->Update();
		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;
		viewProjection_.TransferMatrix();

		AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);
	}
	else {
		viewProjection_.UpdateMatrix();
	}
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
	player_->Draw(viewProjection_);

	enemy_->Draw(viewProjection_);


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
