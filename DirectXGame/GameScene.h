#pragma once
#include "KamataEngine.h"
#include "Player.h"
#include "Skydome.h"
#include"MapChipField.h"
#include <vector>

using namespace KamataEngine;

// ゲームシーン
class GameScene {
public:
	// 初期化
	void Initialize();
	// 更新
	void Update();
	// 　描画
	void Draw();
	uint32_t textureHandle_ = 0;
	Model* model_ = nullptr;
	Model* modelBlock_ = Model::CreateFromOBJ("block");
	Model* modelSkyDome_ = nullptr;
	WorldTransform worldTransform_;
	Camera camera_;
	MapChipField* mapChipField_;

	Player* player_ = nullptr;
	SkyDome* skyDome_ = nullptr;
	bool isDebugCameraActive_ = false;
	DebugCamera* debugCamera_ = nullptr;
	
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	std::vector<std::vector<WorldTransform*>> worldTransformBlocks_;
	void GenerateBlock();
	// デストラクタ
	~GameScene();
};
