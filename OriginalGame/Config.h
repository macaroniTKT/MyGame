#pragma once
#include "SceneManager.h"
#include "DxLib.h"

class Config {
public:
	void Config_Initialize();//初期化
	void Config_Finalize();//終了処理
	void Config_Update();//更新
	void Config_Select();
	void Config_Draw();//描画
};