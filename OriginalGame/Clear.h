#pragma once
#include "SceneManager.h"
#include "DxLib.h"

class Clear {
public:
	void Clear_Initialize();//初期化
	void Clear_Finalize();//終了処理
	void Clear_Update();//更新
	void Clear_Draw();//描画
};