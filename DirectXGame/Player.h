#pragma once
#include <KamataEngine.h>
#include <3d/Model.h>
#include <3d/WorldTransform.h>
using namespace KamataEngine;
class Player {
private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
	Camera* camera_ = nullptr;

public:
	void Initialize(Model*model,uint32_t textureHandle,Camera*camera);

	void Update();

	void Draw();
};
