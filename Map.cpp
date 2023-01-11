#include "Map.h"

void Map::Initialize(Model* model, uint32_t textureHandle) {
	//引数として受け取ったデータをメンバ変数に記録する
	BlockSize = 32;
	block = textureHandle;
	model_ = model;

	for (int y = 0; y < 15; y++) {
		for (int x = 0; x < 15; x++) {
			worldTransform_[y][x].Initialize();
			worldTransform_[y][x].translation_.x = 2 * x - 10;
			worldTransform_[y][x].translation_.y = 2 * y - 5;
			worldTransform_[y][x].translation_.z = -2;
			myFunc_.UpdateWorldTransform(worldTransform_[y][x]);
		}
	}
}

void Map::Draw(const ViewProjection& viewProjection) {
	//3Dモデルを描画
	for (int y = 0; y < 15; y++) {
		for (int x = 0; x < 15; x++) {
			if (FirstMap[y][x] == BLOCK) {
				model_->Draw(worldTransform_[y][x], viewProjection, block);
			}
		}
	}
}