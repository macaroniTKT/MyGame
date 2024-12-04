//タイトル　画像の表示のみ

#include "Title.h"
extern SceneMgr* Scene;
extern Sound* sound;

int T_Logo0, T_Logo1, T_Logo2;//画像読み込み
float T_GraphAngle;//画像の回転値

int PV; //PV読み込み
int Fade; //透過
int FadeFlag; //透過状態
int SecondNow, SecondPV; //PVの再生待機時間,再生時間


//初期化
void Title::Title_Initialize() {
	T_Logo0 = LoadGraph("Asset/Logo02.png"); //画像読み込み
	T_Logo1 = LoadGraph("Asset/Logo03.png");
	T_Logo2 = LoadGraph("Asset/Logo01.png");
	PV = LoadGraph("Asset/PV.mp4"); //PV読み込み
}

//更新
void Title::Title_Update() {
	if (!GetMovieStateToGraph(PV))SecondNow += 1;//PV停止中ならムービーコマ送りを進める
	sound->Sound_BGM00(true);//BGM(BGM00)を再生
	T_GraphAngle -= 0.01f; //画像を回転させる　
	if (T_GraphAngle > 0)T_GraphAngle = 360;

	Title_Draw();

	if ((CheckHitKey(KEY_INPUT_SPACE) == 1) || (Scene->input.Buttons[4] == 1)) {//決定キーが押されていたら
		WaitTimer(100);
		if (!GetMovieStateToGraph(PV))Scene->ChangeScene(SceneName::Scene_Menu);//PV停止中ならシーンをメニュー画面に変更
		else {
			PauseMovieToGraph(PV);//再生を停止
			SecondNow = 0; //再生待機時間をリセット
			SecondPV = 0; //再生時間をリセット
			sound->Sound_BGM00(true); //BGM再生
		}
	}

	if (FadeFlag)Fade += 5;//透過状態によって透過と可視化
	else Fade -= 5;

	if (Fade >= 255)FadeFlag = false;//透過進行の切り替え
	if (Fade <= 0)FadeFlag = true;

	if (SecondNow >= 30 * 60) { //待機時間が 30(*60)秒を超過
		SecondNow = 0; //リセット
		sound->Sound_BGM00(false); //BGMを停止
		if (!GetMovieStateToGraph(PV)) {//PV再生中でない

			SeekMovieToGraph(PV, 0);//再生を初めからに
			SecondPV += 1; //再生コマ送り
			PlayMovieToGraph(PV); //再生
		}
		if (SecondPV >= 45 * 60) { //待機時間(現在再生中)が 45(*60)秒を超過

			PauseMovieToGraph(PV);//停止
			SecondPV = 0;//リセット
			sound->Sound_BGM00(true);//BGM再生
		}
	}
}

//描画
void Title::Title_Draw() {
	if (!GetMovieStateToGraph(PV)) { //PV状態でない

		DrawRotaGraph2(SizeX / 2, SizeY / 2 - 100, 250, 250, 0.6f, T_GraphAngle, T_Logo0, TRUE);//回転値で描画
		DrawRotaGraph2(SizeX / 2, SizeY / 2 - 100, 250, 250, 0.6f, 0, T_Logo1, TRUE);
		DrawRotaGraph2(SizeX / 2, SizeY / 2 - 100, 250, 250, 0.6f, 0, T_Logo2, TRUE);
		SetFontSize(20);

		if (GetJoypadNum() != 0)
			DrawString(500, 470, "-Pless Start Botton-", GetColor(Fade, Fade, Fade)); //透過度で描画
		else
			DrawString(515, 470, "-Pless Space Key-", GetColor(Fade, Fade, Fade)); //透過度で描画
	}
	else {
		DrawExtendGraph(0, 0, SizeX, SizeY, PV, FALSE);//PV描画
		WaitTimer(10); 
	}
}

//終了処理
void Title::Title_Finalize() {
}