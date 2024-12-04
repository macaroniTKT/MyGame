#pragma once
#include "DxLib.h"
#include "Stage.h"
class Object {
public:
	VECTOR Scale;//モデルのサイズ
	VECTOR ModelPos, ModelPosNavi;
	VECTOR OLU,ORU,OLD,ORD;//角の四点---ObjectLeftUp,ObjectRightDown
	int Building,Debri;//ビル本体 , 壊れたビルの欠片
	int AnimAttachIndexB, AnimAttachIndexD;//アニメーション名--AnimationAttachIndexBuilding,AnimationAttachIndexDebri
	float  AnimTotalTime;//アニメーション総時間
	float  AnimNowTime;//アニメーション	経過時間
	bool isHit;//オブジェクトヒット状態
	bool CameraClip(VECTOR pos1, VECTOR pos2, VECTOR pos3, VECTOR pos4);//カメラ内外判定

	virtual void Initialize() = 0;//開始
	virtual void Finalize() = 0;//終了
	virtual void Update() = 0;//
	virtual void Draw() = 0;//描画

	//アニメーション操作
	virtual void Animation() = 0;
	virtual void SetAnimation() = 0;
};
class Object1 :public Object {
	void Initialize();
	void Finalize();
	void Update();
	void Draw();
	void Animation();
	void SetAnimation();
};
class Object2 :public Object {
	void Initialize();
	void Finalize();
	void Update();
	void Draw();
	void Animation();
	void SetAnimation();
};