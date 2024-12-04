//メイン
#include "Define.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(true); // Windowモード
	SetGraphMode(SizeX, SizeY, 32);    // 画面サイズの設定

	// ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1) return -1;        // エラーが起きたら直ちに終了

	//描画先を裏画面にする
	SetDrawScreen(DX_SCREEN_BACK);
	SetLightAmbColor(GetColorF(1.0f, 1.0f, 1.0f, 1.0f));
	SetUseLighting(true);

	Scene = new SceneMgr;
	Scene->SceneMgr_Initialize();
	sound = new Sound;
	sound->Sound_Initialize();

	// while(裏画面を表画面に反映, メッセージ処理, 画面クリア)
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		DrawBox(0, 0, SizeX, SizeY, GetColor(255, 255, 255), true);    // 背景

		Scene->SceneMgr_Update();

		//強制終了キー
		if (CheckHitKey(KEY_INPUT_ESCAPE) > 0) {
			break;
		}

	}
	Scene->SceneMgr_Finalize();//ゲーム内管理の終了処理

	delete Scene;

	DxLib_End();    // DXライブラリ終了処理
	return 0;
}