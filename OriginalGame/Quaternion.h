#pragma once
#include <math.h>
#include "DxLib.h"

//クォータニオン構造体
typedef struct
{
	float x;   //x
	float y;   //y
	float z;   //z
	float t;   //real
} QUATERNION;

//クォータニオンの計算
QUATERNION operator*(QUATERNION q1, QUATERNION q2);

//回転クォータニオン
QUATERNION CreateRotationQuaternion(double radian, VECTOR Axis);

//位置クォータニオン
QUATERNION CreateXYZToQuaternion(double PosX, double PosY, double PosZ);

//クォータニオンから回転行列へ
MATRIX QuaternionToMatrix(QUATERNION q); //</math.h>


float QuaternionDot(const QUATERNION& q1, const QUATERNION& q2);

QUATERNION QuaternionNormalize(const QUATERNION& q);

QUATERNION QuaternionSlerp(const QUATERNION& q1, const QUATERNION& q2, float t);
