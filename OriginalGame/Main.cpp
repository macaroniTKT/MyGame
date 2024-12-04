//���C��
#include "Define.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(true); // Window���[�h
	SetGraphMode(SizeX, SizeY, 32);    // ��ʃT�C�Y�̐ݒ�

	// �c�w���C�u��������������
	if (DxLib_Init() == -1) return -1;        // �G���[���N�����璼���ɏI��

	//�`���𗠉�ʂɂ���
	SetDrawScreen(DX_SCREEN_BACK);
	SetLightAmbColor(GetColorF(1.0f, 1.0f, 1.0f, 1.0f));
	SetUseLighting(true);

	Scene = new SceneMgr;
	Scene->SceneMgr_Initialize();
	sound = new Sound;
	sound->Sound_Initialize();

	// while(����ʂ�\��ʂɔ��f, ���b�Z�[�W����, ��ʃN���A)
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		DrawBox(0, 0, SizeX, SizeY, GetColor(255, 255, 255), true);    // �w�i

		Scene->SceneMgr_Update();

		//�����I���L�[
		if (CheckHitKey(KEY_INPUT_ESCAPE) > 0) {
			break;
		}

	}
	Scene->SceneMgr_Finalize();//�Q�[�����Ǘ��̏I������

	delete Scene;

	DxLib_End();    // DX���C�u�����I������
	return 0;
}