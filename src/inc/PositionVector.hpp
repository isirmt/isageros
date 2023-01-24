#pragma once

// これは座標などを管理する時のみ使い，行列の計算には使えない
struct PosVec {
  float x;
  float y;
  float z;

  PosVec() : x(0), y(0), z(0) {}
  PosVec(float _x, float _y) : x(_x), y(_y), z(0) {}
  PosVec(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

  PosVec operator+(PosVec posVec) {
    return PosVec(x + posVec.x, y + posVec.y, z + posVec.z);
  }
  PosVec operator-(PosVec posVec) {
    return PosVec(x - posVec.x, y - posVec.y, z - posVec.z);
  }

  PosVec operator*(float v) { return PosVec(x * v, y * v, z * v); }
  PosVec operator/(float v) { return PosVec(x / v, y / v, z / v); }
};