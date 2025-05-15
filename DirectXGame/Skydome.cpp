#include "Skydome.h"

void SkyDome::Initialize(Model* model, Camera* camera) {

	assert(model);
	model_ = model;
	camera_ = camera;

	worldTransform_.Initialize();
}

void SkyDome::Update() {}

void SkyDome::Draw() { 
	model_->Draw(worldTransform_, *camera_);
}
