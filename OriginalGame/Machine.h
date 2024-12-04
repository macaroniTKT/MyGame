#pragma once
#include "DxLib.h"
#include <math.h>
#include"AABB.h"
#include "Stage.h"
#include"Quaternion.h"

class Machine {
protected:

public:
	int MachineModel;//モデル読み込み
	float Speed = 0.0f;//加算される速度
	float MaxSpeed;//最大速度
	float SpeedRate;
	double RotSpeed;//回転速度
	float Angle;//Y軸回転の回転値
	VECTOR Rotation;//回転

	QUATERNION Quaternion1;
	QUATERNION Quaternion2;

	VECTOR xAxis, yAxis, zAxis;
	float yaw = 0.0f, pitch = 0.0f, roll = 0.0f;
	MATRIX mat;
	MATRIX matRot;
	MATRIX matTrans;
	MATRIX mat01;


	VECTOR Position;  //座標
	VECTOR LF, RF, LB, RB;//角の四点---LeftFront ,RightBack
	VECTOR LF0, RF0, LB0, RB0;//回転の予測座標

	VECTOR Dir;

	bool AdvRec;//回転可能
	bool isRun;//前進中
	bool isBack;//後退中

	bool FrontBounce;//前方衝突跳ね返り
	bool BackBounce;//後方衝突跳ね返り

	virtual void Initialize() = 0;//開始
	virtual void Finalize() = 0;//終了
	virtual void Update() = 0;
	virtual void Draw() = 0;//描画
	virtual void Move() = 0;//基本移動(共通)
	virtual void Bounce(int TF) = 0;//基本移動(共通)
	virtual void Attack() = 0;//壊すアクション
	virtual void Action() = 0;//独自アクションがあれば追加
	virtual void Inclination(VECTOR a, VECTOR b, VECTOR c,int Area) = 0;//車体を傾ける

	MATRIX Mat;//回転行列
};

class Bulldozer : public Machine {
public:
	void Initialize();
	void Finalize();

	void Update();
	void Move();
	void Bounce(int TF);
	void Draw();
	void Attack();
	void Action();
	void Inclination(VECTOR a,VECTOR b,VECTOR c,int Area);
};
//
//class Buggy :public  Machine {
//	void Initialize();
//	void Finalize();
//
//	void Update();
//	void Move();
//	void Bounce(int TF);
//	void Draw();
//	void Attack();
//	void Action();
//	void Inclination(VECTOR a,VECTOR b,VECTOR c,int Area);
//};
//
//class DampCar :public  Machine {
//	void Initialize();
//	void Finalize();
//
//	void Update();
//	void Move();
//	void Bounce(int TF);
//	void Draw();
//	void Attack();
//	void Action();
//	void Inclination(VECTOR a,VECTOR b,VECTOR c,int Area);
//};
//
//class Robot :public  Machine {
//	void Initialize();
//	void Finalize();
//
//	void Update();
//	void Move();
//	void Bounce(int TF);
//	void Draw();
//	void Attack();
//	void Action();
//	void Inclination(VECTOR a,VECTOR b,VECTOR c,int Area);
//};