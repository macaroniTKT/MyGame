#pragma once
#include"DxLib.h"

class Sound {
private:
	int Object;//�T�E���h�f�[�^�ǂݍ���
	int Engine;
	int Cursor;
	int Enter;
	int BGM00;
	int BGM01;
public:
	void Sound_Initialize();//������

	void Sound_Engine(); //�G���W�����Đ�
	void Sound_Object(); //�I�u�W�F�N�g�j�󉹍Đ�
	void Sound_Cursor(); //�J�[�\���ړ����Đ�
	void Sound_Enter();  //���艹�Đ�
	void Sound_BGM00(bool TF);//BGM�Đ�(false�Œ�~)
	void Sound_BGM01(bool TF);
};