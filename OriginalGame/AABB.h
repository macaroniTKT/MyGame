#pragma once
#include "DxLib.h"
#include <math.h>

struct AABB {
    VECTOR min;            //      最大値
    VECTOR max;            //      最小値
    VECTOR actorOldPos;    //      前の座標値
    AABB() = default;
    ~AABB() = default;
    AABB(VECTOR minValue, VECTOR maxValue, VECTOR actorPos) {
        min = minValue;
        max = maxValue;
        actorOldPos = actorPos;
    }
    // 更新
    void update(const VECTOR& actorPosition) {
        VECTOR diff = VSub(actorPosition , actorOldPos);
        min = VAdd(min, diff);
        min = VAdd(max, diff);
        actorOldPos = actorPosition;
    }
};
// AABBとAABBの衝突判定(枠1と枠2が衝突している)-------(プレイヤーが左向き)
inline bool intersectAABB_Right(const AABB& box1, const AABB& box2) {
    if (box1.min.x > box2.max.x) return false;
    if (box1.max.x < box2.min.x) return false;

    if (box1.min.z < box2.max.z) return false;
    if (box1.max.z > box2.min.z) return false;
    return true;   // 衝突
}
// AABBとAABBの衝突判定(枠1と枠2が衝突している)-------(プレイヤーが右向き)
inline bool intersectAABB_Left(const AABB& box1, const AABB& box2) {

    if (box1.min.x > box2.max.x) return false;
    if (box1.max.x < box2.min.x) return false;

    if (box1.min.z < box2.max.z) return false;
    if (box1.max.z > box2.min.z) return false;
    return true;   // 衝突
}

// AABBとAABBの衝突判定(枠1と枠2が離れている)
inline bool intersectAABB_Area(const AABB& box1, const AABB& box2) {
    if (box1.min.x > box2.max.x) return true;
    if (box1.max.x < box2.min.x) return true;

    if (box1.min.z > box2.max.z) return true;
    if (box1.max.z < box2.min.z) return true;
    return false;   // 非衝突
}
