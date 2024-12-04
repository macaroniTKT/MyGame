#include"Clear.h"

extern SceneMgr* Scene;
extern Sound* sound;

int C_Logo0, C_Logo1, C_Logo2; //�摜�ǂݍ���
float C_GraphAngle; //�摜�̉�]�l
int C_Cursor; //�I���J�[�\��
int C_ColorUnChoice = GetColor(0, 0, 0), C_ColorChoice = GetColor(255, 0, 0); //�I����Ԃ̕`��J���[


//������
void Clear::Clear_Initialize() {
	C_Logo0 = LoadGraph("Asset/Logo02.png");//�摜�ǂݍ���
	C_Logo1 = LoadGraph("Asset/Logo03.png");
	C_Logo2 = LoadGraph("Asset/Logo01.png");
}

//�X�V
void Clear::Clear_Update() {
	sound->Sound_BGM00(true);//BGM�Đ�
	C_GraphAngle -= 0.01f;//�摜����]������
	if (C_GraphAngle > 0)C_GraphAngle = 360;
	Clear_Draw();

	if ((CheckHitKey(KEY_INPUT_W) == 1) || (Scene->input.ThumbLY > 1.0f) || (Scene->input.Buttons[0] == 1)) {//�����
		C_Cursor -= 1;//�J�[�\���A�b�v
		sound->Sound_Cursor();//�J�[�\���ړ���
		WaitTimer(150);
	}
	else if ((CheckHitKey(KEY_INPUT_S) == 1) || (Scene->input.ThumbLY < -1.0f) || (Scene->input.Buttons[1] == 1)) { //������
		C_Cursor += 1;//�J�[�\���_�E��
		sound->Sound_Cursor();
		WaitTimer(150);
	}

	if (C_Cursor > 2)	C_Cursor = 0; //�J�[�\�����[�v
	if (C_Cursor < 0)	C_Cursor = 2;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	if ((CheckHitKey(KEY_INPUT_SPACE) == 1) || (Scene->input.Buttons[12] == 1) || (Scene->input.Buttons[4] == 1)) {//����L�[��������Ă�����
		switch (C_Cursor) {
		case 0:
			sound->Sound_BGM00(false);//BGM���~
			if (Scene->UseVibration)StartJoypadVibration(1, 250, 500, -1);//�U��
			sound->Sound_Engine();//�G���W�����Đ�
			Scene->ChangeScene(SceneName::Scene_Game);//�V�[�����Q�[����ʂɕύX
			break;
		case 1:
			sound->Sound_Enter();//�m�艹�Đ�
			Scene->ChangeScene(SceneName::Scene_Config);//�V�[�����Q�[����ʂɕύX
			break;
		case 2:
			sound->Sound_Enter();
			DxLib_End();    // DX���C�u�����I������
			break;
		}
	}
}

//�`��
void Clear::Clear_Draw() {
	DrawRotaGraph2(SizeX / 2, SizeY / 2 - 100, 250, 250, 0.6f, C_GraphAngle, C_Logo0, TRUE);//��]�l�ŕ`��
	DrawRotaGraph2(SizeX / 2, SizeY / 2 - 100, 250, 250, 0.6f, 0, C_Logo1, TRUE);
	DrawRotaGraph2(SizeX / 2, SizeY / 2 - 100, 250, 250, 0.6f, 0, C_Logo2, TRUE);

	SetFontSize(20);
	DrawString(515, 490, "   -  ReStart -   ", C_ColorUnChoice);//�I�΂�Ă��Ȃ��F
	DrawString(515, 510, "   -  Config  -   ", C_ColorUnChoice);
	DrawString(515, 530, "   -    End   -   ", C_ColorUnChoice);

	switch (C_Cursor) {
	case 0:
		DrawString(515, 490, "   -  ReStart -   ", C_ColorChoice);//�I������Ă���Ȃ�F��ύX���ĕ`��
		break;
	case 1:
		DrawString(515, 510, "   -  Config  -   ", C_ColorChoice);
		break;
	case 2:
		DrawString(515, 530, "   -    End   -   ", C_ColorChoice);
		break;
	}
}

//�I������
void Clear::Clear_Finalize() {
}