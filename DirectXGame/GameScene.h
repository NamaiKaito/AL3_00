#pragma once
#include "KamataEngine.h"
#include "Player.h"
using namespace KamataEngine;

//ゲームシーン
class GameScene 
{
private:
	uint32_t textureHandle_ = 0;
	Model* model_ = nullptr;
	WorldTransform worldTransform_;
	Camera camera_;
	Player* player_ = nullptr;

public:
	~GameScene();
	//初期化
	void Initialize();
	//更新
	void Update();
	//描画
	void Draw();
};
