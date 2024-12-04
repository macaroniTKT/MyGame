#include "Machine.h"

extern SceneMgr* Scene;

void Machine::Draw() {
	MV1DrawModel(MachineModel);   // ���f���̕`��
}
void Machine::Move() {
	if (Speed > MaxSpeed)Speed = MaxSpeed;//������������Œ�
	if (Speed < -MaxSpeed/2)Speed = -MaxSpeed/2;//�����̉������Œ�

	if ((!isBack) && (!isRun)) { //��~���Ă���
		if (Speed > 0)Speed -= 0.08f;
		else Speed += 0.08f;
		if(Speed<=0.08f&&Speed>=-0.08f)AdvRec = false;//��]�����b�N
	}
	
	Dir = VGet(sinf(Angle * (DX_PI_F / 180)) * Speed, 0, cosf(Angle * (DX_PI_F / 180)) * Speed);

	//�ړ�
	this->Position.x += Dir.x;
	this->Position.z += Dir.z;
	this->LF.x += Dir.x;
	this->LF.z += Dir.z;
	this->RF.x += Dir.x;
	this->RF.z += Dir.z;
	this->LB.x += Dir.x;
	this->LB.z += Dir.z;
	this->RB.x += Dir.x;
	this->RB.z += Dir.z;
	matTrans = MGetTranslate(Position);

	if (Scene->TypeRadicon) {
		//����^�C�v�ŕ���
//--------------------------------
// �������x�ݒ�
// 
// ���s���:ON
// ����
//--------------------------------
		if (((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) || (Scene->input.Buttons[12] == 1)) {
			if(!AdvRec)Speed = 5.0f;
			AdvRec = true;
			isRun = true;
			Speed += 0.05;

			if (Speed < 0)Speed += 0.5;
		}
		else {
			isRun = false;
			//isBack = false;
		}
		 if (((GetMouseInput() & MOUSE_INPUT_RIGHT) != 0) || (Scene->input.Buttons[13] == 1)) {
			if (!AdvRec)Speed -= 1.5f;

				AdvRec = true;
				isBack = true;
				Speed -= 0.05f;
				if (Speed > 0)Speed -= 0.5;
		}
		else {
			isBack = false;
		}
	}
	else{
		//����^�C�v�ŕ���
//--------------------------------
// �������x�ݒ�
// 
// ���s���:ON
// ����
//--------------------------------
		// ���̑���
		if (CheckHitKey(KEY_INPUT_W) || (Scene->input.ThumbLY > 1.0f)) {
			if (!AdvRec)Speed = 5.0f;
			AdvRec = true;
			isRun = true;
			Speed += 0.05;

			if (Speed < 0)Speed += 0.5;
		}
		else {
			isRun = false;
			//isBack = false;
		}
		if (CheckHitKey(KEY_INPUT_S) || (Scene->input.ThumbLY < -1.0f)) {
			if (!AdvRec)Speed -= 1.5f;

			AdvRec = true;
			isBack = true;
			Speed -= 0.05f;

			if (Speed > 0)Speed -= 0.5;
		}
		else {
			//isRun = false;
			isBack = false;
		}
	}

	if (CheckHitKey(KEY_INPUT_D) || (Scene->input.ThumbLX > 1.0f)) {
		if (AdvRec) {
			this->Angle += RotSpeed;  // �E��]
		}
	}
	if (CheckHitKey(KEY_INPUT_A) || (Scene->input.ThumbLX < -1.0f)) {
		if (AdvRec) {
			this->Angle -= RotSpeed;  // ����]
		}
	}

	//��]�s��ŉ�]
	Mat = MGetIdent();

	mat = MGetRotY(Angle * (DX_PI_F / 180));

	LF = VAdd(Position, VTransform(LF0, mat));
	RF = VAdd(Position, VTransform(RF0, mat));
	LB = VAdd(Position, VTransform(LB0, mat));
	RB = VAdd(Position, VTransform(RB0, mat));
	SpeedRate = Speed / MaxSpeed;
}
void Machine::Bounce(int TF) {
	//���˕Ԃ�
	if(Scene->UseVibration)StartJoypadVibration(1, 500, 10, -1);

	//�O��I��
	switch (TF) {
	case 1:
		FrontBounce = true;
		break;
	case 2:
		BackBounce = true;
		break;
	}
	//�i�s�����t���Ɍ��݂̑��x�����Z���߂荞�݉�� & ��~
	if (FrontBounce) {
		this->Position.x -= sinf(this->Angle) * Speed * 2;
		this->Position.z -= cosf(this->Angle) * Speed * 2;
		this->LF.x -= sinf(this->Angle) * Speed * 2;
		this->LF.z -= cosf(this->Angle) * Speed * 2;
		this->RF.x -= sinf(this->Angle) * Speed * 2;
		this->RF.z -= cosf(this->Angle) * Speed * 2;
		this->LB.x -= sinf(this->Angle) * Speed * 2;
		this->LB.z -= cosf(this->Angle) * Speed * 2;
		this->RB.x -= sinf(this->Angle) * Speed * 2;
		this->RB.z -= cosf(this->Angle) * Speed * 2;
		Speed = 0;
	}
	if (BackBounce) {
		this->Position.x += sinf(this->Angle) * Speed * 4;
		this->Position.z += cosf(this->Angle) * Speed * 4;
		this->LF.x += sinf(this->Angle) * Speed * 4;
		this->LF.z += cosf(this->Angle) * Speed * 4;
		this->RF.x += sinf(this->Angle) * Speed * 4;
		this->RF.z += cosf(this->Angle) * Speed * 4;
		this->LB.x += sinf(this->Angle) * Speed * 4;
		this->LB.z += cosf(this->Angle) * Speed * 4;
		this->RB.x += sinf(this->Angle) * Speed * 4;
		this->RB.z += cosf(this->Angle) * Speed * 4;
		Speed = 0;
	}
		FrontBounce = false;
		BackBounce = false;
}
void Machine::Inclination(VECTOR a, VECTOR b, VECTOR c, int Area) {
	//�n�ʂ�3�_����X���Z�o

	VECTOR OU = VGet(0, 1, 0);
	VECTOR N= VCross(VSub(b, a), VSub(c, a));

	VECTOR Ax1 = VCross(OU, N);

	Ax1=VNorm(Ax1);

	float b1 = VSize(OU) * VSize(N);
	float a1 = VDot(OU, N);
	float R1 = acos(a1/b1);

	Quaternion2 = CreateRotationQuaternion(R1, Ax1);

	//DrawFormatString(0, 0, 3200, "%f.%f.%f.%f", Quaternion2.x, Quaternion2.y, Quaternion2.z, Quaternion2.t);
	//DrawFormatString(0, 40, 3200, "%f.%f.%f.%f", a.x, a.y, a.z);
	//DrawFormatString(0, 60, 3200, "%f.%f.%f.%f", b.x, b.y, b.z);
	//DrawFormatString(0, 80, 3200, "%f.%f.%f.%f", c.x, c.y, c.z);

	Quaternion1 = QuaternionSlerp(Quaternion1, Quaternion2, 0.2f);

	mat01 = QuaternionToMatrix(Quaternion1);


	VECTOR O = VGet(Position.x, 0,Position.z);

	O.y = a.y - 1 / N.y * (N.x * (O.x - a.x) + N.z * (O.z - a.z));

	Position.y = O.y;

	matTrans = MGetTranslate(Position);

	mat = MMult(mat, mat01);         //��]�~�X�P�[��
	mat = MMult(mat, matTrans);       //�ړ��~��]�~�X�P�[��
	MV1SetMatrix(MachineModel, mat);         //�s��Z�b�g
}
///////////////////////////////////////////////////////////////////////////////////////////
void Bulldozer::Initialize() {
	MachineModel = MV1LoadModel("Asset/Machine/MV1/Bulldozer.mv1");//���f���ǂݍ���

	Position = VGet(0.0f, 0.0f, 0.0f);//������

	LF = VGet(Position.x - 150, Position.y, Position.z + 400);//���f���T�C�Y����p�̂S�_�̐ݒ�(���O)
	RF = VGet(Position.x + 150, Position.y, Position.z + 400);//���f���T�C�Y����p�̂S�_�̐ݒ�(�E�O)
	LB = VGet(Position.x - 150, Position.y, Position.z - 250);//���f���T�C�Y����p�̂S�_�̐ݒ�(����)
	RB = VGet(Position.x + 150, Position.y, Position.z - 250);//���f���T�C�Y����p�̂S�_�̐ݒ�(�E��)
	RotSpeed = 1.5f;//��]���x
	MaxSpeed = 30.0f;//�ő呬�x

	LF0 = VSub(LF, Position);//��]�̂��߂̍��W�̏����ݒ�
	RF0 = VSub(RF, Position);
	LB0 = VSub(LB, Position);
	RB0 = VSub(RB, Position);
		
	Quaternion1.x = Quaternion1.y = Quaternion1.z = 0.0f;
	Quaternion2.x = Quaternion2.y = Quaternion2.z = 0.0f;
	Quaternion1.t = 1.0f;
	Quaternion2.t = 1.0f;
	CreateIdentityMatrix(&mat);
	CreateIdentityMatrix(&matRot);
	matTrans = MGetTranslate(Position);

	Mat = MGetRotY(Angle * (DX_PI_F / 180));//��]�s��擾
}
void Bulldozer::Finalize() {

}
void Bulldozer::Update() {
	Move();
	Draw();
	Attack();
	Action();
}
void Bulldozer::Draw() {
	Machine::Draw();
}
void Bulldozer::Move() {
	Machine::Move();
}
void Bulldozer::Bounce(int TF) {
	Machine::Bounce(TF);
}
void Bulldozer::Attack() {

}
void Bulldozer::Action() {

}
void Bulldozer::Inclination(VECTOR a, VECTOR b, VECTOR c,int Area){
	Machine::Inclination(a, b, c, Area);
}
/////////////////////////////////////////////////////////////////////////////////////////////
//void Buggy::Initialize() {
//	MachineModel = MV1LoadModel("Asset/Machine/MV1/Buggy.mv1");
//	Position = VGet(0.0f, 0.0f, 0.0f);
//
//	LF = VGet(Position.x - 150, Position.y, Position.z + 400);
//	RF = VGet(Position.x + 150, Position.y, Position.z + 400);
//	LB = VGet(Position.x - 150, Position.y, Position.z - 250);
//	RB = VGet(Position.x + 150, Position.y, Position.z - 250);
//	RotSpeed *= 3;
//}
//void Buggy::Finalize() {
//
//}
//void Buggy::Update() {
//	Draw();
//	Move();
//	//�����
//	Attack();
//	Action();
//}
//void Buggy::Draw() {
//	Machine::Draw();
//}
//void Buggy::Move() {
//	Machine::Move();
//}
//void Buggy::Bounce(int TF) {
//	Bounce(TF)
//}
//void Buggy::Attack() {
//
//}
//void Buggy::Action() {
//
//}
/////////////////////////////////////////////////////////////////////////////////////////////
//void DampCar::Initialize() {
//	MachineModel = MV1LoadModel("Asset/Machine/MV1/DampCar.mv1");
//	Position = VGet(0.0f, 0.0f, 0.0f);
//
//	LF = VGet(Position.x - 150, Position.y, Position.z + 400);
//	RF = VGet(Position.x + 150, Position.y, Position.z + 400);
//	LB = VGet(Position.x - 150, Position.y, Position.z - 250);
//	RB = VGet(Position.x + 150, Position.y, Position.z - 250);
//}
//void DampCar::Finalize() {
//}
//void DampCar::Update() {
//	Draw();
//	Move();
//	//�����
//	Attack();
//	Action();
//}
//void DampCar::Draw() {
//	DampCar::Draw();
//}
//void DampCar::Move() {
//	Machine::Move();
//}
//void DampCar::Bounce(int TF) {
//	Bounce(TF)
//}
//void DampCar::Attack() {
//
//}
//void DampCar::Action() {
//
//}
/////////////////////////////////////////////////////////////////////////////////////////////
//void Robot::Initialize() {
//	MachineModel = MV1LoadModel("");
//}
//void Robot::Finalize() {
//}
//void Robot::Update() {
//	Draw();
//	Move();
//	//�����
//	Attack();
//	Action();
//}
//void Robot::Draw() {
//	Machine::Draw();
//}
//void Robot::Move() {
//	Machine::Move();
//}
//void Robot::Bounce(int TF) {
//	Bounce(TF)
//}
//void Robot::Attack() {
//
//}
//void Robot::Action() {
//
//}

/////////////////////////////////////////////////////////////////////////////////////////////