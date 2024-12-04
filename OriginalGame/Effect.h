#pragma once
#include "DxLib.h"
#define Effect_MAX 185//çÇí·ç∑äÓèÄ
class Effect {
public:
	int EffectGraph;
	float alpha = 0.0f;
	bool Flag = false;
	VECTOR StartPos;
	VECTOR EndPos;
	float Speed = 0.0f;
	float a, b;

	virtual void Initialize() = 0;
	virtual void Finalize() = 0;
	virtual void Draw() = 0;
	virtual void SetEffect(VECTOR Position,float x,float z,float rate) = 0;
};

class Effect1 : public Effect {

public:

	void Initialize();
	void Finalize();
	void Draw();
	void SetEffect(VECTOR Position, float x, float z,float rate);
};
//
//class Effect2 : public Effect {
//public:
//	void Initialize();
//	void Finalize();
//	void Draw();
//	void SetEffect(VECTOR Position, float x, float z);
//};