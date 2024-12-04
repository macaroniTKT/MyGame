#include"Game.h"

extern SceneMgr* Scene;
extern Sound* sound;

int Judge=0; //壊したオブジェクト数
Machine* M_Array[1]; //マシンクラス 
Stage* stage; //ステージクラス
Object* O_Array[10]; //オブジェクトクラス
VECTOR Nearest, InvisibilePos = VGet(30000, 30000, 30000); //マシンから最も近い地点 , 隠す用
const int AreaSceal = MAPLONG * MAPWIDE; //移動可能エリアの辺
int Navi; //ナビオブジェクト
int Indicator;
int GraphX, GraphY;
int Number[11];
int NumGraX, NumGraY;

int KeyGraph[9];
int KeyGraX, KeyGraY;

VECTOR NaviPos; //ナビオブジェクト座標
int AnimAttachIndexN[4]; //ナビオブジェクトのアニメーション
float  AnimTotalTimeN;	//アニメーション総再生時間
float  AnimNowTimeN;	//アニメーション再生時間

VECTOR  ALT, ART, ALB, ARB;//エリアの角の四点---AreaLeftTop,AreaRightBottom

Effect* effect[255];
int Ef=0;

VECTOR CameraPos = VGet(0.0f, 0.0f, 0.0f);// カメラ位置
const float Camera_Distance = 400.f;//カメラ最大距離
float Angle = 0.0f;//カメラ角度
float Distance = 0.0f;//移動のカメラ距離

int ObjectMax = 5;//オブジェクト生成数設定
int ObjectNow;//オブジェクト現在数
int MapGridX, MapGridZ;//マップ位置識別
int MachineGridX, MachineGridZ;//マシンのマップ位置識別
int BackScreen;//背景

float Timer=0.f;
float TimeLimit = 4*1000;
float StartTime = 0.f;

void Game::Game_Initialize() {//初期化
	SRand(0);
	LoadGraphs();
	BackScreen = LoadGraph("Asset/MapTexture.png");//背景画像読み込み
	Indicator = LoadGraph("Asset/Indicator.png");//背景画像読み込み
	GetGraphSize(Indicator, &GraphX, &GraphY);
	//マップ生成
	stage = new Stage();
	stage->Initialize();

	ObjectNow = ObjectMax;//オブジェクト生成数をセット

	//オブジェクト生成
	for (int i = 0; i < ObjectMax; i++) {
		MapGridX = GetRand(9);
		MapGridZ = GetRand(9);
		O_Array[i] = new Object1();
		O_Array[i]->ModelPos = VGet(stage->MapTip[MapGridX * 2][MapGridZ * 2]->Pos.x, stage->MapTip[MapGridX * 2][MapGridZ * 2]->Pos.y + DefaltHeight / 2, stage->MapTip[MapGridX * 2][MapGridZ * 2]->Pos.z);//ランダム地点に設定
		O_Array[i]->ModelPosNavi = O_Array[i]->ModelPos; //ナビオブジェク用の枠を揃える
		O_Array[i]->Initialize();//生成
	}

	//マシン生成
	M_Array[0] = new Bulldozer();
	M_Array[0]->Initialize();

	Navi = MV1LoadModel("Asset/Building/MV1/ObjectNavi.mv1");//モデル読み込み
	MV1SetScale(Navi, VGet(0.5f, 0.5f, 0.5f));//サイズセット
	Nearest = O_Array[0]->ModelPos; //とりあえず0番目にする

	//アニメーション設定
	AnimAttachIndexN[0] = MV1AttachAnim(Navi, 3, -1, false);
	AnimAttachIndexN[1] = MV1AttachAnim(Navi, 4, -1, false);
	AnimAttachIndexN[2] = MV1AttachAnim(Navi, 9, -1, false);
	AnimAttachIndexN[3] = MV1AttachAnim(Navi, 14, -1, false);
	AnimTotalTimeN = MV1GetAttachAnimTotalTime(Navi, AnimAttachIndexN[0]);

	for (int i = 0; i < 255; i++) {
		effect[i] = new Effect1();
		effect[i]->Initialize();
	}

	WaitTimer(150);
	sound->Sound_BGM01(true);//BGM再生

	TimeLimit = 4 * 1000;
	Scene->ChangePhase(Phase::Phase_isStart);
}
void Game::Game_Finalize() {//終了処理
	M_Array[0]->Finalize();
}
void Game::LoadGraphs() {//画像読み込み
	Number[0] = LoadGraph("Asset/Number/00.png");
	Number[1] = LoadGraph("Asset/Number/01.png");
	Number[2] = LoadGraph("Asset/Number/02.png");
	Number[3] = LoadGraph("Asset/Number/03.png");
	Number[4] = LoadGraph("Asset/Number/04.png");
	Number[5] = LoadGraph("Asset/Number/05.png");
	Number[6] = LoadGraph("Asset/Number/06.png");
	Number[7] = LoadGraph("Asset/Number/07.png");
	Number[8] = LoadGraph("Asset/Number/08.png");
	Number[9] = LoadGraph("Asset/Number/09.png");

	Number[10] = LoadGraph("Asset/Number/dot.png");

	GetGraphSize(Number[10], &NumGraX, &NumGraY);

	KeyGraph[0] = LoadGraph("Asset/Key/Wkey.png");
	KeyGraph[1] = LoadGraph("Asset/Key/Akey.png");
	KeyGraph[2] = LoadGraph("Asset/Key/Skey.png");
	KeyGraph[3] = LoadGraph("Asset/Key/Dkey.png");
	KeyGraph[4] = LoadGraph("Asset/Key/MoL.png");
	KeyGraph[5] = LoadGraph("Asset/Key/MoR.png");
	KeyGraph[6] = LoadGraph("Asset/Key/GPA.png");
	KeyGraph[7] = LoadGraph("Asset/Key/GPB.png");
	KeyGraph[8] = LoadGraph("Asset/Key/GPLS.png");

	GetGraphSize(KeyGraph[0], &KeyGraX, &KeyGraY);
}

void Game::Game_Standby() {//開始まで

	Judge = 0;
	DrawExtendGraph(0, 0, 1200, 800, BackScreen, FALSE); //背景描画
	Game::Follow_Camera(M_Array[0]->Position); //カメラ追尾

	stage->Update();
	SearchGrid(); //マシンのステージ上の座標を得る
	for (int i = 0; i < ObjectMax; i++) {
		if (O_Array[i] != NULL) { //エラー回避
			O_Array[i]->Draw();  //描画 , アニメーション
			SearchObject(i); //近いオブジェクトの判別
		}
	}
	AnimNowTimeN += 1.0f;//アニメ時間を進める
	if (AnimNowTimeN >= AnimTotalTimeN)AnimNowTimeN = 0.0f;
	MV1SetAttachAnimTime(Navi, AnimAttachIndexN[0], AnimNowTimeN);
	MV1SetAttachAnimTime(Navi, AnimAttachIndexN[1], AnimNowTimeN);
	MV1SetAttachAnimTime(Navi, AnimAttachIndexN[2], AnimNowTimeN);
	MV1SetAttachAnimTime(Navi, AnimAttachIndexN[3], AnimNowTimeN);
	MV1GetAnimNum(Navi);

	M_Array[0]->mat = MGetIdent();
	M_Array[0]->matTrans = MGetIdent();

	switch (stage->CheckArea(MachineGridX, MachineGridZ, M_Array[0]->Position)) { //マシン下のマップチップの中心からの角度
	case 1:
		M_Array[0]->Inclination(stage->MapTip[MachineGridX][MachineGridZ]->MLT, stage->MapTip[MachineGridX][MachineGridZ]->MRT, stage->MapTip[MachineGridX][MachineGridZ]->Center, 1); //任意の回転
		break;
	case 2:
		M_Array[0]->Inclination(stage->MapTip[MachineGridX][MachineGridZ]->MRT, stage->MapTip[MachineGridX][MachineGridZ]->MRB, stage->MapTip[MachineGridX][MachineGridZ]->Center, 2);
		break;
	case 3:
		M_Array[0]->Inclination(stage->MapTip[MachineGridX][MachineGridZ]->MRB, stage->MapTip[MachineGridX][MachineGridZ]->MLB, stage->MapTip[MachineGridX][MachineGridZ]->Center, 3);
		break;
	case 4: 
		M_Array[0]->Inclination(stage->MapTip[MachineGridX][MachineGridZ]->MLB, stage->MapTip[MachineGridX][MachineGridZ]->MLT, stage->MapTip[MachineGridX][MachineGridZ]->Center, 4);
		break;
	default:
		break;
	}

	M_Array[0]->Draw(); //描画
	Game_Count(0);
}
void Game::Game_Update() {//ゲーム中
	Judge = 0;

	DrawExtendGraph(0, 0, 1200, 800, BackScreen, FALSE);//背景描画
	Game::Follow_Camera(M_Array[0]->Position); //カメラ追尾

	Game::Area_Update(); //エリアの内外判定

	stage->Update();//ステージの描画 , クリア判定など
	SearchGrid(); //マシンのステージ上の座標を得る

	//当たり判定等(まとめたい)
	for (int i = 0; i < ObjectMax; i++) {
		if (O_Array[i] != NULL) { //エラー回避
			O_Array[i]->Update();  //描画 , アニメーション
			SearchObject(i); //近いオブジェクトの判別
			CheckHit(i); //衝突判別
			if (O_Array[i]->isHit)Judge += 1;//ヒットで更新
		}
	}

	M_Array[0]->mat = MGetIdent();
	M_Array[0]->Update(); //描画 , 操作

	AnimNowTimeN += 1.0f;//アニメ時間を進める
	if (AnimNowTimeN >= AnimTotalTimeN)AnimNowTimeN = 0.0f;
	MV1SetAttachAnimTime(Navi, AnimAttachIndexN[0], AnimNowTimeN);
	MV1SetAttachAnimTime(Navi, AnimAttachIndexN[1], AnimNowTimeN);
	MV1SetAttachAnimTime(Navi, AnimAttachIndexN[2], AnimNowTimeN);
	MV1SetAttachAnimTime(Navi, AnimAttachIndexN[3], AnimNowTimeN);
	MV1GetAnimNum(Navi);

	//DrawFormatString(0, 150, GetColor(255, 255, 255), "%f,%f", M_Array[0]->Position.x, M_Array[0]->Position.z);

	switch (stage->CheckArea(MachineGridX, MachineGridZ, M_Array[0]->Position)) { //マシン下のマップチップの中心からの角度
	case 1:
		M_Array[0]->Inclination(stage->MapTip[MachineGridX][MachineGridZ]->MLT, stage->MapTip[MachineGridX][MachineGridZ]->MRT, stage->MapTip[MachineGridX][MachineGridZ]->Center, 1); //任意の回転
		break;
	case 2:
		M_Array[0]->Inclination(stage->MapTip[MachineGridX][MachineGridZ]->MRT, stage->MapTip[MachineGridX][MachineGridZ]->MRB, stage->MapTip[MachineGridX][MachineGridZ]->Center, 2);
		break;
	case 3:
		M_Array[0]->Inclination(stage->MapTip[MachineGridX][MachineGridZ]->MRB, stage->MapTip[MachineGridX][MachineGridZ]->MLB, stage->MapTip[MachineGridX][MachineGridZ]->Center, 3);
		break;
	case 4:
		M_Array[0]->Inclination(stage->MapTip[MachineGridX][MachineGridZ]->MLB, stage->MapTip[MachineGridX][MachineGridZ]->MLT, stage->MapTip[MachineGridX][MachineGridZ]->Center, 4);
		break;
	default:
		break;
	}
	//エフェクト設定
	if (M_Array[0]->Speed>0&&M_Array[0]->AdvRec) {
		EffectSet();
		Ef += 1;
		if (Ef >= Effect_MAX)Ef = 0;
	}
	//エフェクト描画
	for (int i = 0; i < Effect_MAX; i++) {
		effect[i]->Draw();
	}

	Game_Draw();
	Input_Draw();

	Game_Count(1);
	if (ObjectMax <= Judge) {//オブジェクトの破壊数が生成数を超える
		stage->ClearFlag = true;//ゲームクリア
		Scene->ChangePhase(Phase::Phase_isEnd);
	}
}
void Game::Game_End() {//終了まで
	Judge = ObjectMax;

	DrawExtendGraph(0, 0, 1200, 800, BackScreen, FALSE); //背景描画
	Game::Follow_Camera(M_Array[0]->Position); //カメラ追尾

	stage->Update();
	stage->StageFinish((Timer - StartTime) / 1000.f);
}

void Game::EffectSet() {
	effect[Ef]->SetEffect(VGet((M_Array[0]->RB.x + M_Array[0]->LB.x) / 2, M_Array[0]->Position.y, (M_Array[0]->RB.z + M_Array[0]->LB.z) / 2),
		sinf(M_Array[0]->Angle * (DX_PI_F / 180)) * M_Array[0]->Speed, cosf(M_Array[0]->Angle * (DX_PI_F / 180)) * M_Array[0]->Speed, M_Array[0]->SpeedRate);
}

void Game::Game_Draw() {//描画
	SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 0);
	MV1DrawModel(Navi);//ナビモデル描画

	//画面外のどの方向か
	if (CheckCameraViewClip(NaviPos)) {

		VECTOR center = VGet(SizeX * 0.5f, SizeY * 0.5f, 0.0f);

		VECTOR target_pos = VSub(ConvWorldPosToScreenPos(NaviPos), center);

		if (target_pos.z > 1.0f) {
			target_pos.x = -target_pos.x;
			target_pos.y = -target_pos.y;
		}

		float ArrowDir = atan2(NaviPos.x - M_Array[0]->Position.x, NaviPos.z - M_Array[0]->Position.z);

		float half = GraphX / 2;//画像の半分の大きさ

		float d = max(fabs(target_pos.x / (center.x - half)), fabs(target_pos.y / (center.y - half)));

		bool isOffscreen = (target_pos.z < 0.0f || d > 1.0f);
		if (isOffscreen)
		{
			target_pos.x /= d;
			target_pos.y /= d;
		}
		target_pos.x += center.x - half;
		target_pos.y += center.y - half;

		DrawRotaGraph2(target_pos.x + half, target_pos.y + half, half, half, 1.0f, ArrowDir, Indicator, true, false);
	}
}
void Game::Follow_Camera(VECTOR Target) {//カメラの設定
	Distance = sqrtf((Target.x - CameraPos.x) * (Target.x - CameraPos.x) + (Target.z - CameraPos.z) * (Target.z - CameraPos.z));
	if (Distance >= Camera_Distance) {
		// プレイヤーキャラの位置(x,z）を起点にプレイヤーキャラの後方を追従する
		// Camera_Distanceは、プレイヤー位置から後方までの距離
		Angle = atan2f(Target.x - CameraPos.x, Target.z - CameraPos.z);
		CameraPos.x = Target.x - sinf(Angle) * Camera_Distance;
		CameraPos.z = Target.z - cosf(Angle) * Camera_Distance;
	}
	CameraPos = VGet(Target.x, Target.y + 3200, Target.z - 2000);
	SetCameraPositionAndAngle(CameraPos, 45.0f, 0.0f, 0.0f);
}
void Game::Area_Update() {
	ALT = VGet(-AreaSceal, M_Array[0]->Position.y, AreaSceal);//角の四点設定
	ART = VGet(AreaSceal, M_Array[0]->Position.y, AreaSceal);
	ALB = VGet(-AreaSceal, M_Array[0]->Position.y, -AreaSceal);
	ARB = VGet(AreaSceal, M_Array[0]->Position.y, -AreaSceal);

	if (intersectAABB_Area(AABB(VGet(-MAPLONG * 2 * 10, -1000, -MAPLONG * 2 * 10), VGet(MAPLONG * 2 * 10, 1000, MAPLONG * 2 * 10), VGet(0, 0, 0)), AABB(M_Array[0]->LF, M_Array[0]->RB, M_Array[0]->Position))) {
		AABB(M_Array[0]->LF, M_Array[0]->RB, M_Array[0]->Position).update(M_Array[0]->Position);
	}

	//ステージ境界に達したら 跳ね返り
	if (M_Array[0]->LF.z >= ALT.z || M_Array[0]->RF.z >= ALT.z)M_Array[0]->Bounce(1);//前方衝突
	if (M_Array[0]->LF.z <= ALB.z || M_Array[0]->RF.z <= ALB.z)M_Array[0]->Bounce(1);
	if (M_Array[0]->LF.x <= ALT.x || M_Array[0]->RF.x <= ALT.x)M_Array[0]->Bounce(1);
	if (M_Array[0]->LF.x >= ART.x || M_Array[0]->RF.x >= ART.x)M_Array[0]->Bounce(1);

	if (M_Array[0]->LB.z >= ALT.z || M_Array[0]->RB.z >= ALT.z)M_Array[0]->Bounce(2);//後方衝突
	if (M_Array[0]->LB.z <= ALB.z || M_Array[0]->RB.z <= ALB.z)M_Array[0]->Bounce(2);
	if (M_Array[0]->LB.x <= ALT.x || M_Array[0]->RB.x <= ALT.x)M_Array[0]->Bounce(2);
	if (M_Array[0]->LB.x >= ART.x || M_Array[0]->RB.x >= ART.x)M_Array[0]->Bounce(2);
}
void Game::SearchGrid() {
	for (int i = 0; i < MAPWIDE; i++) {
		for (int j = 0; j < MAPWIDE; j++) {
			if (stage->MapTip[i][j]->Pos.x - MAPLONG <= M_Array[0]->Position.x && stage->MapTip[i][j]->Pos.x + MAPLONG >= M_Array[0]->Position.x)//	マシンがどのマップチップ上にいるか
				MachineGridX = i;
			if (stage->MapTip[i][j]->Pos.z - MAPLONG <= M_Array[0]->Position.z && stage->MapTip[i][j]->Pos.z + MAPLONG >= M_Array[0]->Position.z)
				MachineGridZ = j;
		}
	}
}
void Game::SearchObject(int ObjectNumber) {
	if (VSize(VSub(M_Array[0]->Position, O_Array[ObjectNumber]->ModelPosNavi)) < VSize(VSub(M_Array[0]->Position, Nearest)))//マシンからNearestが離れた
		Nearest = O_Array[ObjectNumber]->ModelPosNavi; //Nearestを更新
	NaviPos = VGet(Nearest.x, Nearest.y + 300, Nearest.z); //ナビオブジェクトを更新
	MV1SetPosition(Navi, NaviPos);
}
void Game::CheckHit(int ObjectNumber) {
	if (!O_Array[ObjectNumber]->isHit) {
		if (CheckHit_Square_Point(O_Array[ObjectNumber]->OLU, O_Array[ObjectNumber]->ORU, O_Array[ObjectNumber]->ORD, O_Array[ObjectNumber]->OLD, M_Array[0]->LF))	//オブジェクトの4点とマシンの角が接触
			DeleteObject(ObjectNumber);																																//オブジェクト削除
		if (CheckHit_Square_Point(O_Array[ObjectNumber]->OLU, O_Array[ObjectNumber]->ORU, O_Array[ObjectNumber]->ORD, O_Array[ObjectNumber]->OLD, M_Array[0]->RF))
			DeleteObject(ObjectNumber);
		if (CheckHit_Square_Point(O_Array[ObjectNumber]->OLU, O_Array[ObjectNumber]->ORU, O_Array[ObjectNumber]->ORD, O_Array[ObjectNumber]->OLD, M_Array[0]->LB))
			M_Array[0]->Bounce(2);																																	//跳ね返り後方
		if (CheckHit_Square_Point(O_Array[ObjectNumber]->OLU, O_Array[ObjectNumber]->ORU, O_Array[ObjectNumber]->ORD, O_Array[ObjectNumber]->OLD, M_Array[0]->RF))
			M_Array[0]->Bounce(2);
	}
}
void Game::DeleteObject(int ObjectNumber) {
	if (Scene->UseVibration)StartJoypadVibration(1, 750, 500, -1); //振動
	O_Array[ObjectNumber]->SetAnimation();//アニメーション初期化
	O_Array[ObjectNumber]->ModelPosNavi = InvisibilePos;//オブジェクトを見えない位置に隠す
	Nearest = InvisibilePos; //近いオブジェクトを遠くに移動
	ObjectNow = ObjectNow - 1;//オブジェクト数を削除
	O_Array[ObjectNumber]->isHit = true;//ヒット状態に
	sound->Sound_Object();//破壊音再生
}
bool Game::CheckHit_Square_Point(VECTOR UL, VECTOR UR, VECTOR LR, VECTOR LL, VECTOR Point) { //四点からなる四角形と点との当たり判定
	if (UL.z <= Point.z && UR.z <= Point.z)return false;
    if (LL.z >= Point.z && LR.z >= Point.z)return false;
	if (UL.x >= Point.x && LL.x >= Point.x)return false;
	if (UR.x <= Point.x && LR.x <= Point.x)return false;

	return true;
}

void Game::Input_Draw() {//操作の描画

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawBox(0, SizeY - 50, SizeX, SizeY, GetColor(255, 255, 255), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0 || Scene->input.Buttons[12] == 1 || CheckHitKey(KEY_INPUT_W) || Scene->input.ThumbLY > 1.0f)
		if (M_Array[0]->Speed < -0.8f)
			DrawFormatString(0, SizeY - 30, GetColor(255, 0, 0), "　　ブレーキ");
		else
			DrawFormatString(0, SizeY - 30, GetColor(255, 0, 0), "　　前進");
	else
		if (M_Array[0]->Speed < -0.8f)
			DrawFormatString(0, SizeY - 30, GetColor(0, 0, 0), "　　ブレーキ");
		else
			DrawFormatString(0, SizeY - 30, GetColor(0, 0, 0), "　　前進");

	if ((GetMouseInput() & MOUSE_INPUT_RIGHT) != 0 || Scene->input.Buttons[13] == 1 || CheckHitKey(KEY_INPUT_S) || Scene->input.ThumbLY < -1.0f)
		if (M_Array[0]->Speed > 0.8f)
			DrawFormatString(200, SizeY - 30, GetColor(255, 0, 0), "　　ブレーキ");
		else
			DrawFormatString(200, SizeY - 30, GetColor(255, 0, 0), "　　後退");
	else
		if (M_Array[0]->Speed > 0.8f)
			DrawFormatString(200, SizeY - 30, GetColor(0, 0, 0), "　　ブレーキ");
		else
			DrawFormatString(200, SizeY - 30, GetColor(0, 0, 0), "　　後退");


	if (Scene->input.ThumbLX < -1.0f || CheckHitKey(KEY_INPUT_A))
		DrawFormatString(400, SizeY - 30, GetColor(255, 0, 0), "　　左");
	else
		DrawFormatString(400, SizeY - 30, GetColor(0, 0, 0), "　　左");
	if (Scene->input.ThumbLX > 1.0f || CheckHitKey(KEY_INPUT_D))
		DrawFormatString(600, SizeY - 30, GetColor(255, 0, 0), "　　右");
	else
		DrawFormatString(600, SizeY - 30, GetColor(0, 0, 0), "　　右");

	if (GetJoypadNum() != 0) {
		if (Scene->TypeRadicon) {
			DrawExtendGraph(0, SizeY - 40, 0 + 40, SizeY, KeyGraph[7], true);
			DrawExtendGraph(200, SizeY - 40, 200 + 40, SizeY, KeyGraph[6], true);
		}
		else {
			DrawExtendGraph(0, SizeY - 40, 0 + 40, SizeY, KeyGraph[8], true);
			DrawExtendGraph(200, SizeY - 40, 200 + 40, SizeY, KeyGraph[8], true);
			DrawExtendGraph(400, SizeY - 40, 400 + 40, SizeY, KeyGraph[8], true);
			DrawExtendGraph(600, SizeY - 40, 600 + 40, SizeY, KeyGraph[8], true);
		}
		DrawExtendGraph(400, SizeY - 40, 400 + 40, SizeY, KeyGraph[8], true);
		DrawExtendGraph(600, SizeY - 40, 600 + 40, SizeY, KeyGraph[8], true);
	}
	else {
		if (Scene->TypeRadicon) {
			DrawExtendGraph(0, SizeY - 40, 0 + 40, SizeY, KeyGraph[4], true);
			DrawExtendGraph(200, SizeY - 40, 200 + 40, SizeY, KeyGraph[5], true);
		}
		else {
			DrawExtendGraph(0, SizeY - 40, 0 + 40, SizeY, KeyGraph[0], true);
			DrawExtendGraph(200, SizeY - 40, 200 + 40, SizeY, KeyGraph[2], true);
		}
		DrawExtendGraph(400, SizeY - 40, 400 + 40, SizeY, KeyGraph[1], true);
		DrawExtendGraph(600, SizeY - 40, 600 + 40, SizeY, KeyGraph[3], true);
	}
}

void Game::Game_Count(int phase){//タイマー関連
	if (phase != 2) {
		if (Scene->StartrCount) {
			StartTime = GetNowCount();
			Scene->StartrCount = false;
		}
		Timer = GetNowCount();
	}

	int Time = TimeLimit - (Timer - StartTime);

	int a = Time / 10000;
	int b = (Time / 1000) % 10;
	int c= (Time / 100) % 10;
	int d = (Time / 10) % 10;

	switch (phase) {
	case 0:
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 / (10 - c));
		DrawExtendGraph(SizeX / 2 - 147 / 2, SizeY / 2 - 220 / 2, SizeX / 2 + 147 / 2, SizeY / 2 + 220 / 2, Number[b], true);
		if (TimeLimit <= Timer - StartTime) {
			TimeLimit = 90*1000;
			phase = 1;
			Scene->ChangePhase(Phase::Phase_isScene);
		}
		break;
	case 1:
		DrawExtendGraph(SizeX / 2 - NumGraX / 2 * 2.5 / 2, 0, SizeX / 2 - NumGraX / 2 * 1.5 / 2, NumGraY / 4, Number[a], true);
		DrawExtendGraph(SizeX / 2 - NumGraX / 2 * 1.5 / 2, 0, SizeX / 2 - NumGraX / 2 * 0.5 / 2, NumGraY / 4, Number[b], true);
		DrawExtendGraph(SizeX / 2 - NumGraX / 2 * 0.5 / 2, 0, SizeX / 2 + NumGraX / 2 * 0.5 / 2, NumGraY / 4, Number[10], true);
		DrawExtendGraph(SizeX / 2 + NumGraX / 2 * 0.5 / 2, 0, SizeX / 2 + NumGraX / 2 * 1.5 / 2, NumGraY / 4, Number[c], true);
		DrawExtendGraph(SizeX / 2 + NumGraX / 2 * 1.5 / 2, 0, SizeX / 2 + NumGraX / 2 * 2.5 / 2, NumGraY / 4, Number[d], true);

		if (TimeLimit <= Timer - StartTime) {
			phase = 2;
			stage->ClearFlag = false;

			Scene->ChangePhase(Phase::Phase_isEnd);
		}
		break;
	case 2:

		break;
	}
}