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
	Scene_None,    //無し
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
	bool UseVibration = true; //振動機能

	void SceneMgr_Initialize();//初期化
	void SceneMgr_Finalize();//終了処理
	void SceneMgr_Update();//更新

	void SceneMgr_InitializeModule(SceneName Scene);//指定モジュールを初期化する
	void SceneMgr_FinalizeModule(SceneName Scene);//指定モジュールの終了処理を行う

	// 引数 NextScene にシーンを変更する
	void ChangeScene(SceneName NextScene);

	void ChangePhase(Phase NextPhase);
};