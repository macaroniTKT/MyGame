#pragma once
#include"DxLib.h"
#include"Title.h"
#include"Menu.h"
#include"Config.h"
#include"Game.h"
#include"Clear.h"


const int SizeX = 1200;
const int SizeY = 800;

enum class SceneName {
	Scene_Title,
	Scene_Menu,
	Scene_Config,
	Scene_Game,
	Scene_Clear,
	Scene_None,    //����
};

enum class Phase {
	Phase_isStart,
	Phase_isScene,
	Phase_isEnd,
};
enum class Fade {
	Fade_Open,
	Fade_isOpen,
	Fade_Close,
};

class SceneMgr {
public:

	bool StartrCount = false;

	int MouseX = 0, MouseY = 0;
	XINPUT_STATE input;
	bool TypeRadicon=true;
	bool UseVibration = true; //�U���@�\

	void SceneMgr_Initialize();//������
	void SceneMgr_Finalize();//�I������
	void SceneMgr_Update();//�X�V

	void SceneMgr_InitializeModule(SceneName Scene);//�w�胂�W���[��������������
	void SceneMgr_FinalizeModule(SceneName Scene);//�w�胂�W���[���̏I���������s��

	// ���� NextScene �ɃV�[����ύX����
	void ChangeScene(SceneName NextScene);

	void ChangePhase(Phase NextPhase);
};