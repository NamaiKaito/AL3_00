#include "GameScene.h"
#include "Player.h"
#include "Skydome.h"
#include "KamataEngine.h"
#include "MyMath.h"

using namespace KamataEngine;

void GameScene::Initialize() {

	// ファイル名を指定してテクスチャを読み込む
	//textureHandle_ = TextureManager::Load("mario.png");

	// 3Dモデルの生成
	model_ = Model::Create();

	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();

	// カメラの初期化
	camera_.Initialize();

	model_ = Model::CreateFromOBJ("player", true);

	player_ = new Player();

	modelSkyDome_ = Model::CreateFromOBJ("skyDome", true);

	// 天球の生成
	skyDome_ = new SkyDome();

	// 初期化
	skyDome_->Initialize(modelSkyDome_, &camera_);

	// デバッグカメラの生成
	debugCamera_ = new DebugCamera(1280, 720);

	modelBlock_ = Model::CreateFromOBJ("block", true);
	mapChipField_ = new MapChipField;
	mapChipField_->LoadMapChipCsv("Resources/blocks.csv");
	
	GenerateBlock();

	Vector3 playerPosition = mapChipField_->GetMapChipPositionByIndex(1, 18);
	player_->Initialize(model_, &camera_, playerPosition);

	// カメラコントローラーの生成
	cameraController_ = new CameraController();
	// 初期化
	cameraController_->Initialize();
	// 追従対象をセット
	cameraController_->SetTarget(player_);
	// リセット
	cameraController_->Reset();

	CameraController::Rect cameraArea = {12.0f, 100 - 12.0f, 6.0f, 6.0f};
	cameraController_->SetMovableArea(cameraArea);
	//	// 要素数
//	const uint32_t kNumBlockVertical = 10;
//	const uint32_t kNumBlockHorizontal = 20;
//
//	// ブロック1個分の横幅
//	const float kBlockWidth = 2.0f;
//	const float kBlockHeight = 2.0f;
//
//	// 要素数を変更する
//	worldTransformBlocks_.resize(kNumBlockVertical);
//	for (uint32_t i = 0; i < kNumBlockVertical; ++i) {
//		worldTransformBlocks_[i].resize(kNumBlockHorizontal, nullptr);
//	}
//
//
//	for (uint32_t i = 0; i < kNumBlockVertical; ++i) {
//		worldTransformBlocks_[i].resize(kNumBlockHorizontal);
//	}
//
//	// キューブの生成
//	for (uint32_t i = 0; i < kNumBlockVertical; i++) {
//
//		for (uint32_t j = 0; j < kNumBlockHorizontal; ++j) {
//
//			if (j % 2 == 0)
//				continue;
//
//			worldTransformBlocks_[i][j] = new WorldTransform();
//			worldTransformBlocks_[i][j]->Initialize();
//			worldTransformBlocks_[i][j]->translation_.x = kBlockWidth * j;
//			worldTransformBlocks_[i][j]->translation_.y = kBlockHeight * i;
//		}
//	}
}

void GameScene::Update() {

	// 自キャラの更新
	player_->Update();

	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {

		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {

			if (!worldTransformBlock) 
				continue;
			
				worldTransformBlock->matWorld_ = MakeAffineMatrix(worldTransformBlock->scale_, worldTransformBlock->rotation_, worldTransformBlock->translation_);
				worldTransformBlock->TransferMatrix();
			
		}
	}

	
	debugCamera_->Update();

#ifdef _DEBUG
	if (Input::GetInstance()->TriggerKey(DIK_O)) {

		isDebugCameraActive_ = !isDebugCameraActive_;
	}
#endif

	if (isDebugCameraActive_) {
		debugCamera_->Update();
		camera_.matView = debugCamera_->GetCamera().matView;
		camera_.matProjection = debugCamera_->GetCamera().matProjection;
		camera_.UpdateMatrix();
	} else {
		camera_.UpdateMatrix();
		camera_.matView = cameraController_->GetViewProjection().matView;
		camera_.matProjection = cameraController_->GetViewProjection().matProjection;
		// ビュープロジェクション行列の転送
		camera_.TransferMatrix();
	}
	// 追従カメラの更新
	cameraController_->Update();
}

void GameScene::Draw() {

	Model::PreDraw(dxCommon->GetCommandList());

	

	skyDome_->Draw();

	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {

		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {

			if (!worldTransformBlock)
				continue;

			modelBlock_->Draw(*worldTransformBlock, camera_);
		}
	}
player_->Draw();
	Model::PostDraw();
}
void GameScene::GenerateBlock() {
	uint32_t numBlockVertical = mapChipField_->GetNumBlockVertical();
	uint32_t numBlockHorizontal = mapChipField_->GetNumBlockHorizontal();

	worldTransformBlocks_.resize(numBlockVertical);
	for (uint32_t i = 0; i < numBlockVertical; ++i) {
		worldTransformBlocks_[i].resize(numBlockHorizontal);
	}
	for (uint32_t i = 0; i < numBlockVertical; ++i) {
		for (uint32_t j = 0; j < numBlockHorizontal; ++j) {

			if (mapChipField_->GetMapChipTypeByIndex(j, i) == MapChipType::kBlock) {

				WorldTransform* worldTransform = new WorldTransform();
				worldTransform->Initialize();
				worldTransformBlocks_[i][j] = worldTransform;
				worldTransformBlocks_[i][j]->translation_ = mapChipField_->GetMapChipPositionByIndex(j, i);
			}
		}
	}
}
GameScene::~GameScene() {
	delete model_;
	delete modelBlock_;
	delete player_;
	delete debugCamera_;
	delete modelSkyDome_;
	delete mapChipField_; 

	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {

		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {

			delete worldTransformBlock;
		}
	}

	worldTransformBlocks_.clear();
}