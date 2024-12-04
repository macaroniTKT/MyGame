#pragma once
#include "DxLib.h"
#include <math.h>

struct AABB {
    VECTOR min;            //      �ő�l
    VECTOR max;            //      �ŏ��l
    VECTOR actorOldPos;    //      �O�̍��W�l
    AABB() = default;
    ~AABB() = default;
    AABB(VECTOR minValue, VECTOR maxValue, VECTOR actorPos) {
        min = minValue;
        max = maxValue;
        actorOldPos = actorPos;
    }
    // �X�V
    void update(const VECTOR& actorPosition) {
        VECTOR diff = VSub(actorPosition , actorOldPos);
        min = VAdd(min, diff);
        min = VAdd(max, diff);
        actorOldPos = actorPosition;
    }
};
// AABB��AABB�̏Փ˔���(�g1�Ƙg2���Փ˂��Ă���)-------(�v���C���[��������)
inline bool intersectAABB_Right(const AABB& box1, const AABB& box2) {
    if (box1.min.x > box2.max.x) return false;
    if (box1.max.x < box2.min.x) return false;

    if (box1.min.z < box2.max.z) return false;
    if (box1.max.z > box2.min.z) return false;
    return true;   // �Փ�
}
// AABB��AABB�̏Փ˔���(�g1�Ƙg2���Փ˂��Ă���)-------(�v���C���[���E����)
inline bool intersectAABB_Left(const AABB& box1, const AABB& box2) {

    if (box1.min.x > box2.max.x) return false;
    if (box1.max.x < box2.min.x) return false;

    if (box1.min.z < box2.max.z) return false;
    if (box1.max.z > box2.min.z) return false;
    return true;   // �Փ�
}

// AABB��AABB�̏Փ˔���(�g1�Ƙg2������Ă���)
inline bool intersectAABB_Area(const AABB& box1, const AABB& box2) {
    if (box1.min.x > box2.max.x) return true;
    if (box1.max.x < box2.min.x) return true;

    if (box1.min.z > box2.max.z) return true;
    if (box1.max.z < box2.min.z) return true;
    return false;   // ��Փ�
}
