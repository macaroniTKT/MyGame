#include"Config.h"
extern SceneMgr* Scene;
extern Sound* sound;

int ColorTrue, ColorFalse,ColorNoPad;//設定項目の描画カラー
int ConfigChoice = GetColor(255, 0, 0), ConfigUnChoice = GetColor(0, 0, 0);//選択状態の描画カラー
int ConfigCursorMenu; //項目の選択カーソル
const int ConfigCursorMax=2; //選択ごとの項目数
int ConfigCursor[ConfigCursorMax];//配列として格納

void Config::Config_Initialize() {//初期化
	ConfigCursor[0] = 1;//カーソル初期値
	ConfigCursorMenu= 0;//カーソル初期値

	ColorTrue = GetColor(255, 0, 0);//設定でのカラー設定
	ColorFalse = GetColor(0, 0, 0);
	ColorNoPad = GetColor(200, 200, 200);
	WaitTimer(100);
}
void Config::Config_Finalize() {//終了処理
}
void Config::Config_Update() {//更新
	Config_Draw();
	Config_Select();
	if ((CheckHitKey(KEY_INPUT_W) == 1) || (Scene->input.Buttons[0] == 1) || (Scene->input.ThumbLY > 1.0f)) {//上入力
		ConfigCursorMenu -= 1;//カーソルアップ
		if(GetJoypadNum() == 0)ConfigCursorMenu -= 1;//コントローラー接続がないならスキップ
		WaitTimer(150);
	}
	else if ((CheckHitKey(KEY_INPUT_S) == 1) || (Scene->input.Buttons[1] == 1) || (Scene->input.ThumbLY < -1.0f)) { //下入力
		ConfigCursorMenu += 1;//カーソルダウン
		if (GetJoypadNum() == 0)ConfigCursorMenu += 1;//コントローラー接続がないならスキップ
		WaitTimer(150);
	}

	if (ConfigCursor[0] > 1)ConfigCursor[0] = 0;//カーソルループ
	if (ConfigCursor[0] < 0)ConfigCursor[0] = 1;
	if (ConfigCursor[1] > 1)ConfigCursor[1] = 0;
	if (ConfigCursor[1] < 0)ConfigCursor[1] = 1;

	if (ConfigCursorMenu > ConfigCursorMax)ConfigCursorMenu = 0;//カーソルループ
	if (ConfigCursorMenu < 0)ConfigCursorMenu = ConfigCursorMax;
}
void Config::Config_Select() {

	if (ConfigCursorMenu != ConfigCursorMax) {
		if ((CheckHitKey(KEY_INPUT_D) == 1) || (Scene->input.Buttons[3] == 1) || (Scene->input.ThumbLX > 1.0f)) {//左入力
			ConfigCursor[ConfigCursorMenu] += 1;
			sound->Sound_Cursor(); //カーソル移動音再生
			WaitTimer(150);
		}
		else if ((CheckHitKey(KEY_INPUT_A) == 1) || (Scene->input.Buttons[2] == 1) || (Scene->input.ThumbLX < -1.0f)) {//右入力
			ConfigCursor[ConfigCursorMenu] -= 1;
			sound->Sound_Cursor();
			WaitTimer(150);
		}
	}
	else 
		if ((CheckHitKey(KEY_INPUT_SPACE) == 1) || (Scene->input.Buttons[12] == 1)) {
			sound->Sound_Enter(); //確定音再生
			WaitTimer(100); Scene->ChangeScene(SceneName::Scene_Menu);//シーンをメニュー画面に変更
		}

	switch (ConfigCursor[0]) { //操作タイプ切り替え
	case 0:
		Scene->TypeRadicon = false;
		break;
	case 1:
		Scene->TypeRadicon = true;
		break;
	}
	switch (ConfigCursor[1]) { //振動機能の有無
	case 0:
		Scene->UseVibration = true;
		break;
	case 1:
		Scene->UseVibration = false;
		break;
	}
}

void Config::Config_Draw() {//描画
	SetFontSize(64); DrawString(0, 0, "設定", GetColor(0, 0, 0));
	SetFontSize(20);

	DrawString(315, 430, "操作タイプ　　　　", ConfigUnChoice);//選ばれていない色
	if (GetJoypadNum() != 0) {
		DrawString(315, 450, "コントローラー振動", ConfigUnChoice);
	}
	else {
		DrawString(315, 450, "コントローラー振動", ColorNoPad);//コントローラー接続がなければ別色にする
	}
	DrawString(515, 500, "メニューに戻る", ConfigUnChoice);

	switch (ConfigCursorMenu)
	{
	case 0:
		DrawString(315, 430, "操作タイプ　　　　", ConfigChoice);//選択されているなら色を変更して描画
		break;
	case 1:
		if (GetJoypadNum() != 0) {
			DrawString(315, 450, "コントローラー振動", ConfigChoice);
		}
		else {
			DrawString(315, 450, "コントローラー振動", ColorNoPad);
		}
		break;
	case ConfigCursorMax:
		DrawString(515, 500, "メニューに戻る", ConfigChoice);
		break;
	}

	if (!Scene->TypeRadicon) {
		DrawString(515, 430, "ノーマル　　　　　", ColorTrue);	DrawString(515, 430, "　　　　　ラジコン", ColorFalse);
	}
	else {
		DrawString(515, 430, "ノーマル　　　　　", ColorFalse);	DrawString(515, 430, "　　　　　ラジコン", ColorTrue);
	}
	if (GetJoypadNum() != 0) {
		if (Scene->UseVibration) {
			DrawString(515, 450, "   ON   　　　　　", ColorTrue);	DrawString(515, 450, "　　　　　  OFF   ", ColorFalse);
		}
		else {
			DrawString(515, 450, "   ON   　　　　　", ColorFalse);	DrawString(515, 450, "　　　　　  OFF   ", ColorTrue);
		}
	}
	else {
		DrawString(515, 450, "   ON   　　　　　", ColorNoPad);	DrawString(515, 450, "　　　　　  OFF   ", ColorNoPad);
	}
}