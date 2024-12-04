#include"Game.h"

extern SceneMgr* Scene;
extern Sound* sound;

int Judge=0; //�󂵂��I�u�W�F�N�g��
Machine* M_Array[1]; //�}�V���N���X 
Stage* stage; //�X�e�[�W�N���X
Object* O_Array[10]; //�I�u�W�F�N�g�N���X
VECTOR Nearest, InvisibilePos = VGet(30000, 30000, 30000); //�}�V������ł��߂��n�_ , �B���p
const int AreaSceal = MAPLONG * MAPWIDE; //�ړ��\�G���A�̕�
int Navi; //�i�r�I�u�W�F�N�g
int Indicator;
int GraphX, GraphY;
int Number[11];
int NumGraX, NumGraY;

int KeyGraph[9];
int KeyGraX, KeyGraY;

VECTOR NaviPos; //�i�r�I�u�W�F�N�g���W
int AnimAttachIndexN[4]; //�i�r�I�u�W�F�N�g�̃A�j���[�V����
float  AnimTotalTimeN;	//�A�j���[�V�������Đ�����
float  AnimNowTimeN;	//�A�j���[�V�����Đ�����

VECTOR  ALT, ART, ALB, ARB;//�G���A�̊p�̎l�_---AreaLeftTop,AreaRightBottom

Effect* effect[255];
int Ef=0;

VECTOR CameraPos = VGet(0.0f, 0.0f, 0.0f);// �J�����ʒu
const float Camera_Distance = 400.f;//�J�����ő勗��
float Angle = 0.0f;//�J�����p�x
float Distance = 0.0f;//�ړ��̃J��������

int ObjectMax = 5;//�I�u�W�F�N�g�������ݒ�
int ObjectNow;//�I�u�W�F�N�g���ݐ�
int MapGridX, MapGridZ;//�}�b�v�ʒu����
int MachineGridX, MachineGridZ;//�}�V���̃}�b�v�ʒu����
int BackScreen;//�w�i

float Timer=0.f;
float TimeLimit = 4*1000;
float StartTime = 0.f;

void Game::Game_Initialize() {//������
	SRand(0);
	LoadGraphs();
	BackScreen = LoadGraph("Asset/MapTexture.png");//�w�i�摜�ǂݍ���
	Indicator = LoadGraph("Asset/Indicator.png");//�w�i�摜�ǂݍ���
	GetGraphSize(Indicator, &GraphX, &GraphY);
	//�}�b�v����
	stage = new Stage();
	stage->Initialize();

	ObjectNow = ObjectMax;//�I�u�W�F�N�g���������Z�b�g

	//�I�u�W�F�N�g����
	for (int i = 0; i < ObjectMax; i++) {
		MapGridX = GetRand(9);
		MapGridZ = GetRand(9);
		O_Array[i] = new Object1();
		O_Array[i]->ModelPos = VGet(stage->MapTip[MapGridX * 2][MapGridZ * 2]->Pos.x, stage->MapTip[MapGridX * 2][MapGridZ * 2]->Pos.y + DefaltHeight / 2, stage->MapTip[MapGridX * 2][MapGridZ * 2]->Pos.z);//�����_���n�_�ɐݒ�
		O_Array[i]->ModelPosNavi = O_Array[i]->ModelPos; //�i�r�I�u�W�F�N�p�̘g�𑵂���
		O_Array[i]->Initialize();//����
	}

	//�}�V������
	M_Array[0] = new Bulldozer();
	M_Array[0]->Initialize();

	Navi = MV1LoadModel("Asset/Building/MV1/ObjectNavi.mv1");//���f���ǂݍ���
	MV1SetScale(Navi, VGet(0.5f, 0.5f, 0.5f));//�T�C�Y�Z�b�g
	Nearest = O_Array[0]->ModelPos; //�Ƃ肠����0�Ԗڂɂ���

	//�A�j���[�V�����ݒ�
	AnimAttachIndexN[0] = MV1AttachAnim(Navi, 3, -1, false);
	AnimAttachIndexN[1] = MV1AttachAnim(Navi, 4, -1, false);
	AnimAttachIndexN[2] = MV1AttachAnim(Navi, 9, -1, false);
	AnimAttachIndexN[3] = MV1AttachAnim(Navi, 14, -1, false);
	AnimTotalTimeN = MV1GetAttachAnimTotalTime(Navi, AnimAttachIndexN[0]);

	for (int i = 0; i < 255; i++) {
		effect[i] = new Effect1();
		effect[i]->Initialize();
	}

	WaitTimer(150);
	sound->Sound_BGM01(true);//BGM�Đ�

	TimeLimit = 4 * 1000;
	Scene->ChangePhase(Phase::Phase_isStart);
}
void Game::Game_Finalize() {//�I������
	M_Array[0]->Finalize();
}
void Game::LoadGraphs() {//�摜�ǂݍ���
	Number[0] = LoadGraph("Asset/Number/00.png");
	Number[1] = LoadGraph("Asset/Number/01.png");
	Number[2] = LoadGraph("Asset/Number/02.png");
	Number[3] = LoadGraph("Asset/Number/03.png");
	Number[4] = LoadGraph("Asset/Number/04.png");
	Number[5] = LoadGraph("Asset/Number/05.png");
	Number[6] = LoadGraph("Asset/Number/06.png");
	Number[7] = LoadGraph("Asset/Number/07.png");
	Number[8] = LoadGraph("Asset/Number/08.png");
	Number[9] = LoadGraph("Asset/Number/09.png");

	Number[10] = LoadGraph("Asset/Number/dot.png");

	GetGraphSize(Number[10], &NumGraX, &NumGraY);

	KeyGraph[0] = LoadGraph("Asset/Key/Wkey.png");
	KeyGraph[1] = LoadGraph("Asset/Key/Akey.png");
	KeyGraph[2] = LoadGraph("Asset/Key/Skey.png");
	KeyGraph[3] = LoadGraph("Asset/Key/Dkey.png");
	KeyGraph[4] = LoadGraph("Asset/Key/MoL.png");
	KeyGraph[5] = LoadGraph("Asset/Key/MoR.png");
	KeyGraph[6] = LoadGraph("Asset/Key/GPA.png");
	KeyGraph[7] = LoadGraph("Asset/Key/GPB.png");
	KeyGraph[8] = LoadGraph("Asset/Key/GPLS.png");

	GetGraphSize(KeyGraph[0], &KeyGraX, &KeyGraY);
}

void Game::Game_Standby() {//�J�n�܂�

	Judge = 0;
	DrawExtendGraph(0, 0, 1200, 800, BackScreen, FALSE); //�w�i�`��
	Game::Follow_Camera(M_Array[0]->Position); //�J�����ǔ�

	stage->Update();
	SearchGrid(); //�}�V���̃X�e�[�W��̍��W�𓾂�
	for (int i = 0; i < ObjectMax; i++) {
		if (O_Array[i] != NULL) { //�G���[���
			O_Array[i]->Draw();  //�`�� , �A�j���[�V����
			SearchObject(i); //�߂��I�u�W�F�N�g�̔���
		}
	}
	AnimNowTimeN += 1.0f;//�A�j�����Ԃ�i�߂�
	if (AnimNowTimeN >= AnimTotalTimeN)AnimNowTimeN = 0.0f;
	MV1SetAttachAnimTime(Navi, AnimAttachIndexN[0], AnimNowTimeN);
	MV1SetAttachAnimTime(Navi, AnimAttachIndexN[1], AnimNowTimeN);
	MV1SetAttachAnimTime(Navi, AnimAttachIndexN[2], AnimNowTimeN);
	MV1SetAttachAnimTime(Navi, AnimAttachIndexN[3], AnimNowTimeN);
	MV1GetAnimNum(Navi);

	M_Array[0]->mat = MGetIdent();
	M_Array[0]->matTrans = MGetIdent();

	switch (stage->CheckArea(MachineGridX, MachineGridZ, M_Array[0]->Position)) { //�}�V�����̃}�b�v�`�b�v�̒��S����̊p�x
	case 1:
		M_Array[0]->Inclination(stage->MapTip[MachineGridX][MachineGridZ]->MLT, stage->MapTip[MachineGridX][MachineGridZ]->MRT, stage->MapTip[MachineGridX][MachineGridZ]->Center, 1); //�C�ӂ̉�]
		break;
	case 2:
		M_Array[0]->Inclination(stage->MapTip[MachineGridX][MachineGridZ]->MRT, stage->MapTip[MachineGridX][MachineGridZ]->MRB, stage->MapTip[MachineGridX][MachineGridZ]->Center, 2);
		break;
	case 3:
		M_Array[0]->Inclination(stage->MapTip[MachineGridX][MachineGridZ]->MRB, stage->MapTip[MachineGridX][MachineGridZ]->MLB, stage->MapTip[MachineGridX][MachineGridZ]->Center, 3);
		break;
	case 4: 
		M_Array[0]->Inclination(stage->MapTip[MachineGridX][MachineGridZ]->MLB, stage->MapTip[MachineGridX][MachineGridZ]->MLT, stage->MapTip[MachineGridX][MachineGridZ]->Center, 4);
		break;
	default:
		break;
	}

	M_Array[0]->Draw(); //�`��
	Game_Count(0);
}
void Game::Game_Update() {//�Q�[����
	Judge = 0;

	DrawExtendGraph(0, 0, 1200, 800, BackScreen, FALSE);//�w�i�`��
	Game::Follow_Camera(M_Array[0]->Position); //�J�����ǔ�

	Game::Area_Update(); //�G���A�̓��O����

	stage->Update();//�X�e�[�W�̕`�� , �N���A����Ȃ�
	SearchGrid(); //�}�V���̃X�e�[�W��̍��W�𓾂�

	//�����蔻�蓙(�܂Ƃ߂���)
	for (int i = 0; i < ObjectMax; i++) {
		if (O_Array[i] != NULL) { //�G���[���
			O_Array[i]->Update();  //�`�� , �A�j���[�V����
			SearchObject(i); //�߂��I�u�W�F�N�g�̔���
			CheckHit(i); //�Փ˔���
			if (O_Array[i]->isHit)Judge += 1;//�q�b�g�ōX�V
		}
	}

	M_Array[0]->mat = MGetIdent();
	M_Array[0]->Update(); //�`�� , ����

	AnimNowTimeN += 1.0f;//�A�j�����Ԃ�i�߂�
	if (AnimNowTimeN >= AnimTotalTimeN)AnimNowTimeN = 0.0f;
	MV1SetAttachAnimTime(Navi, AnimAttachIndexN[0], AnimNowTimeN);
	MV1SetAttachAnimTime(Navi, AnimAttachIndexN[1], AnimNowTimeN);
	MV1SetAttachAnimTime(Navi, AnimAttachIndexN[2], AnimNowTimeN);
	MV1SetAttachAnimTime(Navi, AnimAttachIndexN[3], AnimNowTimeN);
	MV1GetAnimNum(Navi);

	//DrawFormatString(0, 150, GetColor(255, 255, 255), "%f,%f", M_Array[0]->Position.x, M_Array[0]->Position.z);

	switch (stage->CheckArea(MachineGridX, MachineGridZ, M_Array[0]->Position)) { //�}�V�����̃}�b�v�`�b�v�̒��S����̊p�x
	case 1:
		M_Array[0]->Inclination(stage->MapTip[MachineGridX][MachineGridZ]->MLT, stage->MapTip[MachineGridX][MachineGridZ]->MRT, stage->MapTip[MachineGridX][MachineGridZ]->Center, 1); //�C�ӂ̉�]
		break;
	case 2:
		M_Array[0]->Inclination(stage->MapTip[MachineGridX][MachineGridZ]->MRT, stage->MapTip[MachineGridX][MachineGridZ]->MRB, stage->MapTip[MachineGridX][MachineGridZ]->Center, 2);
		break;
	case 3:
		M_Array[0]->Inclination(stage->MapTip[MachineGridX][MachineGridZ]->MRB, stage->MapTip[MachineGridX][MachineGridZ]->MLB, stage->MapTip[MachineGridX][MachineGridZ]->Center, 3);
		break;
	case 4:
		M_Array[0]->Inclination(stage->MapTip[MachineGridX][MachineGridZ]->MLB, stage->MapTip[MachineGridX][MachineGridZ]->MLT, stage->MapTip[MachineGridX][MachineGridZ]->Center, 4);
		break;
	default:
		break;
	}
	//�G�t�F�N�g�ݒ�
	if (M_Array[0]->Speed>0&&M_Array[0]->AdvRec) {
		EffectSet();
		Ef += 1;
		if (Ef >= Effect_MAX)Ef = 0;
	}
	//�G�t�F�N�g�`��
	for (int i = 0; i < Effect_MAX; i++) {
		effect[i]->Draw();
	}

	Game_Draw();
	Input_Draw();

	Game_Count(1);
	if (ObjectMax <= Judge) {//�I�u�W�F�N�g�̔j�󐔂��������𒴂���
		stage->ClearFlag = true;//�Q�[���N���A
		Scene->ChangePhase(Phase::Phase_isEnd);
	}
}
void Game::Game_End() {//�I���܂�
	Judge = ObjectMax;

	DrawExtendGraph(0, 0, 1200, 800, BackScreen, FALSE); //�w�i�`��
	Game::Follow_Camera(M_Array[0]->Position); //�J�����ǔ�

	stage->Update();
	stage->StageFinish((Timer - StartTime) / 1000.f);
}

void Game::EffectSet() {
	effect[Ef]->SetEffect(VGet((M_Array[0]->RB.x + M_Array[0]->LB.x) / 2, M_Array[0]->Position.y, (M_Array[0]->RB.z + M_Array[0]->LB.z) / 2),
		sinf(M_Array[0]->Angle * (DX_PI_F / 180)) * M_Array[0]->Speed, cosf(M_Array[0]->Angle * (DX_PI_F / 180)) * M_Array[0]->Speed, M_Array[0]->SpeedRate);
}

void Game::Game_Draw() {//�`��
	SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 0);
	MV1DrawModel(Navi);//�i�r���f���`��

	//��ʊO�̂ǂ̕�����
	if (CheckCameraViewClip(NaviPos)) {

		VECTOR center = VGet(SizeX * 0.5f, SizeY * 0.5f, 0.0f);

		VECTOR target_pos = VSub(ConvWorldPosToScreenPos(NaviPos), center);

		if (target_pos.z > 1.0f) {
			target_pos.x = -target_pos.x;
			target_pos.y = -target_pos.y;
		}

		float ArrowDir = atan2(NaviPos.x - M_Array[0]->Position.x, NaviPos.z - M_Array[0]->Position.z);

		float half = GraphX / 2;//�摜�̔����̑傫��

		float d = max(fabs(target_pos.x / (center.x - half)), fabs(target_pos.y / (center.y - half)));

		bool isOffscreen = (target_pos.z < 0.0f || d > 1.0f);
		if (isOffscreen)
		{
			target_pos.x /= d;
			target_pos.y /= d;
		}
		target_pos.x += center.x - half;
		target_pos.y += center.y - half;

		DrawRotaGraph2(target_pos.x + half, target_pos.y + half, half, half, 1.0f, ArrowDir, Indicator, true, false);
	}
}
void Game::Follow_Camera(VECTOR Target) {//�J�����̐ݒ�
	Distance = sqrtf((Target.x - CameraPos.x) * (Target.x - CameraPos.x) + (Target.z - CameraPos.z) * (Target.z - CameraPos.z));
	if (Distance >= Camera_Distance) {
		// �v���C���[�L�����̈ʒu(x,z�j���N�_�Ƀv���C���[�L�����̌����Ǐ]����
		// Camera_Distance�́A�v���C���[�ʒu�������܂ł̋���
		Angle = atan2f(Target.x - CameraPos.x, Target.z - CameraPos.z);
		CameraPos.x = Target.x - sinf(Angle) * Camera_Distance;
		CameraPos.z = Target.z - cosf(Angle) * Camera_Distance;
	}
	CameraPos = VGet(Target.x, Target.y + 3200, Target.z - 2000);
	SetCameraPositionAndAngle(CameraPos, 45.0f, 0.0f, 0.0f);
}
void Game::Area_Update() {
	ALT = VGet(-AreaSceal, M_Array[0]->Position.y, AreaSceal);//�p�̎l�_�ݒ�
	ART = VGet(AreaSceal, M_Array[0]->Position.y, AreaSceal);
	ALB = VGet(-AreaSceal, M_Array[0]->Position.y, -AreaSceal);
	ARB = VGet(AreaSceal, M_Array[0]->Position.y, -AreaSceal);

	if (intersectAABB_Area(AABB(VGet(-MAPLONG * 2 * 10, -1000, -MAPLONG * 2 * 10), VGet(MAPLONG * 2 * 10, 1000, MAPLONG * 2 * 10), VGet(0, 0, 0)), AABB(M_Array[0]->LF, M_Array[0]->RB, M_Array[0]->Position))) {
		AABB(M_Array[0]->LF, M_Array[0]->RB, M_Array[0]->Position).update(M_Array[0]->Position);
	}

	//�X�e�[�W���E�ɒB������ ���˕Ԃ�
	if (M_Array[0]->LF.z >= ALT.z || M_Array[0]->RF.z >= ALT.z)M_Array[0]->Bounce(1);//�O���Փ�
	if (M_Array[0]->LF.z <= ALB.z || M_Array[0]->RF.z <= ALB.z)M_Array[0]->Bounce(1);
	if (M_Array[0]->LF.x <= ALT.x || M_Array[0]->RF.x <= ALT.x)M_Array[0]->Bounce(1);
	if (M_Array[0]->LF.x >= ART.x || M_Array[0]->RF.x >= ART.x)M_Array[0]->Bounce(1);

	if (M_Array[0]->LB.z >= ALT.z || M_Array[0]->RB.z >= ALT.z)M_Array[0]->Bounce(2);//����Փ�
	if (M_Array[0]->LB.z <= ALB.z || M_Array[0]->RB.z <= ALB.z)M_Array[0]->Bounce(2);
	if (M_Array[0]->LB.x <= ALT.x || M_Array[0]->RB.x <= ALT.x)M_Array[0]->Bounce(2);
	if (M_Array[0]->LB.x >= ART.x || M_Array[0]->RB.x >= ART.x)M_Array[0]->Bounce(2);
}
void Game::SearchGrid() {
	for (int i = 0; i < MAPWIDE; i++) {
		for (int j = 0; j < MAPWIDE; j++) {
			if (stage->MapTip[i][j]->Pos.x - MAPLONG <= M_Array[0]->Position.x && stage->MapTip[i][j]->Pos.x + MAPLONG >= M_Array[0]->Position.x)//	�}�V�����ǂ̃}�b�v�`�b�v��ɂ��邩
				MachineGridX = i;
			if (stage->MapTip[i][j]->Pos.z - MAPLONG <= M_Array[0]->Position.z && stage->MapTip[i][j]->Pos.z + MAPLONG >= M_Array[0]->Position.z)
				MachineGridZ = j;
		}
	}
}
void Game::SearchObject(int ObjectNumber) {
	if (VSize(VSub(M_Array[0]->Position, O_Array[ObjectNumber]->ModelPosNavi)) < VSize(VSub(M_Array[0]->Position, Nearest)))//�}�V������Nearest�����ꂽ
		Nearest = O_Array[ObjectNumber]->ModelPosNavi; //Nearest���X�V
	NaviPos = VGet(Nearest.x, Nearest.y + 300, Nearest.z); //�i�r�I�u�W�F�N�g���X�V
	MV1SetPosition(Navi, NaviPos);
}
void Game::CheckHit(int ObjectNumber) {
	if (!O_Array[ObjectNumber]->isHit) {
		if (CheckHit_Square_Point(O_Array[ObjectNumber]->OLU, O_Array[ObjectNumber]->ORU, O_Array[ObjectNumber]->ORD, O_Array[ObjectNumber]->OLD, M_Array[0]->LF))	//�I�u�W�F�N�g��4�_�ƃ}�V���̊p���ڐG
			DeleteObject(ObjectNumber);																																//�I�u�W�F�N�g�폜
		if (CheckHit_Square_Point(O_Array[ObjectNumber]->OLU, O_Array[ObjectNumber]->ORU, O_Array[ObjectNumber]->ORD, O_Array[ObjectNumber]->OLD, M_Array[0]->RF))
			DeleteObject(ObjectNumber);
		if (CheckHit_Square_Point(O_Array[ObjectNumber]->OLU, O_Array[ObjectNumber]->ORU, O_Array[ObjectNumber]->ORD, O_Array[ObjectNumber]->OLD, M_Array[0]->LB))
			M_Array[0]->Bounce(2);																																	//���˕Ԃ���
		if (CheckHit_Square_Point(O_Array[ObjectNumber]->OLU, O_Array[ObjectNumber]->ORU, O_Array[ObjectNumber]->ORD, O_Array[ObjectNumber]->OLD, M_Array[0]->RF))
			M_Array[0]->Bounce(2);
	}
}
void Game::DeleteObject(int ObjectNumber) {
	if (Scene->UseVibration)StartJoypadVibration(1, 750, 500, -1); //�U��
	O_Array[ObjectNumber]->SetAnimation();//�A�j���[�V����������
	O_Array[ObjectNumber]->ModelPosNavi = InvisibilePos;//�I�u�W�F�N�g�������Ȃ��ʒu�ɉB��
	Nearest = InvisibilePos; //�߂��I�u�W�F�N�g�������Ɉړ�
	ObjectNow = ObjectNow - 1;//�I�u�W�F�N�g�����폜
	O_Array[ObjectNumber]->isHit = true;//�q�b�g��Ԃ�
	sound->Sound_Object();//�j�󉹍Đ�
}
bool Game::CheckHit_Square_Point(VECTOR UL, VECTOR UR, VECTOR LR, VECTOR LL, VECTOR Point) { //�l�_����Ȃ�l�p�`�Ɠ_�Ƃ̓����蔻��
	if (UL.z <= Point.z && UR.z <= Point.z)return false;
    if (LL.z >= Point.z && LR.z >= Point.z)return false;
	if (UL.x >= Point.x && LL.x >= Point.x)return false;
	if (UR.x <= Point.x && LR.x <= Point.x)return false;

	return true;
}

void Game::Input_Draw() {//����̕`��

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawBox(0, SizeY - 50, SizeX, SizeY, GetColor(255, 255, 255), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0 || Scene->input.Buttons[12] == 1 || CheckHitKey(KEY_INPUT_W) || Scene->input.ThumbLY > 1.0f)
		if (M_Array[0]->Speed < -0.8f)
			DrawFormatString(0, SizeY - 30, GetColor(255, 0, 0), "�@�@�u���[�L");
		else
			DrawFormatString(0, SizeY - 30, GetColor(255, 0, 0), "�@�@�O�i");
	else
		if (M_Array[0]->Speed < -0.8f)
			DrawFormatString(0, SizeY - 30, GetColor(0, 0, 0), "�@�@�u���[�L");
		else
			DrawFormatString(0, SizeY - 30, GetColor(0, 0, 0), "�@�@�O�i");

	if ((GetMouseInput() & MOUSE_INPUT_RIGHT) != 0 || Scene->input.Buttons[13] == 1 || CheckHitKey(KEY_INPUT_S) || Scene->input.ThumbLY < -1.0f)
		if (M_Array[0]->Speed > 0.8f)
			DrawFormatString(200, SizeY - 30, GetColor(255, 0, 0), "�@�@�u���[�L");
		else
			DrawFormatString(200, SizeY - 30, GetColor(255, 0, 0), "�@�@���");
	else
		if (M_Array[0]->Speed > 0.8f)
			DrawFormatString(200, SizeY - 30, GetColor(0, 0, 0), "�@�@�u���[�L");
		else
			DrawFormatString(200, SizeY - 30, GetColor(0, 0, 0), "�@�@���");


	if (Scene->input.ThumbLX < -1.0f || CheckHitKey(KEY_INPUT_A))
		DrawFormatString(400, SizeY - 30, GetColor(255, 0, 0), "�@�@��");
	else
		DrawFormatString(400, SizeY - 30, GetColor(0, 0, 0), "�@�@��");
	if (Scene->input.ThumbLX > 1.0f || CheckHitKey(KEY_INPUT_D))
		DrawFormatString(600, SizeY - 30, GetColor(255, 0, 0), "�@�@�E");
	else
		DrawFormatString(600, SizeY - 30, GetColor(0, 0, 0), "�@�@�E");

	if (GetJoypadNum() != 0) {
		if (Scene->TypeRadicon) {
			DrawExtendGraph(0, SizeY - 40, 0 + 40, SizeY, KeyGraph[7], true);
			DrawExtendGraph(200, SizeY - 40, 200 + 40, SizeY, KeyGraph[6], true);
		}
		else {
			DrawExtendGraph(0, SizeY - 40, 0 + 40, SizeY, KeyGraph[8], true);
			DrawExtendGraph(200, SizeY - 40, 200 + 40, SizeY, KeyGraph[8], true);
			DrawExtendGraph(400, SizeY - 40, 400 + 40, SizeY, KeyGraph[8], true);
			DrawExtendGraph(600, SizeY - 40, 600 + 40, SizeY, KeyGraph[8], true);
		}
		DrawExtendGraph(400, SizeY - 40, 400 + 40, SizeY, KeyGraph[8], true);
		DrawExtendGraph(600, SizeY - 40, 600 + 40, SizeY, KeyGraph[8], true);
	}
	else {
		if (Scene->TypeRadicon) {
			DrawExtendGraph(0, SizeY - 40, 0 + 40, SizeY, KeyGraph[4], true);
			DrawExtendGraph(200, SizeY - 40, 200 + 40, SizeY, KeyGraph[5], true);
		}
		else {
			DrawExtendGraph(0, SizeY - 40, 0 + 40, SizeY, KeyGraph[0], true);
			DrawExtendGraph(200, SizeY - 40, 200 + 40, SizeY, KeyGraph[2], true);
		}
		DrawExtendGraph(400, SizeY - 40, 400 + 40, SizeY, KeyGraph[1], true);
		DrawExtendGraph(600, SizeY - 40, 600 + 40, SizeY, KeyGraph[3], true);
	}
}

void Game::Game_Count(int phase){//�^�C�}�[�֘A
	if (phase != 2) {
		if (Scene->StartrCount) {
			StartTime = GetNowCount();
			Scene->StartrCount = false;
		}
		Timer = GetNowCount();
	}

	int Time = TimeLimit - (Timer - StartTime);

	int a = Time / 10000;
	int b = (Time / 1000) % 10;
	int c= (Time / 100) % 10;
	int d = (Time / 10) % 10;

	switch (phase) {
	case 0:
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 / (10 - c));
		DrawExtendGraph(SizeX / 2 - 147 / 2, SizeY / 2 - 220 / 2, SizeX / 2 + 147 / 2, SizeY / 2 + 220 / 2, Number[b], true);
		if (TimeLimit <= Timer - StartTime) {
			TimeLimit = 90*1000;
			phase = 1;
			Scene->ChangePhase(Phase::Phase_isScene);
		}
		break;
	case 1:
		DrawExtendGraph(SizeX / 2 - NumGraX / 2 * 2.5 / 2, 0, SizeX / 2 - NumGraX / 2 * 1.5 / 2, NumGraY / 4, Number[a], true);
		DrawExtendGraph(SizeX / 2 - NumGraX / 2 * 1.5 / 2, 0, SizeX / 2 - NumGraX / 2 * 0.5 / 2, NumGraY / 4, Number[b], true);
		DrawExtendGraph(SizeX / 2 - NumGraX / 2 * 0.5 / 2, 0, SizeX / 2 + NumGraX / 2 * 0.5 / 2, NumGraY / 4, Number[10], true);
		DrawExtendGraph(SizeX / 2 + NumGraX / 2 * 0.5 / 2, 0, SizeX / 2 + NumGraX / 2 * 1.5 / 2, NumGraY / 4, Number[c], true);
		DrawExtendGraph(SizeX / 2 + NumGraX / 2 * 1.5 / 2, 0, SizeX / 2 + NumGraX / 2 * 2.5 / 2, NumGraY / 4, Number[d], true);

		if (TimeLimit <= Timer - StartTime) {
			phase = 2;
			stage->ClearFlag = false;

			Scene->ChangePhase(Phase::Phase_isEnd);
		}
		break;
	case 2:

		break;
	}
}