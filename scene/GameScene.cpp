#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "PrimitiveDrawer.h"
#include "AxisIndicator.h"

GameScene::GameScene() : 
	textureHandle_(0), 
	soundDataHandle_(0),
	voiceHandle_(0), 
	inputFloat3() 
{}

GameScene::~GameScene() {}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	textureHandle_ = TextureManager::Load("./Resources/mario.jpg");
	sprite_.reset(Sprite::Create(textureHandle_, {100, 50}));

	worldTransform_.Initialize();
	viewProjection_.Initialize();

	soundDataHandle_ = audio_->LoadWave("./Resources/fanfare.wav");

	 voiceHandle_ = audio_->PlayWave(soundDataHandle_, true);

	 PrimitiveDrawer::GetInstance()->SetViewProjection(&viewProjection_);

	 debugCamera_ = std::make_unique<DebugCamera>(1280, 720);

	 AxisIndicator::GetInstance()->SetVisible(true);

	 AxisIndicator::GetInstance()->SetTargetViewProjection(&debugCamera_->GetViewProjection());
}

void GameScene::Update()
{
	// スプライトの今の座標を表示
	Vector2 position = sprite_->GetPosition();
	// 座標を{ 2, 1 }移動
	position.x += 2.0f;
	position.y += 1.0f;
	// 移動した座標をスプライトに反映
	sprite_->SetPosition(position);

	model.reset(Model::Create());

	if (input_->TriggerKey(DIK_SPACE)) {
		audio_->StopWave(voiceHandle_);
	}

	ImGui::Begin("Debug1");
	ImGui::InputFloat3("InputFloat3", inputFloat3.data());
	ImGui::SliderFloat3("SliderFloat3", inputFloat3.data(), 0.0f, 1.0f);
	ImGui::End();

	ImGui::ShowDemoWindow();

	debugCamera_->Update();
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
	model->Draw(worldTransform_, debugCamera_->GetViewProjection(), textureHandle_);

	for (int y = -360; y < 360; y+=2) {
		PrimitiveDrawer::GetInstance()->DrawLine3d(
		    {-640.0f, float(y), 0.0f}, {640.0f, float(y), 0.0f}, {1.0f, 0.0f, 0.0f, 1.0f});
	}
	for (int x = -640; x < 640; x+=2) {
		PrimitiveDrawer::GetInstance()->DrawLine3d(
		    {(float)x, -360.0f, 0.0f}, {(float)x, 360.0f, 0.0f}, {0.0f, 1.0f, 0.0f, 1.0f});
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
	sprite_->Draw();

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
