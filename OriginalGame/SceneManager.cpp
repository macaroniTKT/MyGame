//�S�ẴV�[���ϑJ���Ǘ�����

#include "SceneManager.h"


static SceneName nowScene = SceneName::Scene_Title; // ���V�[���̊Ǘ��ϐ�
static SceneName nextScene = SceneName::Scene_None; //���̃V�[���Ǘ��ϐ�
static Phase phase = Phase::Phase_isStart;
static Fade fade = Fade::Fade_Open;



extern SceneMgr* Scene;

extern Title* SC_tit;
extern Menu* SC_men;
extern Config* SC_con;
extern Game* SC_gam;
extern Clear* SC_cle;

int SceneAlpha = 255;

//������
void SceneMgr::SceneMgr_Initialize() {
	SceneMgr_InitializeModule(nowScene);
}

//�V�[���̍X�V
void SceneMgr::SceneMgr_Update() {
	if (SceneAlpha > 255)
	if (nextScene != SceneName::Scene_None) {    //���̃V�[�����Z�b�g����Ă�����
		SceneMgr_FinalizeModule(nowScene); //���݂̃V�[���̏I�����������s
		nowScene = nextScene;    //���̃V�[�������݂̃V�[���Z�b�g
		nextScene = SceneName::Scene_None;    //���̃V�[�������N���A
		SceneMgr_InitializeModule(nowScene);    //���݂̃V�[����������
	}

	//���݂̃V�[���ɂ���ď����𕪊�
	switch (nowScene) {
	case SceneName::Scene_Title:
		SC_tit->Title_Update();
		break;
	case SceneName::Scene_Menu:
		SC_men->Menu_Update();
		break;
	case SceneName::Scene_Config:
		SC_con->Config_Update();
		break;
	case SceneName::Scene_Game:
		switch (phase) {
		case Phase::Phase_isStart:
			SC_gam->Game_Standby();
			break;
		case Phase::Phase_isScene:
			SC_gam->Game_Update();
			break;
		case Phase::Phase_isEnd:
			SC_gam->Game_End();
			break;
		}
		break;
	case SceneName::Scene_Clear:
		SC_cle->Clear_Update();
		break;
	default:
		break;
	}
	GetJoypadXInputState(DX_INPUT_PAD1, &Scene->input);

	//�V�[���؂�ւ����̃t�F�[�h
	switch (fade) {
	case Fade::Fade_Open:
		SceneAlpha -= 5;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, SceneAlpha);
		DrawBox(0, 0, SizeX, SizeY, GetColor(0, 0, 0), true);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
		break;
	case Fade::Fade_isOpen:

		break;
	case Fade::Fade_Close:
		SceneAlpha += 5;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, SceneAlpha);
		DrawBox(0, 0, SizeX, SizeY, GetColor(0, 0, 0), true);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
		break;
	}
}
// ���� nextScene �̃V�[����ύX����
void SceneMgr::ChangeScene(SceneName NextScene) {
	if (nextScene == SceneName::Scene_None) {    //���̃V�[�����Z�b�g����Ă�����
		fade = Fade::Fade_Close;
		SceneAlpha = 0;
		nextScene = NextScene;    //���̃V�[�����Z�b�g����
	}
}

// ���� nextPhase �̃V�[����ύX����
void SceneMgr::ChangePhase(Phase NextPhase) {
	SceneAlpha = 0;
	phase = NextPhase;    //���̃V�[�����Z�b�g����
	StartrCount = true;
}

//�I������
void SceneMgr::SceneMgr_Finalize() {
	SceneMgr_FinalizeModule(nowScene);
}

// ����Scene���W���[��������������
void SceneMgr::SceneMgr_InitializeModule(SceneName Scene) {
	SceneAlpha = 255;
	fade = Fade::Fade_Open;
	switch (Scene) {          //�V�[���ɂ���ď����𕪊�
	case SceneName::Scene_Title:       //�w���ʂ�***��ʂȂ�
		SC_tit->Title_Initialize();  //***��ʂ̏���������������
		break;
	case SceneName::Scene_Menu:
		SC_men->Menu_Initialize();
		break;
	case SceneName::Scene_Config:
		SC_con->Config_Initialize();
		break;
	case SceneName::Scene_Game:
		SC_gam->Game_Initialize();
		StartrCount = true;
		break;
	case SceneName::Scene_Clear:
		SC_cle->Clear_Initialize();
		break;
	}
}

// ����Scene���W���[���̏I���������s��
 void SceneMgr::SceneMgr_FinalizeModule(SceneName Scene) {
	 switch (Scene) {         //�V�[���ɂ���ď����𕪊�
	 case SceneName::Scene_Title:      //�w���ʂ�***��ʂȂ�
		 SC_tit->Title_Finalize();   //***��ʂ̏I����������������
		 break;
	 case SceneName::Scene_Menu:
		 SC_men->Menu_Finalize();
		 break;
	 case SceneName::Scene_Config:
		 SC_con->Config_Finalize();
		 break;
	 case SceneName::Scene_Game:
		 SC_gam->Game_Finalize();
		 break;
	 case SceneName::Scene_Clear:
		 SC_cle->Clear_Finalize();
		 break;
	 }
 }