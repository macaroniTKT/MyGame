#pragma once
#include "DxLib.h"
#include "SceneManager.h"

const float MAPLONG = 500;//�}�b�v��
const int MAPWIDE_F = 10;
const int MAPWIDE = MAPWIDE_F * 2 - 1;//�}�b�v�O���b�h��
#define DefaltHeight MAPLONG/5//���፷�
class Stage {
private:
public:
	int i, j;
	class MapObject* MapTip[MAPWIDE][MAPWIDE];

	void Initialize();//�J�n
	void Finalize();//�I��
	void Update();
	void Draw();//�`��
	void Check();//
	void StageFinish(float Timer);//�X�e�[�W�N���A�`��
	void MapCreate();//�S�̃}�b�v����
	void MapJudge();//�}�b�v�`�b�v���ϊ�
	void MapCreateSlope(int R, int M, int H, int TF);//�X�����������}�b�v�`�b�v����
	void LoadMapModel();//���f���ǂݍ���

	float DirMachine;//�}�b�v�`�b�v��̃}�V�����f���̑��Έʒu�p�x

	int CheckArea(int x, int y, VECTOR Machine);//�}�V���Ƃ̑��Έʒu�ƌX��

	bool ClearFlag = false;//�Q�[���N���A����

	//�}�b�v�����p
	int X, Z;
	int MapF[MAPWIDE_F][MAPWIDE_F];
	int MapA[MAPWIDE][MAPWIDE];

	//���f�����ʗp
	int JudgeNL[4];
	int JudgeN = 0;
};

class MapObject{
private: 

protected:

public:
	VECTOR Pos;    //�����ʒu
	VECTOR MLT,MRT,MLB,MRB;//�p�̎l�_---MapTipLeftTop,MapTipRightBottom
	VECTOR Center;
	int HeightList[4];//�p�̎l�_�̍����w��
	int Rotation;  //���f���̉�]�l
	int Model;     //���f���ǂݍ���
	int Height;	//�����w��
	bool Bool; //���፷�ω��̗L��

	virtual void Finalize() = 0;//�I��
	virtual void StageSet(int X, int Y, int Rot, int ModelNum, int High) = 0;//����

	virtual void Draw(int X,int Y) = 0;//�`��
};

class Map : public MapObject{
	bool CameraClip(VECTOR pos1, VECTOR pos2, VECTOR pos3, VECTOR pos4);//�J�������O����
	void Finalize();
	void StageSet(int X, int Y, int Rot, int ModelNum, int High);
	void Draw(int X, int Y);
};