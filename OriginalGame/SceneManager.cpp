//全てのシーン変遷を管理する

#include "SceneManager.h"


static SceneName nowScene = SceneName::Scene_Title; // 現シーンの管理変数
static SceneName nextScene = SceneName::Scene_None; //次のシーン管理変数
static Phase phase = Phase::Phase_isStart;
static Fade fade = Fade::Fade_Open;



extern SceneMgr* Scene;

extern Title* SC_tit;
extern Menu* SC_men;
extern Config* SC_con;
extern Game* SC_gam;
extern Clear* SC_cle;

int SceneAlpha = 255;

//初期化
void SceneMgr::SceneMgr_Initialize() {
	SceneMgr_InitializeModule(nowScene);
}

//シーンの更新
void SceneMgr::SceneMgr_Update() {
	if (SceneAlpha > 255)
	if (nextScene != SceneName::Scene_None) {    //次のシーンがセットされていたら
		SceneMgr_FinalizeModule(nowScene); //現在のシーンの終了処理を実行
		nowScene = nextScene;    //次のシーンを現在のシーンセット
		nextScene = SceneName::Scene_None;    //次のシーン情報をクリア
		SceneMgr_InitializeModule(nowScene);    //現在のシーンを初期化
	}

	//現在のシーンによって処理を分岐
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

	//シーン切り替え時のフェード
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
// 引数 nextScene のシーンを変更する
void SceneMgr::ChangeScene(SceneName NextScene) {
	if (nextScene == SceneName::Scene_None) {    //次のシーンがセットされていたら
		fade = Fade::Fade_Close;
		SceneAlpha = 0;
		nextScene = NextScene;    //次のシーンをセットする
	}
}

// 引数 nextPhase のシーンを変更する
void SceneMgr::ChangePhase(Phase NextPhase) {
	SceneAlpha = 0;
	phase = NextPhase;    //次のシーンをセットする
	StartrCount = true;
}

//終了処理
void SceneMgr::SceneMgr_Finalize() {
	SceneMgr_FinalizeModule(nowScene);
}

// 引数Sceneモジュールを初期化する
void SceneMgr::SceneMgr_InitializeModule(SceneName Scene) {
	SceneAlpha = 255;
	fade = Fade::Fade_Open;
	switch (Scene) {          //シーンによって処理を分岐
	case SceneName::Scene_Title:       //指定画面が***画面なら
		SC_tit->Title_Initialize();  //***画面の初期化処理をする
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

// 引数Sceneモジュールの終了処理を行う
 void SceneMgr::SceneMgr_FinalizeModule(SceneName Scene) {
	 switch (Scene) {         //シーンによって処理を分岐
	 case SceneName::Scene_Title:      //指定画面が***画面なら
		 SC_tit->Title_Finalize();   //***画面の終了処理処理をする
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