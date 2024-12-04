//�^�C�g���@�摜�̕\���̂�

#include "Title.h"
extern SceneMgr* Scene;
extern Sound* sound;

int T_Logo0, T_Logo1, T_Logo2;//�摜�ǂݍ���
float T_GraphAngle;//�摜�̉�]�l

int PV; //PV�ǂݍ���
int Fade; //����
int FadeFlag; //���ߏ��
int SecondNow, SecondPV; //PV�̍Đ��ҋ@����,�Đ�����


//������
void Title::Title_Initialize() {
	T_Logo0 = LoadGraph("Asset/Logo02.png"); //�摜�ǂݍ���
	T_Logo1 = LoadGraph("Asset/Logo03.png");
	T_Logo2 = LoadGraph("Asset/Logo01.png");
	PV = LoadGraph("Asset/PV.mp4"); //PV�ǂݍ���
}

//�X�V
void Title::Title_Update() {
	if (!GetMovieStateToGraph(PV))SecondNow += 1;//PV��~���Ȃ烀�[�r�[�R�}�����i�߂�
	sound->Sound_BGM00(true);//BGM(BGM00)���Đ�
	T_GraphAngle -= 0.01f; //�摜����]������@
	if (T_GraphAngle > 0)T_GraphAngle = 360;

	Title_Draw();

	if ((CheckHitKey(KEY_INPUT_SPACE) == 1) || (Scene->input.Buttons[4] == 1)) {//����L�[��������Ă�����
		WaitTimer(100);
		if (!GetMovieStateToGraph(PV))Scene->ChangeScene(SceneName::Scene_Menu);//PV��~���Ȃ�V�[�������j���[��ʂɕύX
		else {
			PauseMovieToGraph(PV);//�Đ����~
			SecondNow = 0; //�Đ��ҋ@���Ԃ����Z�b�g
			SecondPV = 0; //�Đ����Ԃ����Z�b�g
			sound->Sound_BGM00(true); //BGM�Đ�
		}
	}

	if (FadeFlag)Fade += 5;//���ߏ�Ԃɂ���ē��߂Ɖ���
	else Fade -= 5;

	if (Fade >= 255)FadeFlag = false;//���ߐi�s�̐؂�ւ�
	if (Fade <= 0)FadeFlag = true;

	if (SecondNow >= 30 * 60) { //�ҋ@���Ԃ� 30(*60)�b�𒴉�
		SecondNow = 0; //���Z�b�g
		sound->Sound_BGM00(false); //BGM���~
		if (!GetMovieStateToGraph(PV)) {//PV�Đ����łȂ�

			SeekMovieToGraph(PV, 0);//�Đ������߂����
			SecondPV += 1; //�Đ��R�}����
			PlayMovieToGraph(PV); //�Đ�
		}
		if (SecondPV >= 45 * 60) { //�ҋ@����(���ݍĐ���)�� 45(*60)�b�𒴉�

			PauseMovieToGraph(PV);//��~
			SecondPV = 0;//���Z�b�g
			sound->Sound_BGM00(true);//BGM�Đ�
		}
	}
}

//�`��
void Title::Title_Draw() {
	if (!GetMovieStateToGraph(PV)) { //PV��ԂłȂ�

		DrawRotaGraph2(SizeX / 2, SizeY / 2 - 100, 250, 250, 0.6f, T_GraphAngle, T_Logo0, TRUE);//��]�l�ŕ`��
		DrawRotaGraph2(SizeX / 2, SizeY / 2 - 100, 250, 250, 0.6f, 0, T_Logo1, TRUE);
		DrawRotaGraph2(SizeX / 2, SizeY / 2 - 100, 250, 250, 0.6f, 0, T_Logo2, TRUE);
		SetFontSize(20);

		if (GetJoypadNum() != 0)
			DrawString(500, 470, "-Pless Start Botton-", GetColor(Fade, Fade, Fade)); //���ߓx�ŕ`��
		else
			DrawString(515, 470, "-Pless Space Key-", GetColor(Fade, Fade, Fade)); //���ߓx�ŕ`��
	}
	else {
		DrawExtendGraph(0, 0, SizeX, SizeY, PV, FALSE);//PV�`��
		WaitTimer(10); 
	}
}

//�I������
void Title::Title_Finalize() {
}