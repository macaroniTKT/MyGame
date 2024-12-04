#pragma once
#include "DxLib.h"
#include "Stage.h"
class Object {
public:
	VECTOR Scale;//���f���̃T�C�Y
	VECTOR ModelPos, ModelPosNavi;
	VECTOR OLU,ORU,OLD,ORD;//�p�̎l�_---ObjectLeftUp,ObjectRightDown
	int Building,Debri;//�r���{�� , ��ꂽ�r���̌���
	int AnimAttachIndexB, AnimAttachIndexD;//�A�j���[�V������--AnimationAttachIndexBuilding,AnimationAttachIndexDebri
	float  AnimTotalTime;//�A�j���[�V����������
	float  AnimNowTime;//�A�j���[�V����	�o�ߎ���
	bool isHit;//�I�u�W�F�N�g�q�b�g���
	bool CameraClip(VECTOR pos1, VECTOR pos2, VECTOR pos3, VECTOR pos4);//�J�������O����

	virtual void Initialize() = 0;//�J�n
	virtual void Finalize() = 0;//�I��
	virtual void Update() = 0;//
	virtual void Draw() = 0;//�`��

	//�A�j���[�V��������
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