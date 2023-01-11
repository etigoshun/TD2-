#pragma once

#include "Model.h"
#include "WorldTransform.h"
#include "Function.h"
#include <cassert>
#include "DebugText.h"
#include"Input.h"
#include "MathUtility.h"
#include "ViewProjection.h"

class Map
{
public:		//�����o�֐�

	//������
	void Initialize(Model* model, uint32_t textureHandle);

	//�`��
	void Draw(ViewProjection& viewProjection);


	enum Mapinfo {
		NONE, //0
		BLOCK //1
	};

public:		//�}�b�v

	//���X�e�[�W
	int FirstMap[15][15]{
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	};

private:	//�����o�ϐ�
	//���[���h�ϊ��f�[�^
	WorldTransform worldTransform_[15][15] = {};
	int BlockSize;

	//���f��
	Model* model_ = nullptr;

	//�e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;

	//�t�@���N�V����
	MyFunc myFunc_;

	int block;
};