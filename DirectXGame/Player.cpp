#include "Player.h"
using namespace KamataEngine;

void Player::Initialize(Model* model, Camera* camera) {

	assert(model);
	model_ = model;
	
	camera_ = camera;

	worldTransform_.Initialize();
}

void Player::Update() {
	worldTransform_.TransferMatrix();
}

void Player::Draw() { 
	model_->Draw(worldTransform_, *camera_, textureHandle_); 
}
