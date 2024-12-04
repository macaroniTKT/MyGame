//���j���[�@�摜�̕\���̂�

#include "Menu.h"
extern SceneMgr* Scene;
extern Sound* sound;
int Cursor;//�I���J�[�\��
int ColorChoice, ColorUnChoice; //�I����Ԃ̕`��J���[
bool Menu_Input = true;
//������
void Menu::Menu_Initialize() {
	sound->Sound_BGM00(true);
	ColorChoice = GetColor(255, 0, 0);
	ColorUnChoice = GetColor(0, 0, 0);

	Cursor = 0;
}

//�X�V
void Menu::Menu_Update() {
	Menu_Draw();

	if (!Menu_Input) {
		if ((CheckHitKey(KEY_INPUT_W) == 1) || (Scene->input.ThumbLY > 1.0f) || (Scene->input.Buttons[0] == 1)) { //�����
			Cursor -= 1; //�J�[�\���A�b�v
			sound->Sound_Cursor(); //�J�[�\���ړ����Đ�
			Menu_Input = true;
		}
		else if ((CheckHitKey(KEY_INPUT_S) == 1) || (Scene->input.ThumbLY < -1.0f) || (Scene->input.Buttons[1] == 1)) { //������
			Cursor += 1; //�J�[�\���_�E��
			sound->Sound_Cursor();
			Menu_Input = true;
		}
	}
	else if (!CheckHitKey(KEY_INPUT_S) && !CheckHitKey(KEY_INPUT_W) && !(Scene->input.ThumbLY > 0.5f) && !(Scene->input.ThumbLY < -0.5f) && !(Scene->input.Buttons[0] == 1) && !(Scene->input.Buttons[1] == 1) && !(Scene->input.Buttons[12] == 1))
		Menu_Input = false;

	if (Cursor > 2)	Cursor = 0;//�J�[�\�������[�v
	if (Cursor < 0)	Cursor = 2;
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	if (!Menu_Input)
		if ((CheckHitKey(KEY_INPUT_SPACE) == 1) || (Scene->input.Buttons[12] == 1) || (Scene->input.Buttons[4] == 1)) {//�G���^�[�L�[��������Ă�����
			switch (Cursor) {
			case 0:
				sound->Sound_BGM00(false);//BGM��~
				if (Scene->UseVibration)StartJoypadVibration(1, 250, 500, -1);//�U��
				sound->Sound_Engine();//�G���W�����Đ�
				Scene->ChangeScene(SceneName::Scene_Game);//�V�[�����Q�[����ʂɕύX
				break;
			case 1:
				sound->Sound_Enter();//�m�艹�Đ�
				Scene->ChangeScene(SceneName::Scene_Config);//�V�[�����Q�[����ʂɕύX
				break;
			case 2:
				sound->Sound_Enter();//�m�艹�Đ�
				DxLib_End();    // DX���C�u�����I������
				break;
			}
		}
}
//�`��
void Menu::Menu_Draw() {
	//SetFontSize(64); DrawString(0, 0, "���j���[", GetColor(0, 0, 0));
	SetFontSize(20);
	DrawString(515, 430, "   -   Start  -   ", ColorUnChoice);//�I�΂�Ă��Ȃ��F
	DrawString(515, 450, "   -  Config  -   ", ColorUnChoice);
	DrawString(515, 470, "   -    End   -   ", ColorUnChoice);

	switch (Cursor) {
	case 0:
		DrawString(515, 430, "   -   Start  -   ", ColorChoice);//�I������Ă���Ȃ�F��ύX���ĕ`��
		break;
	case 1:
		DrawString(515, 450, "   -  Config  -   ", ColorChoice);
		break;
	case 2:
		DrawString(515, 470, "   -    End   -   ", ColorChoice);
		break;
	}
}

//�I������
void Menu::Menu_Finalize() {
}