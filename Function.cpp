#include "Function.h"
#include"WorldTransform.h"

#include<math.h>
void MyFunc::UpdateWorldTransform(WorldTransform& worldTransform) {
	//�s��
	useful::UsefulMat usefulMat;

	//////
	useful::setScaleMat(usefulMat.scale, worldTransform);
	useful::setRotateMat(usefulMat, worldTransform);
	useful::setTranslateMat(usefulMat.translate, worldTransform);

	//matworld�ɒP�ʍs�������
	worldTransform.matWorld_ = MathUtility::Matrix4Identity();

	//�s��̌v�Z
	useful::setTransformationWolrdMat(usefulMat, worldTransform);

	//�s��̓]��
	worldTransform.TransferMatrix();
}

Vector3 Vector3s(Vector3& v1, Vector3& v2) {
	Vector3 temp(v2);
	return temp -= v1;
}

float length(Vector3& vec) {
	return std::sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

/// <summary>
/// �X�P�[�����O�s��̍쐬
/// </summary>
/// <param name="scale">WorldTransform��scale_</param>
/// <returns>�쐬�����X�P�[�����O�s��</returns>
Matrix4 CreateMatScale(Vector3 scale) {
	Matrix4 mat;
	mat.m[0][0] = scale.x;
	mat.m[1][1] = scale.y;
	mat.m[2][2] = scale.z;
	mat.m[3][3] = 1;

	return mat;
}

Vector3 CreateVector(Vector3 velocity, WorldTransform& worldTransform) {
	Vector3 dirVector;
	dirVector.x = velocity.x * worldTransform.matWorld_.m[0][0] + velocity.y * worldTransform.matWorld_.m[1][0] + velocity.z * worldTransform.matWorld_.m[2][0];
	dirVector.y = velocity.x * worldTransform.matWorld_.m[0][1] + velocity.y * worldTransform.matWorld_.m[1][1] + velocity.z * worldTransform.matWorld_.m[2][1];
	dirVector.z = velocity.x * worldTransform.matWorld_.m[0][2] + velocity.y * worldTransform.matWorld_.m[1][2] + velocity.z * worldTransform.matWorld_.m[2][2];
	return dirVector;
}

Matrix4 CreateMatIdentity() {
	Matrix4 mat;
	mat.m[0][0] = 1;
	mat.m[1][1] = 1;
	mat.m[2][2] = 1;
	mat.m[3][3] = 1;
	return mat;
}



/// <summary>
/// Z���̉�]�s��쐬
/// </summary>
/// <param name="rotation">WorldTransform��rotation_</param>
/// <returns>Z������̉�]�s��</returns>
Matrix4 CreateMatRotationZ(Vector3 rotation) {
	Matrix4 mat = CreateMatIdentity();
	mat.m[0][0] = cos(rotation.z);
	mat.m[0][1] = sin(rotation.z);
	mat.m[1][0] = -sin(rotation.z);
	mat.m[1][1] = cos(rotation.z);

	return mat;
}

/// <summary>
/// X���̉�]�s��쐬
/// </summary>
/// <param name="rotation">WorldTransform��rotation_</param>
/// <returns>X���̉�]�s��</returns>
Matrix4 CreateMatRotationX(Vector3 rotation) {
	Matrix4 mat = CreateMatIdentity();
	mat.m[1][1] = cos(rotation.x);
	mat.m[1][2] = sin(rotation.x);
	mat.m[2][1] = -sin(rotation.x);
	mat.m[2][2] = cos(rotation.x);

	return mat;
}


/// <summary>
/// Y���̉�]�s��
/// </summary>
/// <param name="rotation">WorldTransform��rotation_</param>
/// <returns>Y���̉�]�s��</returns>
Matrix4 CreateMatRotationY(Vector3 rotation) {
	Matrix4 mat = CreateMatIdentity();
	mat.m[0][0] = cos(rotation.y);
	mat.m[0][2] = -sin(rotation.y);
	mat.m[2][0] = sin(rotation.y);
	mat.m[2][2] = cos(rotation.y);

	return mat;
}


/// <summary>
/// ���s�ړ�
/// </summary>
/// <param name="translation">WorldTransform��Translation_</param>
/// <returns>���s�ړ�</returns>
Matrix4 CreateMatTranslation(Vector3 translation) {
	Matrix4 lat = CreateMatIdentity();
	lat.m[3][0] = translation.x;
	lat.m[3][1] = translation.y;
	lat.m[3][2] = translation.z;
	lat.m[3][3] = 1;

	return lat;

}

Vector3 bvector(Vector3& velocity, Matrix4& mat) {

	Vector3 result;
	//�|���Z

	result.x = velocity.x * mat.m[0][0] +
		velocity.y * mat.m[1][0] +
		velocity.z * mat.m[2][0];

	result.y = velocity.x * mat.m[0][1] +
		velocity.y * mat.m[1][1] +
		velocity.z * mat.m[2][1];

	result.z = velocity.x * mat.m[0][2] +
		velocity.y * mat.m[1][2] +
		velocity.z * mat.m[2][2];

	return result;
}

// ���x�x�N�g�������@�̌����ɍ��킹�ĉ�]������


// �s��X�V
void CreateMatrixUpdate(WorldTransform& worldTransform) {

	//�X�P�[�����O�E��]�E���s�ړ������������s����v�Z
	worldTransform.matWorld_ = CreateMatIdentity();
	worldTransform.matWorld_ *= CreateMatScale(worldTransform.scale_); // �X�P�[�����O�s��쐬
	worldTransform.matWorld_ *= CreateMatRotationZ(worldTransform.rotation_);
	worldTransform.matWorld_ *= CreateMatRotationY(worldTransform.rotation_);
	worldTransform.matWorld_ *= CreateMatRotationX(worldTransform.rotation_);
	worldTransform.matWorld_ *= CreateMatTranslation(worldTransform.translation_);

	//�s��̓]��
	worldTransform.TransferMatrix();
}


Vector3 normalize(Vector3& vec)
{
	float len = length(vec);

	if (len != 0) {
		return vec /= len;
	}

	return vec;
}

