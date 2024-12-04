#include"Stage.h"
////////////////////////////////////////////////////////////////////////////////////////

extern Stage* stage;
extern SceneMgr* Scene;
extern Sound* sound;
int ModelList[18];
void Stage::Initialize() {
    LoadMapModel();//マップモデル読み込み

    //枠を生成
    for (i = 0; i < MAPWIDE; i++) {
        for (j = 0; j < MAPWIDE; j++) {
            MapTip[i][j] = new class Map();
        }
    }
    //マップ生成
    MapCreate();
}
void Stage::Finalize() {
    for (i = 0; i < MAPWIDE; i++) {
        for (j = 0; j < MAPWIDE; j++) {
            MapTip[i][j]->Finalize();
        }
    }
}
void Stage::Update() {
    for (i = 0; i < MAPWIDE; i++) {
        for (j = 0; j < MAPWIDE; j++) {
            MapTip[i][j]->Draw(i, j);
        }
    }
}
void Stage::Check() {

}
void Stage::Draw() {  // ステージの描画

}
void Stage::StageFinish(float Timer) {
 //簡単なクリア画面の描画
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
        DrawBox(0, SizeY / 4, SizeX, SizeY / 4 * 3, GetColor(255, 255, 255), TRUE);

        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
        SetFontSize(100);

        if (ClearFlag) {
            DrawString(200, 300, "   G        R   ", GetColor(255 / 5, 255 / 5, 255 / 5));
            DrawString(200, 300, "    A      A    ", GetColor(255 / 4, 255 / 4, 255 / 4));
            DrawString(200, 300, "     M    E     ", GetColor(255 / 3, 255 / 3, 255 / 3));
            DrawString(200, 300, "      E  L      ", GetColor(255 / 2, 255 / 2, 255 / 2));
            DrawString(200, 300, "        C       ", GetColor(255 / 1, 255 / 1, 255 / 1));

            SetFontSize(20);
            DrawString(500, 420, "ClearTime :         ", GetColor(0, 0, 0));
            DrawFormatString(500 + GetDrawStringWidth("ClearTime : ", strlen("ClearTime : ")), 420, GetColor(0, 0, 0), "%.3f", Timer);
        }
        else {
            DrawString(200, 300, "   G        R   ", GetColor(255 / 5, 255 / 5, 255 / 5));
            DrawString(200, 300, "    A      E    ", GetColor(255 / 4, 255 / 4, 255 / 4));
            DrawString(200, 300, "     M    V     ", GetColor(255 / 3, 255 / 3, 255 / 3));
            DrawString(200, 300, "      E  O      ", GetColor(255 / 2, 255 / 2, 255 / 2));
            DrawString(200, 300, "                ", GetColor(255 / 1, 255 / 1, 255 / 1));
        }

        SetFontSize(20);
        if (GetJoypadNum() != 0)
            DrawString(500, 480, "-Pless Start Botton-", GetColor(0, 0, 0));
        else DrawString(515, 480, "-Pless Space Key-", GetColor(0, 0, 0));

        if ((CheckHitKey(KEY_INPUT_SPACE) == 1) || (Scene->input.Buttons[4] == 1)) {//エンターキーが押されていたら
            WaitTimer(100);
            sound->Sound_BGM01(false);
            sound->Sound_Enter();
            Scene->ChangeScene(SceneName::Scene_Clear);//シーンをメニュー画面に変更
        }
}
void Stage::LoadMapModel() {
    //マップモデル読み込み
    ModelList[0] = MV1LoadModel("Asset/Map/MV1/Map0000.mv1");
    ModelList[1] = MV1LoadModel("Asset/Map/MV1/Map0001.mv1");
    ModelList[2] = MV1LoadModel("Asset/Map/MV1/Map0002.mv1");
    ModelList[3] = MV1LoadModel("Asset/Map/MV1/Map0011.mv1");
    ModelList[4] = MV1LoadModel("Asset/Map/MV1/Map0012.mv1");
    ModelList[5] = MV1LoadModel("Asset/Map/MV1/Map0021.mv1");
    ModelList[6] = MV1LoadModel("Asset/Map/MV1/Map0022.mv1");
    ModelList[7] = MV1LoadModel("Asset/Map/MV1/Map0101.mv1");
    ModelList[8] = MV1LoadModel("Asset/Map/MV1/Map0102.mv1");
    ModelList[9] = MV1LoadModel("Asset/Map/MV1/Map0111.mv1");
    ModelList[10] = MV1LoadModel("Asset/Map/MV1/Map0112.mv1");
    ModelList[11] = MV1LoadModel("Asset/Map/MV1/Map0121.mv1");
    ModelList[12] = MV1LoadModel("Asset/Map/MV1/Map0122.mv1");
    ModelList[13] = MV1LoadModel("Asset/Map/MV1/Map0202.mv1");
    ModelList[14] = MV1LoadModel("Asset/Map/MV1/Map0211.mv1");
    ModelList[15] = MV1LoadModel("Asset/Map/MV1/Map0212.mv1");
    ModelList[16] = MV1LoadModel("Asset/Map/MV1/Map0221.mv1");
    ModelList[17] = MV1LoadModel("Asset/Map/MV1/Map0222.mv1");

    for (int i = 0; i < 17; i++) {
        MV1SetMaterialAmbColor(ModelList[i], 0, GetColorF(1.0f, 0.0f, 1.0f, 1.0f));
        if (i == 0)continue;
        MV1SetMaterialAmbColor(ModelList[i], 1, GetColorF(1.0f, 0.0f, 1.0f, 1.0f));
    }
}
void Stage::MapCreate() {

    //平面マップの分ループ
    for (X = 0; X < MAPWIDE_F; X++) {
        for (Z = 0; Z < MAPWIDE_F; Z++) {
            //0～2を設定
             MapF[X][Z]=GetRand(2);
            MapA[X * 2][Z * 2] = MapF[X][Z];
            //平面マップチップ設定
            stage->MapTip[X * 2][Z * 2]->HeightList[0] = MapA[X * 2][Z * 2];
            stage->MapTip[X * 2][Z * 2]->HeightList[1] = MapA[X * 2][Z * 2];
            stage->MapTip[X * 2][Z * 2]->HeightList[2] = MapA[X * 2][Z * 2];
            stage->MapTip[X * 2][Z * 2]->HeightList[3] = MapA[X * 2][Z * 2];
            //全体マップで生成
            MapTip[X * 2][Z * 2]->StageSet(X * 2, Z * 2, 0, 0, MapA[X * 2][Z * 2]);
            //端列じゃない場合
            //平面マップチップと同列
            if (Z != 0)
                //平面チップから高低差計算
                switch ((MapF[X][Z]) - (MapF[X][Z - 1])) {
                case -2:
                    stage->MapTip[X * 2][Z * 2 - 1]->HeightList[0] = 2;
                    stage->MapTip[X * 2][Z * 2 - 1]->HeightList[1] = 2;
                    stage->MapTip[X * 2][Z * 2 - 1]->HeightList[2] = 0;
                    stage->MapTip[X * 2][Z * 2 - 1]->HeightList[3] = 0;
                    MapTip[X * 2][Z * 2 - 1]->StageSet(X * 2, Z * 2 - 1, 2, 6, 0);
                    MapTip[X * 2][Z * 2 - 1]->Bool = true;
                    break;
                case -1:
                    stage->MapTip[X * 2][Z * 2 - 1]->HeightList[0] = 1 + MapA[X * 2][Z * 2];
                    stage->MapTip[X * 2][Z * 2 - 1]->HeightList[1] = 1 + MapA[X * 2][Z * 2];
                    stage->MapTip[X * 2][Z * 2 - 1]->HeightList[2] = 0 + MapA[X * 2][Z * 2];
                    stage->MapTip[X * 2][Z * 2 - 1]->HeightList[3] = 0 + MapA[X * 2][Z * 2];
                    MapTip[X * 2][Z * 2 - 1]->StageSet(X * 2, Z * 2 - 1, 2, 3, MapA[X * 2][Z * 2]);
                    break;
                case 0:
                    stage->MapTip[X * 2][Z * 2 - 1]->HeightList[0] = MapA[X * 2][Z * 2];
                    stage->MapTip[X * 2][Z * 2 - 1]->HeightList[1] = MapA[X * 2][Z * 2];
                    stage->MapTip[X * 2][Z * 2 - 1]->HeightList[2] = MapA[X * 2][Z * 2];
                    stage->MapTip[X * 2][Z * 2 - 1]->HeightList[3] = MapA[X * 2][Z * 2];
                    MapTip[X * 2][Z * 2 - 1]->StageSet(X * 2, Z * 2 - 1, 0, 0, MapA[X * 2][Z * 2]);
                    break;
                case 1:
                    stage->MapTip[X * 2][Z * 2 - 1]->HeightList[0] = -1 + MapA[X * 2][Z * 2];
                    stage->MapTip[X * 2][Z * 2 - 1]->HeightList[1] = -1 + MapA[X * 2][Z * 2];
                    stage->MapTip[X * 2][Z * 2 - 1]->HeightList[2] = 0 + MapA[X * 2][Z * 2];
                    stage->MapTip[X * 2][Z * 2 - 1]->HeightList[3] = 0 + MapA[X * 2][Z * 2];
                    MapTip[X * 2][Z * 2 - 1]->StageSet(X * 2, Z * 2 - 1, 0, 3, MapA[X * 2][Z * 2 - 2]);
                    break;
                case 2:
                    stage->MapTip[X * 2][Z * 2 - 1]->HeightList[0] = 0;
                    stage->MapTip[X * 2][Z * 2 - 1]->HeightList[1] = 0;
                    stage->MapTip[X * 2][Z * 2 - 1]->HeightList[2] = 2;
                    stage->MapTip[X * 2][Z * 2 - 1]->HeightList[3] = 2;
                    MapTip[X * 2][Z * 2 - 1]->StageSet(X * 2, Z * 2 - 1, 0, 6, 0);
                    MapTip[X * 2][Z * 2 - 1]->Bool = true;
                    break;
                }
            if (X != 0)
                //平面チップから高低差計算
                switch ((MapF[X][Z]) - (MapF[X - 1][Z])) {
                case -2:
                    stage->MapTip[X * 2 - 1][Z * 2]->HeightList[0] = 2;
                    stage->MapTip[X * 2 - 1][Z * 2]->HeightList[1] = 0;
                    stage->MapTip[X * 2 - 1][Z * 2]->HeightList[2] = 0;
                    stage->MapTip[X * 2 - 1][Z * 2]->HeightList[3] = 2;
                    MapTip[X * 2 - 1][Z * 2]->StageSet(X * 2 - 1, Z * 2, 1, 6, 0);
                    MapTip[X * 2 - 1][Z * 2]->Bool = true;
                    break;
                case -1:
                    stage->MapTip[X * 2 - 1][Z * 2]->HeightList[0] = 1 + MapA[X * 2][Z * 2];
                    stage->MapTip[X * 2 - 1][Z * 2]->HeightList[1] = 0 + MapA[X * 2][Z * 2];
                    stage->MapTip[X * 2 - 1][Z * 2]->HeightList[2] = 0 + MapA[X * 2][Z * 2];
                    stage->MapTip[X * 2 - 1][Z * 2]->HeightList[3] = 1 + MapA[X * 2][Z * 2];
                    MapTip[X * 2 - 1][Z * 2]->StageSet(X * 2 - 1, Z * 2, 1, 3, MapA[X * 2][Z * 2]);
                    break;
                case 0:
                    stage->MapTip[X * 2 - 1][Z * 2]->HeightList[0] = MapA[X * 2][Z * 2];
                    stage->MapTip[X * 2 - 1][Z * 2]->HeightList[1] = MapA[X * 2][Z * 2];
                    stage->MapTip[X * 2 - 1][Z * 2]->HeightList[2] = MapA[X * 2][Z * 2];
                    stage->MapTip[X * 2 - 1][Z * 2]->HeightList[3] = MapA[X * 2][Z * 2];
                    MapTip[X * 2 - 1][Z * 2]->StageSet(X * 2 - 1, Z * 2, 0, 0, MapA[X * 2][Z * 2]);
                    break;
                case 1:
                    stage->MapTip[X * 2 - 1][Z * 2]->HeightList[0] = -1 + MapA[X * 2][Z * 2];
                    stage->MapTip[X * 2 - 1][Z * 2]->HeightList[1] = 0 + MapA[X * 2][Z * 2];
                    stage->MapTip[X * 2 - 1][Z * 2]->HeightList[2] = 0 + MapA[X * 2][Z * 2];
                    stage->MapTip[X * 2 - 1][Z * 2]->HeightList[3] = -1 + MapA[X * 2][Z * 2];
                    MapTip[X * 2 - 1][Z * 2]->StageSet(X * 2 - 1, Z * 2, 3, 3, MapA[X * 2 - 2][Z * 2]);
                    break;
                case 2:
                    stage->MapTip[X * 2 - 1][Z * 2]->HeightList[0] = 0;
                    stage->MapTip[X * 2 - 1][Z * 2]->HeightList[1] = 2;
                    stage->MapTip[X * 2 - 1][Z * 2]->HeightList[2] = 2;
                    stage->MapTip[X * 2 - 1][Z * 2]->HeightList[3] = 0;
                    MapTip[X * 2 - 1][Z * 2]->StageSet(X * 2 - 1, Z * 2, 3, 6, 0);
                    MapTip[X * 2 - 1][Z * 2]->Bool = true;
                    break;
                }

            //平面マップ同列でない
            if (X != 0 && Z != 0) {
                MapJudge();
            }
        }
    }
}
void Stage::MapJudge() { 
    //判別用の値設定
    JudgeN = 0;
    //4角の平面チップの高さ取得
    JudgeNL[0] = MapA[X * 2 - 2][Z * 2 - 2];
    JudgeNL[1] = MapA[X * 2][Z * 2 - 2];
    JudgeNL[2] = MapA[X * 2][Z * 2];
    JudgeNL[3] = MapA[X * 2 - 2][Z * 2];
    //取得した高さを4桁の値にする
    JudgeN = JudgeNL[0] * 1000 + JudgeNL[1] * 100 + JudgeNL[2] * 10 + JudgeNL[3];

    //値からモデルと回転値を設定
    switch (JudgeN) {
    case    0:MapCreateSlope(0, 0, 0, 0);  break;  case 1111:MapCreateSlope(0, 0, 1, 0);  break;  case 2222:MapCreateSlope(0, 0, 2, 0);  break;
    case    1:MapCreateSlope(0, 1, 0, 0);  break;  case   10:MapCreateSlope(3, 1, 0, 0);  break;  case  100:MapCreateSlope(2, 1, 0, 0);  break;  case 1000:MapCreateSlope(1, 1, 0, 0);  break;
    case 1112:MapCreateSlope(0, 1, 1, 0);  break;  case 1121:MapCreateSlope(3, 1, 1, 0);  break;  case 1211:MapCreateSlope(2, 1, 1, 0);  break;  case 2111:MapCreateSlope(1, 1, 1, 0);  break;
    case    2:MapCreateSlope(0, 2, 0, 1);  break;  case   20:MapCreateSlope(3, 2, 0, 1);  break;  case  200:MapCreateSlope(2, 2, 0, 1);  break;  case 2000:MapCreateSlope(1, 2, 0, 1);  break;
    case   11:MapCreateSlope(0, 3, 0, 0);  break;  case  110:MapCreateSlope(3, 3, 0, 0);  break;  case 1100:MapCreateSlope(2, 3, 0, 0);  break;  case 1001:MapCreateSlope(1, 3, 0, 0);  break;
    case 1122:MapCreateSlope(0, 3, 1, 0);  break;  case 1221:MapCreateSlope(3, 3, 1, 0);  break;  case 2211:MapCreateSlope(2, 3, 1, 0);  break;  case 2112:MapCreateSlope(1, 3, 1, 0);  break;
    case   12:MapCreateSlope(0, 4, 0, 1);  break;  case  120:MapCreateSlope(3, 4, 0, 1);  break;  case 1200:MapCreateSlope(2, 4, 0, 1);  break;  case 2001:MapCreateSlope(1, 4, 0, 1);  break;
    case   21:MapCreateSlope(0, 5, 0, 1);  break;  case  210:MapCreateSlope(3, 5, 0, 1);  break;  case 2100:MapCreateSlope(2, 5, 0, 1);  break;  case 1002:MapCreateSlope(1, 5, 0, 1);  break;
    case   22:MapCreateSlope(0, 6, 0, 1);  break;  case  220:MapCreateSlope(3, 6, 0, 1);  break;  case 2200:MapCreateSlope(2, 6, 0, 1);  break;  case 2002:MapCreateSlope(1, 6, 0, 1);  break;
    case  101:MapCreateSlope(0, 7, 0, 0);  break;  case 1010:MapCreateSlope(1, 7, 0, 0);  break;  case 1212:MapCreateSlope(0, 7, 1, 0);  break;  case 2121:MapCreateSlope(1, 7, 1, 0);  break;
    case  102:MapCreateSlope(0, 8, 0, 1);  break;  case 1020:MapCreateSlope(3, 8, 0, 1);  break;  case  201:MapCreateSlope(2, 8, 0, 1);  break;  case 2010:MapCreateSlope(1, 8, 0, 1);  break;
    case  111:MapCreateSlope(0, 9, 0, 0);  break;  case 1110:MapCreateSlope(3, 9, 0, 0);  break;  case 1101:MapCreateSlope(2, 9, 0, 0);  break;  case 1011:MapCreateSlope(1, 9, 0, 0);  break;
    case 1222:MapCreateSlope(0, 9, 1, 0);  break;  case 2221:MapCreateSlope(3, 9, 1, 0);  break;  case 2212:MapCreateSlope(2, 9, 1, 0);  break;  case 2122:MapCreateSlope(1, 9, 1, 0);  break;
    case  112:MapCreateSlope(0, 10, 0, 1); break;  case 1120:MapCreateSlope(3, 10, 0, 1); break;  case 1201:MapCreateSlope(2, 10, 0, 1); break;  case 2011:MapCreateSlope(1, 10, 0, 1); break;
    case  121:MapCreateSlope(0, 11, 0, 1); break;  case 1210:MapCreateSlope(3, 11, 0, 1); break;  case 2101:MapCreateSlope(2, 11, 0, 1); break;  case 1012:MapCreateSlope(1, 11, 0, 1); break;
    case  122:MapCreateSlope(0, 12, 0, 1); break;  case 1220:MapCreateSlope(3, 12, 0, 1); break;  case 2201:MapCreateSlope(2, 12, 0, 1); break;  case 2012:MapCreateSlope(1, 12, 0, 1); break;
    case  202:MapCreateSlope(0, 13, 0, 1); break;  case 2020:MapCreateSlope(1, 13, 0, 1); break;
    case  211:MapCreateSlope(0, 14, 0, 1); break;  case 2110:MapCreateSlope(3, 14, 0, 1); break;  case 1102:MapCreateSlope(2, 14, 0, 1); break;  case 1021:MapCreateSlope(1, 14, 0, 1); break;
    case  212:MapCreateSlope(0, 15, 0, 1); break;  case 2120:MapCreateSlope(3, 15, 0, 1); break;  case 1202:MapCreateSlope(2, 15, 0, 1); break;  case 2021:MapCreateSlope(1, 15, 0, 1); break;
    case  221:MapCreateSlope(0, 16, 0, 1); break;  case 2210:MapCreateSlope(3, 16, 0, 1); break;  case 2102:MapCreateSlope(2, 16, 0, 1); break;  case 1022:MapCreateSlope(1, 16, 0, 1); break;
    case  222:MapCreateSlope(0, 17, 0, 1); break;  case 2220:MapCreateSlope(3, 17, 0, 1); break;  case 2202:MapCreateSlope(2, 17, 0, 1); break;  case 2022:MapCreateSlope(1, 17, 0, 1); break;
    }
}
void Stage::MapCreateSlope(int R, int M, int H, int TF) {
    //4角の平面チップの高さ取得
    stage->MapTip[X * 2 - 1][Z * 2 - 1]->HeightList[0] = stage->MapTip[X * 2 - 2][Z * 2 - 2]->HeightList[2];
    stage->MapTip[X * 2 - 1][Z * 2 - 1]->HeightList[1] = stage->MapTip[X * 2][Z * 2 - 2]->HeightList[3];
    stage->MapTip[X * 2 - 1][Z * 2 - 1]->HeightList[2] = stage->MapTip[X * 2][Z * 2]->HeightList[0];
    stage->MapTip[X * 2 - 1][Z * 2 - 1]->HeightList[3] = stage->MapTip[X * 2 - 2][Z * 2]->HeightList[1];

    MapTip[X * 2 - 1][Z * 2 - 1]->StageSet(X * 2 - 1, Z * 2 - 1, R, M, H);
    if (TF == 1)stage->MapTip[X * 2 - 1][Z * 2 - 1]->Bool = true;
}
void Map::Finalize() {
    //モデル削除
    MV1DeleteModel(Model);
}
void Map::StageSet(int X, int Z, int Rot, int ModelNum, int High) {
    //モデルと位置設定
    stage->MapTip[X][Z]->Model = MV1DuplicateModel(ModelList[ModelNum]);
    stage->MapTip[X][Z]->Pos = VGet(-MAPLONG * 20 + (X * 2 * MAPLONG + MAPLONG) + MAPLONG, High * 2 * DefaltHeight + DefaltHeight / 2, MAPLONG * 20 - (Z * 2 * MAPLONG + MAPLONG) - MAPLONG);
    stage->MapTip[X][Z]->Rotation = Rot;
    stage->MapTip[X][Z]->Height = High;

    //マップモデル設定
    MV1SetScale(stage->MapTip[X][Z]->Model, VGet(MAPLONG / 100, MAPLONG / 100, MAPLONG / 100));
    MV1SetPosition(stage->MapTip[X][Z]->Model, VGet(stage->MapTip[X][Z]->Pos.x, stage->MapTip[X][Z]->Pos.y - DefaltHeight / 2, stage->MapTip[X][Z]->Pos.z));
    MV1SetRotationXYZ(stage->MapTip[X][Z]->Model, VGet(0.0f, Rot * DX_PI_F / 180 * 90, 0.0f));
    //角の四点の座標設定
    stage->MapTip[X][Z]->MLT = VGet(Pos.x - MAPLONG, stage->MapTip[X][Z]->HeightList[0] * 2 * DefaltHeight + DefaltHeight / 2, Pos.z + MAPLONG);
    stage->MapTip[X][Z]->MRT = VGet(Pos.x + MAPLONG, stage->MapTip[X][Z]->HeightList[1] * 2 * DefaltHeight + DefaltHeight / 2, Pos.z + MAPLONG);
    stage->MapTip[X][Z]->MRB = VGet(Pos.x + MAPLONG, stage->MapTip[X][Z]->HeightList[2] * 2 * DefaltHeight + DefaltHeight / 2, Pos.z - MAPLONG);
    stage->MapTip[X][Z]->MLB = VGet(Pos.x - MAPLONG, stage->MapTip[X][Z]->HeightList[3] * 2 * DefaltHeight + DefaltHeight / 2, Pos.z - MAPLONG);

    ////
    int a = stage->MapTip[X][Z]->HeightList[0];
    int b = stage->MapTip[X][Z]->HeightList[1];
    int c = stage->MapTip[X][Z]->HeightList[2];
    int d = stage->MapTip[X][Z]->HeightList[3];

    if (a == b && a == c && a == d)										//高さがそろっている(平坦である)
        stage->MapTip[X][Z]->Center = VGet(Pos.x, a * 2 * DefaltHeight + DefaltHeight/2, Pos.z);
    else if (a * b * c * d != 0)									//高さ指数が１と２のみの傾き(高さ０が含まれない)
        stage->MapTip[X][Z]->Center = VGet(Pos.x, 1.5f * 2 * DefaltHeight + DefaltHeight/2, Pos.z);//
    else if (a == 2 || b == 2 || c == 2 ||d==2)						//０～２の傾き(０を含む,２を含む)
        stage->MapTip[X][Z]->Center = VGet(Pos.x, 1 * 2 * DefaltHeight + DefaltHeight/2, Pos.z);
    else														//高さ指数が０と１ののみの傾き(高さ２が含まれない)
        stage->MapTip[X][Z]->Center = VGet(Pos.x, 0.5f * 2 * DefaltHeight + DefaltHeight/2, Pos.z);
} 
void Map::Draw(int X, int Z) {
    //カメラ外でないなら描画
    if (CameraClip(stage->MapTip[X][Z]->MLT, stage->MapTip[X][Z]->MRT, stage->MapTip[X][Z]->MLB, stage->MapTip[X][Z]->MRB)) {
        MV1DrawModel(stage->MapTip[X][Z]->Model);

        DrawLine3D(MLB, MRB, GetColor(137, 137, 137));
        DrawLine3D(MLT, MRT, GetColor(137, 137, 137));
        DrawLine3D(MRT, MRB, GetColor(137, 137, 137));
        DrawLine3D(MLB, MLT, GetColor(137, 137, 137));
    }
}
bool Map::CameraClip(VECTOR pos1, VECTOR pos2, VECTOR pos3, VECTOR pos4) {
    //カメラ内外判定
    if (!CheckCameraViewClip(pos1)) return true;
    if (!CheckCameraViewClip(pos2)) return true;
    if (!CheckCameraViewClip(pos3)) return true;
    if (!CheckCameraViewClip(pos4)) return true;
    return false;
}
int Stage::CheckArea(int x,int y,VECTOR Machine){
    //マップチップにおけるマシンの相対位置
    DirMachine = atan2f((Machine.x - stage->MapTip[x][y]->Pos.x), (Machine.z - stage->MapTip[x][y]->Pos.z)) * 180 / DX_PI_F;
    if (DirMachine >= 45 && DirMachine < 135)return 2;
    else if (DirMachine >= 135 || DirMachine < -135)return 3;
    else if (DirMachine >= -135 && DirMachine < -45)return 4;
    else if (DirMachine >= -45 || DirMachine < 45)return 1;
    else return 0;
}