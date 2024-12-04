//メニュー　画像の表示のみ

#include "Menu.h"
extern SceneMgr* Scene;
extern Sound* sound;
int Cursor;//選択カーソル
int ColorChoice, ColorUnChoice; //選択状態の描画カラー
bool Menu_Input = true;
//初期化
void Menu::Menu_Initialize() {
	sound->Sound_BGM00(true);
	ColorChoice = GetColor(255, 0, 0);
	ColorUnChoice = GetColor(0, 0, 0);

	Cursor = 0;
}

//更新
void Menu::Menu_Update() {
	Menu_Draw();

	if (!Menu_Input) {
		if ((CheckHitKey(KEY_INPUT_W) == 1) || (Scene->input.ThumbLY > 1.0f) || (Scene->input.Buttons[0] == 1)) { //上入力
			Cursor -= 1; //カーソルアップ
			sound->Sound_Cursor(); //カーソル移動音再生
			Menu_Input = true;
		}
		else if ((CheckHitKey(KEY_INPUT_S) == 1) || (Scene->input.ThumbLY < -1.0f) || (Scene->input.Buttons[1] == 1)) { //下入力
			Cursor += 1; //カーソルダウン
			sound->Sound_Cursor();
			Menu_Input = true;
		}
	}
	else if (!CheckHitKey(KEY_INPUT_S) && !CheckHitKey(KEY_INPUT_W) && !(Scene->input.ThumbLY > 0.5f) && !(Scene->input.ThumbLY < -0.5f) && !(Scene->input.Buttons[0] == 1) && !(Scene->input.Buttons[1] == 1) && !(Scene->input.Buttons[12] == 1))
		Menu_Input = false;

	if (Cursor > 2)	Cursor = 0;//カーソルをループ
	if (Cursor < 0)	Cursor = 2;
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	if (!Menu_Input)
		if ((CheckHitKey(KEY_INPUT_SPACE) == 1) || (Scene->input.Buttons[12] == 1) || (Scene->input.Buttons[4] == 1)) {//エンターキーが押されていたら
			switch (Cursor) {
			case 0:
				sound->Sound_BGM00(false);//BGM停止
				if (Scene->UseVibration)StartJoypadVibration(1, 250, 500, -1);//振動
				sound->Sound_Engine();//エンジン音再生
				Scene->ChangeScene(SceneName::Scene_Game);//シーンをゲーム画面に変更
				break;
			case 1:
				sound->Sound_Enter();//確定音再生
				Scene->ChangeScene(SceneName::Scene_Config);//シーンをゲーム画面に変更
				break;
			case 2:
				sound->Sound_Enter();//確定音再生
				DxLib_End();    // DXライブラリ終了処理
				break;
			}
		}
}
//描画
void Menu::Menu_Draw() {
	//SetFontSize(64); DrawString(0, 0, "メニュー", GetColor(0, 0, 0));
	SetFontSize(20);
	DrawString(515, 430, "   -   Start  -   ", ColorUnChoice);//選ばれていない色
	DrawString(515, 450, "   -  Config  -   ", ColorUnChoice);
	DrawString(515, 470, "   -    End   -   ", ColorUnChoice);

	switch (Cursor) {
	case 0:
		DrawString(515, 430, "   -   Start  -   ", ColorChoice);//選択されているなら色を変更して描画
		break;
	case 1:
		DrawString(515, 450, "   -  Config  -   ", ColorChoice);
		break;
	case 2:
		DrawString(515, 470, "   -    End   -   ", ColorChoice);
		break;
	}
}

//終了処理
void Menu::Menu_Finalize() {
}