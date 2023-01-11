#include "RailCamera.h"
#include "MyMath.h"
#include "Function.h"

void RailCamera::Initialize(Vector3& position, Vector3& rotation){
	//シングルトンインスタンスを取得する
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	//ワールドトランスフォームの初期設定
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	worldTransform_.rotation_ = rotation;

	//ビュープロジェクションの初期化
	viewProjection_.farZ = 2000.0f;
	viewProjection_.Initialize();

}

void RailCamera::Update(){
	if (worldTransform_.translation_.z > 0){
		ZoomOut(cameraMove);
	}

	//カメラの位置の移動処理
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

	//デバッグ用表示
	debugText_->SetPos(50, 50);
	debugText_->Printf("RailCamera pos:(%f, %f, %f)", viewProjection_.eye.x, viewProjection_.eye.y, viewProjection_.eye.z);
	
}

void RailCamera::ZoomOut(Vector3 cameraMove){

	cameraMove.y -= 0.1;

	cameraMove.z -= 0.5;

	worldTransform_.translation_ += cameraMove;

	//行列の更新
	myFunc_.UpdateWorldTransform(worldTransform_);

	//カメラ視点座標を設定
	viewProjection_.eye = worldTransform_.translation_;

	//ワールド前方ベクトル
	Vector3 forward(0, 0, 1);
	//レールカメラの回転を判定
	forward = Transform(forward, worldTransform_);
	//視点から前方に適当な距離進んだ位置が注視点
	forward += viewProjection_.eye;
	viewProjection_.target = forward;

	//ワールド上方ベクトル
	Vector3 up(0, 1, 0);
	//レールカメラの回転を反映(レールカメラの上方ベクトル)
	viewProjection_.up = Transform(up, worldTransform_);

	//ビュープロジェクションを更新
	viewProjection_.UpdateMatrix();
}
