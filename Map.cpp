#include "Map.h"

void Map::Initialize(Model* model, uint32_t textureHandle){

	//NULL�|�C���^�`�F�b�N
	assert(model);

	//�����Ƃ��Ď󂯎�����f�[�^�������o�ϐ��ɋL�^����
	model_ = model;
	textureHandle_ = textureHandle;

	for (int y = 0; y < 15; y++) {
		for (int x = 0; x < 15; x++) {
			worldTransform_[y][x].Initialize();
			worldTransform_[y][x].translation_.x = 2 * x;
			worldTransform_[y][x].translation_.y = 2 * y;
			worldTransform_[y][x].translation_.z = 0;
			myFunc_.UpdateWorldTransform(worldTransform_[y][x]);
		}
	}
	
}

void Map::Draw(const ViewProjection& viewProjection) {
	//3D���f����`��
	for (int y = 0; y < 15; y++) {
		for (int x = 0; x < 15; x++) {
			if (FirstMap[y][x] == 1)
			{
				model_->Draw(worldTransform_[y][x], viewProjection);
			}
		}
	}
}
