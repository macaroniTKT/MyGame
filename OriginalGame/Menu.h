#pragma once
#include "SceneManager.h"
#include "DxLib.h"

class Menu {
public:
	void Menu_Initialize();//初期化
	void Menu_Finalize();//終了処理
	void Menu_Update();//更新
	void Menu_Draw();//描画
};