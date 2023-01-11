#include "RailCamera.h"
#include "MyMath.h"
#include "Function.h"

void RailCamera::Initialize(Vector3& position, Vector3& rotation){
	//�V���O���g���C���X�^���X���擾����
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	//���[���h�g�����X�t�H�[���̏����ݒ�
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	worldTransform_.rotation_ = rotation;

	//�r���[�v���W�F�N�V�����̏�����
	viewProjection_.farZ = 2000.0f;
	viewProjection_.Initialize();

}

void RailCamera::Update(){
	if (worldTransform_.translation_.z > 0){
		ZoomOut(cameraMove);
	}

	//�J�����̈ʒu�̈ړ�����
	if(input_->PushKey(DIK_UP)) {
		viewProjection_.eye.y += 0.1;
	}

	if (input_->PushKey(DIK_DOWN)) {
		viewProjection_.eye.y -= 0.1;
	}

	if (input_->PushKey(DIK_RIGHT)) {
		viewProjection_.eye.x += 0.1;
	}

	if (input_->PushKey(DIK_LEFT)) {
		viewProjection_.eye.x -= 0.1;
	}

	if (input_->PushKey(DIK_Q)) {
		viewProjection_.eye.z += 0.1;
	}

	if (input_->PushKey(DIK_E)) {
		viewProjection_.eye.z -= 0.1;
	}

	//�f�o�b�O�p�\��
	debugText_->SetPos(50, 50);
	debugText_->Printf("RailCamera pos:(%f, %f, %f)", viewProjection_.eye.x, viewProjection_.eye.y, viewProjection_.eye.z);
	
}

void RailCamera::ZoomOut(Vector3 cameraMove){

	cameraMove.y -= 0.1;

	cameraMove.z -= 0.5;

	worldTransform_.translation_ += cameraMove;

	//�s��̍X�V
	myFunc_.UpdateWorldTransform(worldTransform_);

	//�J�������_���W��ݒ�
	viewProjection_.eye = worldTransform_.translation_;

	//���[���h�O���x�N�g��
	Vector3 forward(0, 0, 1);
	//���[���J�����̉�]�𔻒�
	forward = Transform(forward, worldTransform_);
	//���_����O���ɓK���ȋ����i�񂾈ʒu�������_
	forward += viewProjection_.eye;
	viewProjection_.target = forward;

	//���[���h����x�N�g��
	Vector3 up(0, 1, 0);
	//���[���J�����̉�]�𔽉f(���[���J�����̏���x�N�g��)
	viewProjection_.up = Transform(up, worldTransform_);

	//�r���[�v���W�F�N�V�������X�V
	viewProjection_.UpdateMatrix();
}
