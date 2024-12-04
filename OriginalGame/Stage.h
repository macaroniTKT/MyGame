#pragma once
#include "DxLib.h"
#include "SceneManager.h"

const float MAPLONG = 500;//マップ幅
const int MAPWIDE_F = 10;
const int MAPWIDE = MAPWIDE_F * 2 - 1;//マップグリッド数
#define DefaltHeight MAPLONG/5//高低差基準
class Stage {
private:
public:
	int i, j;
	class MapObject* MapTip[MAPWIDE][MAPWIDE];

	void Initialize();//開始
	void Finalize();//終了
	void Update();
	void Draw();//描画
	void Check();//
	void StageFinish(float Timer);//ステージクリア描画
	void MapCreate();//全体マップ生成
	void MapJudge();//マップチップ情報変換
	void MapCreateSlope(int R, int M, int H, int TF);//傾きを持ったマップチップ生成
	void LoadMapModel();//モデル読み込み

	float DirMachine;//マップチップ上のマシンモデルの相対位置角度

	int CheckArea(int x, int y, VECTOR Machine);//マシンとの相対位置と傾き

	bool ClearFlag = false;//ゲームクリア判別

	//マップ生成用
	int X, Z;
	int MapF[MAPWIDE_F][MAPWIDE_F];
	int MapA[MAPWIDE][MAPWIDE];

	//モデル判別用
	int JudgeNL[4];
	int JudgeN = 0;
};

class MapObject{
private: 

protected:

public:
	VECTOR Pos;    //生成位置
	VECTOR MLT,MRT,MLB,MRB;//角の四点---MapTipLeftTop,MapTipRightBottom
	VECTOR Center;
	int HeightList[4];//角の四点の高さ指数
	int Rotation;  //モデルの回転値
	int Model;     //モデル読み込み
	int Height;	//高さ指数
	bool Bool; //高低差変化の有効

	virtual void Finalize() = 0;//終了
	virtual void StageSet(int X, int Y, int Rot, int ModelNum, int High) = 0;//生成

	virtual void Draw(int X,int Y) = 0;//描画
};

class Map : public MapObject{
	bool CameraClip(VECTOR pos1, VECTOR pos2, VECTOR pos3, VECTOR pos4);//カメラ内外判定
	void Finalize();
	void StageSet(int X, int Y, int Rot, int ModelNum, int High);
	void Draw(int X, int Y);
};