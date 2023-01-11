#include "Map.h"

void Map::Initialize(Model* model, uint32_t textureHandle) {
	//引数として受け取ったデータをメンバ変数に記録する
	BlockSize = 32;
	block = textureHandle;
	model_ = model;

	//カメラの画角の調整
	for (int y = 0; y < 15; y++) {
		for (int x = 0; x < 15; x++) {
			worldTransform_[y][x].Initialize();
			worldTransform_[y][x].translation_.x = 2 * x - 10;
			worldTransform_[y][x].translation_.y = 2 * y - 15;
			worldTransform_[y][x].translation_.z = -5;
			myFunc_.UpdateWorldTransform(worldTransform_[y][x]);
		}
	}
}

void Map::Draw(ViewProjection& viewProjection) {
	//3Dモデルを描画
	for (int y = 0; y < 15; y++) {
		for (int x = 0; x < 15; x++) {
			if (FirstMap[y][x] == BLOCK) {
				model_->Draw(worldTransform_[y][x], viewProjection, block);
			}
		}
	}
}