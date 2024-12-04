#include"Sound.h"

void Sound::Sound_Initialize() {
	Object = LoadSoundMem("Asset/Sound/Object.mp3");//�T�E���h�f�[�^�ǂݍ���
	Engine = LoadSoundMem("Asset/Sound/Engine.mp3");
	Cursor = LoadSoundMem("Asset/Sound/Cursor.mp3");
	Enter = LoadSoundMem("Asset/Sound/Enter.mp3");
	BGM00 = LoadSoundMem("Asset/Sound/Music00.mp3");
	BGM01 = LoadSoundMem("Asset/Sound/Music01.mp3");
}
void Sound::Sound_Object() {
	PlaySoundMem(Object, DX_PLAYTYPE_BACK);//�T�E���h�Đ�(�o�b�N�O���E���h�Đ�)
}
void Sound::Sound_Engine() {
	PlaySoundMem(Engine, DX_PLAYTYPE_BACK);
}
void Sound::Sound_Cursor() {
	PlaySoundMem(Cursor, DX_PLAYTYPE_BACK);
}
void Sound::Sound_Enter() {
	PlaySoundMem(Enter, DX_PLAYTYPE_NORMAL);
}
void Sound::Sound_BGM00(bool TF) {
	if (TF) {
		if (!CheckSoundMem(BGM00)) {//������BGM���Ȃ��Ă��Ȃ�
			ChangeVolumeSoundMem(255 * 40 / 100, BGM00);//���ʐݒ�
			PlaySoundMem(BGM00, DX_PLAYTYPE_BACK);
		}
	}
	else {
		if (CheckSoundMem(BGM00))
			StopSoundMem(BGM00);
	}
}
void Sound::Sound_BGM01(bool TF) {
	if (TF) {
		if (!CheckSoundMem(BGM01)) {
			ChangeVolumeSoundMem(255 * 40 / 100, BGM01);
			PlaySoundMem(BGM01, DX_PLAYTYPE_BACK);
		}
	}
	else {
		if (CheckSoundMem(BGM01)) {
			StopSoundMem(BGM01);
		}
	}
}