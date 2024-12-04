#pragma once
#include "DxLib.h"
#include <math.h>
#include"AABB.h"
#include "Stage.h"
#include"Quaternion.h"

class Machine {
protected:

public:
	int MachineModel;//���f���ǂݍ���
	float Speed = 0.0f;//���Z����鑬�x
	float MaxSpeed;//�ő呬�x
	float SpeedRate;
	double RotSpeed;//��]���x
	float Angle;//Y����]�̉�]�l
	VECTOR Rotation;//��]

	QUATERNION Quaternion1;
	QUATERNION Quaternion2;

	VECTOR xAxis, yAxis, zAxis;
	float yaw = 0.0f, pitch = 0.0f, roll = 0.0f;
	MATRIX mat;
	MATRIX matRot;
	MATRIX matTrans;
	MATRIX mat01;


	VECTOR Position;  //���W
	VECTOR LF, RF, LB, RB;//�p�̎l�_---LeftFront ,RightBack
	VECTOR LF0, RF0, LB0, RB0;//��]�̗\�����W

	VECTOR Dir;

	bool AdvRec;//��]�\
	bool isRun;//�O�i��
	bool isBack;//��ޒ�

	bool FrontBounce;//�O���Փ˒��˕Ԃ�
	bool BackBounce;//����Փ˒��˕Ԃ�

	virtual void Initialize() = 0;//�J�n
	virtual void Finalize() = 0;//�I��
	virtual void Update() = 0;
	virtual void Draw() = 0;//�`��
	virtual void Move() = 0;//��{�ړ�(����)
	virtual void Bounce(int TF) = 0;//��{�ړ�(����)
	virtual void Attack() = 0;//�󂷃A�N�V����
	virtual void Action() = 0;//�Ǝ��A�N�V����������Βǉ�
	virtual void Inclination(VECTOR a, VECTOR b, VECTOR c,int Area) = 0;//�ԑ̂��X����

	MATRIX Mat;//��]�s��
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