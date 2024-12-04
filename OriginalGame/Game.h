#pragma once
#include "SceneManager.h"
#include "DxLib.h"
#include"Machine.h"
#include"Stage.h"
#include"Object.h"
#include"Effect.h"
#include"AABB.h"
#include"Sound.h"

class Game {
public:

	void Game_Initialize();//������
	void Game_Finalize();//�I������


	void Game_Standby();//�J�n�܂�
	void Game_Update();//�Q�[����
	void Game_End();//�I���܂�

	void LoadGraphs();//�摜�ǂݍ���
	void Game_Count(int phase);//�^�C�}�[�֘A
	void EffectSet();//
	void Game_Draw();//�`��
	void Input_Draw();//����̕`��

	void CheckHit(int ObjectNumber);//�}�V���ƃI�u�W�F�N�g�̃q�b�g
	void DeleteObject(int ObjectNumber);//�I�u�W�F�N�g�j��
	void Follow_Camera(VECTOR Tatget);//�J�����ǔ�
	void Area_Update();//�X�e�[�W���E����
	void SearchGrid();//�X�e�[�W��̃}�V���̍��W�擾
	void SearchObject(int ObjectNumber);//�}�V���Ƌ߂��I�u�W�F�N�g�̔���
	bool CheckHit_Square_Point(VECTOR UL, VECTOR UR, VECTOR LR, VECTOR LL, VECTOR Point);//�l�p�`�Ɠ_�̓����蔻��
};