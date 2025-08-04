#include "DeathParticles.h"
#include "KamataEngine.h"
#include "MyMath.h"
#include <cassert>

using namespace KamataEngine;

void DeathParticles::Initialize(Model* model, Camera* camera, const Vector3& position) { 
	for (WorldTransform& worldTransform : worldTransforms_) {
		worldTransform.Initialize();
		worldTransform.translation_ = position;
	}
}

void DeathParticles::Update() {
	if (deathParticles_ != nullptr) {
		deathParticles_->Update();
	}

	for (WorldTransform& worldTransform : worldTransforms_) {
		worldTransform.UpdateMatrix();
		worldTransform.TransferMatrix();
	}
}

void DeathParticles::Draw() {
	if (deathParticles_ != nullptr) {
		deathParticles_->Draw();
	}

	for (WorldTransform& worldTransform : worldTransforms_) {
		model_->Draw(worldTransform, *camera_);
	}
}

// 初期化
deathParticles_ = new DeathParticles;
deathParticles_->Initialize(model_, &camera_, position);

// 毎フレーム
if (deathParticles_) {
	deathParticles_->Update();
	deathParticles_->Draw();
}

// 解放（終了時 or 寿命で）
if (deathParticles_) {
	delete deathParticles_;
	deathParticles_ = nullptr;
}
