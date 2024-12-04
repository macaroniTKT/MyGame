#include"Object.h"
#include "AABB.h"

bool Object::CameraClip(VECTOR pos1, VECTOR pos2, VECTOR pos3, VECTOR pos4) {
	//カメラ内外判定
	if (!CheckCameraViewClip(pos1)) return true;
	if (!CheckCameraViewClip(pos2)) return true;
	if (!CheckCameraViewClip(pos3)) return true;
	if (!CheckCameraViewClip(pos4)) return true;
	return false;
}
void Object1::Initialize() {
	//モデル読み込み
	Building = MV1LoadModel("Asset/Building/MV1/Tower.mv1");
	Building = MV1DuplicateModel(Building);
	Debri = MV1LoadModel("Asset/Building/MV1/Debris.mv1");
	Debri = MV1DuplicateModel(Debri);

	//サイズセット
	MV1SetScale(Building, VGet(0.3f, 0.3f,0.3f));
	MV1SetPosition(Building,ModelPos);
	MV1SetScale(Debri, VGet(0.3f, 0.3f, 0.3f));
	MV1SetPosition(Debri, ModelPos);

	//4角設定(中央はゲーム内で設定済み)
	OLU = VGet(ModelPos.x - MAPLONG / 2, ModelPos.y, ModelPos.z + MAPLONG / 2);
	ORU = VGet(ModelPos.x + MAPLONG / 2, ModelPos.y, ModelPos.z + MAPLONG / 2);
	OLD = VGet(ModelPos.x - MAPLONG / 2, ModelPos.y, ModelPos.z - MAPLONG / 2);
	ORD = VGet(ModelPos.x + MAPLONG / 2, ModelPos.y, ModelPos.z - MAPLONG / 2);
}
void Object1::Finalize() {
	//モデル削除
	MV1DeleteModel(Building);
	MV1DeleteModel(Debri);
}
void Object1::Update() {
	Draw();
	Animation();
}
void Object1::Draw() {

	if (CameraClip(OLU,ORU,OLD,ORD))//カメラ内外判定
	{
		MV1DrawModel(Building);
		MV1DrawModel(Debri);
	}
}
void Object1::Animation() {
	//アニメ秒数を加算
	 AnimNowTime += 1.0f;
	 //アニメが進んだら
	 if (AnimNowTime >= AnimTotalTime)
		 if (isHit)Finalize();//当たっていたら終了処理
		 else AnimNowTime = 0.0f;//当たっていないならリセット

	 //アニメ秒数でコマ送り
	 MV1SetAttachAnimTime(Building, AnimAttachIndexB, AnimNowTime);
	 MV1SetAttachAnimTime(Debri, AnimAttachIndexD, AnimNowTime);
}
void Object1::SetAnimation() {
	//アニメ秒数をリセット
	AnimNowTime = 0.0f;
	//アニメーションセット
	AnimAttachIndexB = MV1AttachAnim(Building, 0, -1, false);
	AnimAttachIndexD = MV1AttachAnim(Debri, 0, -1, false);
	AnimTotalTime = MV1GetAttachAnimTotalTime(Debri, AnimAttachIndexD);
	MV1SetAttachAnimTime(Building, AnimAttachIndexB, AnimNowTime);
	MV1SetAttachAnimTime(Debri, AnimAttachIndexD, AnimNowTime);
	MV1SetScale(Debri, VGet(0.5f, 0.5f, 0.5f));
}
////////////////////////////////////////////////////////////////////////////////////////////////
//void Object2::Initialize() {
//	//ModelPos = VGet(1000, 0, 1200);
//	Building = MV1LoadModel("Asset/Building/MV1/Tower.mv1");
//	Building = MV1DuplicateModel(Building);
//	MV1SetScale(Building, VGet(0.3f, 0.3f, 0.3f));
//	MV1SetPosition(Building, ModelPos);
//}
//void Object2::Finalize() {
//	MV1DeleteModel(Building);
//}
//void Object2::Update() {
//	Draw();
//}
//void Object2::Draw() {
//		if (CameraClip(OLU, ORU, OLD, ORD))
//		MV1DrawModel(Building);   // モデルの描画
//}
//void Object2::Animation() {
//
//}