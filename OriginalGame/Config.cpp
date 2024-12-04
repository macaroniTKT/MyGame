#include"Config.h"
extern SceneMgr* Scene;
extern Sound* sound;

int ColorTrue, ColorFalse,ColorNoPad;//�ݒ荀�ڂ̕`��J���[
int ConfigChoice = GetColor(255, 0, 0), ConfigUnChoice = GetColor(0, 0, 0);//�I����Ԃ̕`��J���[
int ConfigCursorMenu; //���ڂ̑I���J�[�\��
const int ConfigCursorMax=2; //�I�����Ƃ̍��ڐ�
int ConfigCursor[ConfigCursorMax];//�z��Ƃ��Ċi�[

void Config::Config_Initialize() {//������
	ConfigCursor[0] = 1;//�J�[�\�������l
	ConfigCursorMenu= 0;//�J�[�\�������l

	ColorTrue = GetColor(255, 0, 0);//�ݒ�ł̃J���[�ݒ�
	ColorFalse = GetColor(0, 0, 0);
	ColorNoPad = GetColor(200, 200, 200);
	WaitTimer(100);
}
void Config::Config_Finalize() {//�I������
}
void Config::Config_Update() {//�X�V
	Config_Draw();
	Config_Select();
	if ((CheckHitKey(KEY_INPUT_W) == 1) || (Scene->input.Buttons[0] == 1) || (Scene->input.ThumbLY > 1.0f)) {//�����
		ConfigCursorMenu -= 1;//�J�[�\���A�b�v
		if(GetJoypadNum() == 0)ConfigCursorMenu -= 1;//�R���g���[���[�ڑ����Ȃ��Ȃ�X�L�b�v
		WaitTimer(150);
	}
	else if ((CheckHitKey(KEY_INPUT_S) == 1) || (Scene->input.Buttons[1] == 1) || (Scene->input.ThumbLY < -1.0f)) { //������
		ConfigCursorMenu += 1;//�J�[�\���_�E��
		if (GetJoypadNum() == 0)ConfigCursorMenu += 1;//�R���g���[���[�ڑ����Ȃ��Ȃ�X�L�b�v
		WaitTimer(150);
	}

	if (ConfigCursor[0] > 1)ConfigCursor[0] = 0;//�J�[�\�����[�v
	if (ConfigCursor[0] < 0)ConfigCursor[0] = 1;
	if (ConfigCursor[1] > 1)ConfigCursor[1] = 0;
	if (ConfigCursor[1] < 0)ConfigCursor[1] = 1;

	if (ConfigCursorMenu > ConfigCursorMax)ConfigCursorMenu = 0;//�J�[�\�����[�v
	if (ConfigCursorMenu < 0)ConfigCursorMenu = ConfigCursorMax;
}
void Config::Config_Select() {

	if (ConfigCursorMenu != ConfigCursorMax) {
		if ((CheckHitKey(KEY_INPUT_D) == 1) || (Scene->input.Buttons[3] == 1) || (Scene->input.ThumbLX > 1.0f)) {//������
			ConfigCursor[ConfigCursorMenu] += 1;
			sound->Sound_Cursor(); //�J�[�\���ړ����Đ�
			WaitTimer(150);
		}
		else if ((CheckHitKey(KEY_INPUT_A) == 1) || (Scene->input.Buttons[2] == 1) || (Scene->input.ThumbLX < -1.0f)) {//�E����
			ConfigCursor[ConfigCursorMenu] -= 1;
			sound->Sound_Cursor();
			WaitTimer(150);
		}
	}
	else 
		if ((CheckHitKey(KEY_INPUT_SPACE) == 1) || (Scene->input.Buttons[12] == 1)) {
			sound->Sound_Enter(); //�m�艹�Đ�
			WaitTimer(100); Scene->ChangeScene(SceneName::Scene_Menu);//�V�[�������j���[��ʂɕύX
		}

	switch (ConfigCursor[0]) { //����^�C�v�؂�ւ�
	case 0:
		Scene->TypeRadicon = false;
		break;
	case 1:
		Scene->TypeRadicon = true;
		break;
	}
	switch (ConfigCursor[1]) { //�U���@�\�̗L��
	case 0:
		Scene->UseVibration = true;
		break;
	case 1:
		Scene->UseVibration = false;
		break;
	}
}

void Config::Config_Draw() {//�`��
	SetFontSize(64); DrawString(0, 0, "�ݒ�", GetColor(0, 0, 0));
	SetFontSize(20);

	DrawString(315, 430, "����^�C�v�@�@�@�@", ConfigUnChoice);//�I�΂�Ă��Ȃ��F
	if (GetJoypadNum() != 0) {
		DrawString(315, 450, "�R���g���[���[�U��", ConfigUnChoice);
	}
	else {
		DrawString(315, 450, "�R���g���[���[�U��", ColorNoPad);//�R���g���[���[�ڑ����Ȃ���ΕʐF�ɂ���
	}
	DrawString(515, 500, "���j���[�ɖ߂�", ConfigUnChoice);

	switch (ConfigCursorMenu)
	{
	case 0:
		DrawString(315, 430, "����^�C�v�@�@�@�@", ConfigChoice);//�I������Ă���Ȃ�F��ύX���ĕ`��
		break;
	case 1:
		if (GetJoypadNum() != 0) {
			DrawString(315, 450, "�R���g���[���[�U��", ConfigChoice);
		}
		else {
			DrawString(315, 450, "�R���g���[���[�U��", ColorNoPad);
		}
		break;
	case ConfigCursorMax:
		DrawString(515, 500, "���j���[�ɖ߂�", ConfigChoice);
		break;
	}

	if (!Scene->TypeRadicon) {
		DrawString(515, 430, "�m�[�}���@�@�@�@�@", ColorTrue);	DrawString(515, 430, "�@�@�@�@�@���W�R��", ColorFalse);
	}
	else {
		DrawString(515, 430, "�m�[�}���@�@�@�@�@", ColorFalse);	DrawString(515, 430, "�@�@�@�@�@���W�R��", ColorTrue);
	}
	if (GetJoypadNum() != 0) {
		if (Scene->UseVibration) {
			DrawString(515, 450, "   ON   �@�@�@�@�@", ColorTrue);	DrawString(515, 450, "�@�@�@�@�@  OFF   ", ColorFalse);
		}
		else {
			DrawString(515, 450, "   ON   �@�@�@�@�@", ColorFalse);	DrawString(515, 450, "�@�@�@�@�@  OFF   ", ColorTrue);
		}
	}
	else {
		DrawString(515, 450, "   ON   �@�@�@�@�@", ColorNoPad);	DrawString(515, 450, "�@�@�@�@�@  OFF   ", ColorNoPad);
	}
}