#pragma once
#include <math.h>
#include "DxLib.h"

//�N�H�[�^�j�I���\����
typedef struct
{
	float x;   //x
	float y;   //y
	float z;   //z
	float t;   //real
} QUATERNION;

//�N�H�[�^�j�I���̌v�Z
QUATERNION operator*(QUATERNION q1, QUATERNION q2);

//��]�N�H�[�^�j�I��
QUATERNION CreateRotationQuaternion(double radian, VECTOR Axis);

//�ʒu�N�H�[�^�j�I��
QUATERNION CreateXYZToQuaternion(double PosX, double PosY, double PosZ);

//�N�H�[�^�j�I�������]�s���
MATRIX QuaternionToMatrix(QUATERNION q); //</math.h>


float QuaternionDot(const QUATERNION& q1, const QUATERNION& q2);

QUATERNION QuaternionNormalize(const QUATERNION& q);

QUATERNION QuaternionSlerp(const QUATERNION& q1, const QUATERNION& q2, float t);
