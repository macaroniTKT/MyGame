#pragma once
#include "SceneManager.h"
#include "DxLib.h"

class Title {
public:
	void Title_Initialize();//初期化
	void Title_Finalize();//終了処理
	void Title_Update();//更新
	void Title_Draw();//描画
};