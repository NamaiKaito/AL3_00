#pragma once
#include "KamataEngine.h"
#include<array>

using namespace KamataEngine;

class Player;

class DeathParticles {
public:
	void Initialize(Model* model, Camera* camera, const Vector3& position);
	void Update();
	void Draw();

	// モデルのポインタ
	Model* model_ = nullptr;

	// カメラのポインタ
	Camera* camera_ = nullptr;

	//
	static inline const uint32_t kNumParticles = 8;

	std::array<WorldTransform, kNumParticles> worldTransforms_;
};
