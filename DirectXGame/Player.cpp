#include "Player.h"
using namespace KamataEngine;

void Player::Initialize(Model* model, uint32_t texturHandle, Camera* camera) {

	assert(model);
	model_ = model;
	texturHandle_ = texturHandle;
	camera_ = camera;

	worldTransform_.Initialize();
}

void Player::Update() {
	worldTransform_.TransferMatrix();
}

void Player::Draw() { model_->Draw(worldTransform_, *camera_, texturHandle_); }
