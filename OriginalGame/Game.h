#pragma once
#include "SceneManager.h"
#include "DxLib.h"
#include"Machine.h"
#include"Stage.h"
#include"Object.h"
#include"Effect.h"
#include"AABB.h"
#include"Sound.h"

class Game {
public:

	void Game_Initialize();//初期化
	void Game_Finalize();//終了処理


	void Game_Standby();//開始まで
	void Game_Update();//ゲーム中
	void Game_End();//終了まで

	void LoadGraphs();//画像読み込み
	void Game_Count(int phase);//タイマー関連
	void EffectSet();//
	void Game_Draw();//描画
	void Input_Draw();//操作の描画

	void CheckHit(int ObjectNumber);//マシンとオブジェクトのヒット
	void DeleteObject(int ObjectNumber);//オブジェクト破壊
	void Follow_Camera(VECTOR Tatget);//カメラ追尾
	void Area_Update();//ステージ境界判定
	void SearchGrid();//ステージ上のマシンの座標取得
	void SearchObject(int ObjectNumber);//マシンと近いオブジェクトの判別
	bool CheckHit_Square_Point(VECTOR UL, VECTOR UR, VECTOR LR, VECTOR LL, VECTOR Point);//四角形と点の当たり判別
};