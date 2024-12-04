#include"Effect.h"
#include <math.h>

void Effect1::Initialize() {
	EffectGraph = LoadGraph("Asset/effect01.png");
}

void Effect1::Finalize() {

}

void Effect1::Draw() {
	if (!Flag)return;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);

	if (a >= 0)
		StartPos.x = StartPos.x - EndPos.x * Speed;
	else
		StartPos.x = StartPos.x + EndPos.x * Speed;
	if (b >= 0)
		StartPos.z = StartPos.z - EndPos.z * Speed;
	else
		StartPos.z = StartPos.z + EndPos.z * Speed;

	StartPos.y = StartPos.y +EndPos.y*Speed;

	DrawModiBillboard3D(StartPos, -100 / 2, 100 / 2, 100 / 2, 100 / 2, 100 / 2, -100 / 2, -100 / 2, -100 / 2, EffectGraph, true);
	alpha -= 1;

	if (alpha <= 0)
		Flag = false;
}

void Effect1::SetEffect(VECTOR Position, float x, float z, float rate) {
	if (Flag)return;
	Flag = true;
	alpha = Effect_MAX;
	x = a;
	z = b;

	if (x > 5)
		StartPos.x = Position.x + GetRand(30) * 10;
	else if (x < -5)
		StartPos.x = Position.x - GetRand(30) * 10;
	else 
		StartPos.x = Position.x;

	if (z > 5)
		StartPos.z = Position.z + GetRand(30) * 10;
	else if (x < -5)
		StartPos.z = Position.z - GetRand(30) * 10;
	else
		StartPos.z = Position.z;

	StartPos.y = Position.y - GetRand(30) * 10;


	Speed = 10.f*rate;

	EndPos.x = GetRand(3) * 10 / 2.0f - (GetRand(30) * 10) * rate;
	EndPos.y = GetRand(3) * 10 / 2.0f - (GetRand(30) * 10) * rate;
	EndPos.z = GetRand(3) * 10 / 2.0f - (GetRand(30) * 10) * rate;

	EndPos = VNorm(EndPos);
}
////////////////////////////////////////////////////////////////////////////////////////

//void Effect2::Initialize() {
//	EffectGraph = LoadGraph("Asset/effect01.png");
//}
//
//void Effect2::Finalize() {
//
//}
//
//void Effect2::Draw(float x, float z) {
//	if (!Flag)return;
//	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
//
//	StartPos.x = StartPos.x + EndPos.x * Speed;
//	StartPos.y = StartPos.y + EndPos.y * Speed;
//	StartPos.z = StartPos.z + EndPos.z * Speed;
//
//	DrawModiBillboard3D(StartPos, -100 / 2, 100 / 2, 100 / 2, 100 / 2, 100 / 2, -100 / 2, -100 / 2, -100 / 2, EffectGraph, true);
//	alpha -= 1;
//
//	if (alpha <= 0)
//		Flag = false;
//}
//
//void Effect2::SetEffect(VECTOR Position, float x, float z) {
//	if (Flag)return;
//	Flag = true;
//	alpha = Effect_MAX;
//
//	StartPos.x = Position.x + GetRand(30) * 10;
//	StartPos.y = Position.y + GetRand(30) * 10;
//	StartPos.z = Position.z + GetRand(30) * 10;
//
//	Speed = 10.f;
//
//	EndPos.x = GetRand(30) * 10 / 2.0f - GetRand(30) * 10;
//	EndPos.y = GetRand(30) * 10 / 2.0f - GetRand(30) * 10;
//	EndPos.z = GetRand(30) * 10 / 2.0f - GetRand(30) * 10;
//
//	EndPos = VNorm(EndPos);
//}