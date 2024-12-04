#pragma once
#include"DxLib.h"

class Sound {
private:
	int Object;//サウンドデータ読み込み
	int Engine;
	int Cursor;
	int Enter;
	int BGM00;
	int BGM01;
public:
	void Sound_Initialize();//初期化

	void Sound_Engine(); //エンジン音再生
	void Sound_Object(); //オブジェクト破壊音再生
	void Sound_Cursor(); //カーソル移動音再生
	void Sound_Enter();  //決定音再生
	void Sound_BGM00(bool TF);//BGM再生(falseで停止)
	void Sound_BGM01(bool TF);
};