#include "Quaternion.h"

//クォータニオンの計算
QUATERNION operator*(QUATERNION q1, QUATERNION q2)
{
    QUATERNION ans;
    double d1, d2, d3, d4;

    //tパラメータの計算 
    d1 = q1.t * q2.t;
    d2 = -q1.x * q2.x;
    d3 = -q1.y * q2.y;
    d4 = -q1.z * q2.z;
    ans.t = d1 + d2 + d3 + d4;

    //xパラメータの計算 
    d1 = q1.t * q2.x;
    d2 = q2.t * q1.x;
    d3 = q1.y * q2.z;
    d4 = -q1.z * q2.y;
    ans.x = d1 + d2 + d3 + d4;

    //yパラメータの計算
    d1 = q1.t * q2.y;
    d2 = q2.t * q1.y;
    d3 = q1.z * q2.x;
    d4 = -q1.x * q2.z;
    ans.y = d1 + d2 + d3 + d4;

    //zパラメータの計算
    d1 = q1.t * q2.z;
    d2 = q2.t * q1.z;
    d3 = q1.x * q2.y;
    d4 = -q1.y * q2.x;
    ans.z = d1 + d2 + d3 + d4;

    return ans;
}

//回転クォータニオン
QUATERNION CreateRotationQuaternion(double radian, VECTOR Axis)
{
    QUATERNION ans;
    double norm;
    double ccc, sss;

    ans.t = ans.x = ans.y = ans.z = 0.0;

    norm = Axis.x * Axis.x + Axis.y * Axis.y + Axis.z * Axis.z;
    if (norm <= 0.0) return ans;

    norm = 1.0 / sqrt(norm);
    Axis.x *= norm;
    Axis.y *= norm;
    Axis.z *= norm;

    ccc = cos(0.5 * radian);
    sss = sin(0.5 * radian);

    ans.t = ccc;
    ans.x = sss * Axis.x;
    ans.y = sss * Axis.y;
    ans.z = sss * Axis.z;

    return ans;
}

//位置クォータニオン
QUATERNION CreateXYZToQuaternion(double PosX, double PosY, double PosZ)
{
    QUATERNION ans;

    ans.t = 0.0;
    ans.x = PosX;
    ans.y = PosY;
    ans.z = PosZ;

    return ans;
}

//クォータニオンから回転行列へ
MATRIX QuaternionToMatrix(QUATERNION q)
{
    MATRIX mat = MGetIdent();
    //X軸
    mat.m[0][0] = 1.0f - 2.0f * q.y * q.y - 2.0f * q.z * q.z;
    mat.m[0][1] = 2.0f * q.x * q.y + 2.0f * q.t * q.z;
    mat.m[0][2] = 2.0f * q.x * q.z - 2.0f * q.t * q.y;

    //Y軸
    mat.m[1][0] = 2.0f * q.x * q.y - 2.0f * q.t * q.z;
    mat.m[1][1] = 1.0f - 2.0f * q.x * q.x - 2.0f * q.z * q.z;
    mat.m[1][2] = 2.0f * q.y * q.z + 2.0f * q.t * q.x;

    //Z軸
    mat.m[2][0] = 2.0f * q.x * q.z + 2.0f * q.t * q.y;
    mat.m[2][1] = 2.0f * q.y * q.z - 2.0f * q.t * q.x;
    mat.m[2][2] = 1.0f - 2.0f * q.x * q.x - 2.0f * q.y * q.y;

    return mat;
}


float QuaternionDot(const QUATERNION& q1, const QUATERNION& q2)
{
    return (q1.x * q2.x + q1.y * q2.y + q1.z * q2.z + q1.t * q2.t);
}


QUATERNION QuaternionNormalize(const QUATERNION& q)
{
    float magnitude = sqrtf(q.x * q.x + q.y * q.y + q.z * q.z + q.t * q.t);

    QUATERNION result;
    result.x = q.x / magnitude;
    result.y = q.y / magnitude;
    result.z = q.z / magnitude;
    result.t = q.t / magnitude;

    return result;
}


QUATERNION QuaternionSlerp(const QUATERNION& q1, const QUATERNION& q2, float t)
{
    // 内積計算
    float dot = QuaternionDot(q1, q2);

    // クォータニオンが逆向きなら、q2を反転させる
    QUATERNION q2Adj = q2;
    if (dot < 0.0f) {
        q2Adj.x = -q2.x;
        q2Adj.y = -q2.y;
        q2Adj.z = -q2.z;
        q2Adj.t = -q2.t;
        dot = -dot;
    }

    // クォータニオンがほぼ一致している場合、線形補間を行う
    const float EPSILON = 1.0E-6F;
    if (dot > (1.0f - EPSILON)) {
        // 線形補間 (LERP)
        QUATERNION result;
        result.x = q1.x + t * (q2Adj.x - q1.x);
        result.y = q1.y + t * (q2Adj.y - q1.y);
        result.z = q1.z + t * (q2Adj.z - q1.z);
        result.t = q1.t + t * (q2Adj.t - q1.t);
        return QuaternionNormalize(result);  // 正規化して返す
    }

    // 球面線形補間 (SLERP)
    float theta = acos(dot);  // 2つのクォータニオン間の角度
    float sinTheta = sin(theta);

    float scale1 = sin((1.0f - t) * theta) / sinTheta;
    float scale2 = sin(t * theta) / sinTheta;

    // クォータニオンを補間
    QUATERNION result;
    result.x = scale1 * q1.x + scale2 * q2Adj.x;
    result.y = scale1 * q1.y + scale2 * q2Adj.y;
    result.z = scale1 * q1.z + scale2 * q2Adj.z;
    result.t = scale1 * q1.t + scale2 * q2Adj.t;

    return QuaternionNormalize(result);  // 正規化して返す
}
