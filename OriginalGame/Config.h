#pragma once
#include "SceneManager.h"
#include "DxLib.h"

class Config {
public:
	void Config_Initialize();//������
	void Config_Finalize();//�I������
	void Config_Update();//�X�V
	void Config_Select();
	void Config_Draw();//�`��
};