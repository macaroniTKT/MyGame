#include"Clear.h"

extern SceneMgr* Scene;
extern Sound* sound;

int C_Logo0, C_Logo1, C_Logo2; //画像読み込み
float C_GraphAngle; //画像の回転値
int C_Cursor; //選択カーソル
int C_ColorUnChoice = GetColor(0, 0, 0), C_ColorChoice = GetColor(255, 0, 0); //選択状態の描画カラー


//初期化
void Clear::Clear_Initialize() {
	C_Logo0 = LoadGraph("Asset/Logo02.png");//画像読み込み
	C_Logo1 = LoadGraph("Asset/Logo03.png");
	C_Logo2 = LoadGraph("Asset/Logo01.png");
}

//更新
void Clear::Clear_Update() {
	sound->Sound_BGM00(true);//BGM再生
	C_GraphAngle -= 0.01f;//画像を回転させる
	if (C_GraphAngle > 0)C_GraphAngle = 360;
	Clear_Draw();

	if ((CheckHitKey(KEY_INPUT_W) == 1) || (Scene->input.ThumbLY > 1.0f) || (Scene->input.Buttons[0] == 1)) {//上入力
		C_Cursor -= 1;//カーソルアップ
		sound->Sound_Cursor();//カーソル移動音
		WaitTimer(150);
	}
	else if ((CheckHitKey(KEY_INPUT_S) == 1) || (Scene->input.ThumbLY < -1.0f) || (Scene->input.Buttons[1] == 1)) { //下入力
		C_Cursor += 1;//カーソルダウン
		sound->Sound_Cursor();
		WaitTimer(150);
	}

	if (C_Cursor > 2)	C_Cursor = 0; //カーソルループ
	if (C_Cursor < 0)	C_Cursor = 2;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	if ((CheckHitKey(KEY_INPUT_SPACE) == 1) || (Scene->input.Buttons[12] == 1) || (Scene->input.Buttons[4] == 1)) {//決定キーが押されていたら
		switch (C_Cursor) {
		case 0:
			sound->Sound_BGM00(false);//BGMを停止
			if (Scene->UseVibration)StartJoypadVibration(1, 250, 500, -1);//振動
			sound->Sound_Engine();//エンジン音再生
			Scene->ChangeScene(SceneName::Scene_Game);//シーンをゲーム画面に変更
			break;
		case 1:
			sound->Sound_Enter();//確定音再生
			Scene->ChangeScene(SceneName::Scene_Config);//シーンをゲーム画面に変更
			break;
		case 2:
			sound->Sound_Enter();
			DxLib_End();    // DXライブラリ終了処理
			break;
		}
	}
}

//描画
void Clear::Clear_Draw() {
	DrawRotaGraph2(SizeX / 2, SizeY / 2 - 100, 250, 250, 0.6f, C_GraphAngle, C_Logo0, TRUE);//回転値で描画
	DrawRotaGraph2(SizeX / 2, SizeY / 2 - 100, 250, 250, 0.6f, 0, C_Logo1, TRUE);
	DrawRotaGraph2(SizeX / 2, SizeY / 2 - 100, 250, 250, 0.6f, 0, C_Logo2, TRUE);

	SetFontSize(20);
	DrawString(515, 490, "   -  ReStart -   ", C_ColorUnChoice);//選ばれていない色
	DrawString(515, 510, "   -  Config  -   ", C_ColorUnChoice);
	DrawString(515, 530, "   -    End   -   ", C_ColorUnChoice);

	switch (C_Cursor) {
	case 0:
		DrawString(515, 490, "   -  ReStart -   ", C_ColorChoice);//選択されているなら色を変更して描画
		break;
	case 1:
		DrawString(515, 510, "   -  Config  -   ", C_ColorChoice);
		break;
	case 2:
		DrawString(515, 530, "   -    End   -   ", C_ColorChoice);
		break;
	}
}

//終了処理
void Clear::Clear_Finalize() {
}