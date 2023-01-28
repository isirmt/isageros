#pragma once
#include <stdexcept>
#include <string>

struct Color255 {
 public:
  int rInt;
  int gInt;
  int bInt;
  int aInt;

  union {
    struct {
      float r;
      float g;
      float b;
      float a;
    };
    float set[4];
  };
  inline Color255() : rInt(0), gInt(0), bInt(0), aInt(255) { CalcFloat(); }
  inline Color255(int _grayScale)  // グレースケール(0~255)
      : rInt(_grayScale), gInt(_grayScale), bInt(_grayScale), aInt(255) {
    CalcFloat();
  }
  inline Color255(int _grayScale, int _a)  // グレースケール(0~255), アルファ(0~255)
      : rInt(_grayScale), gInt(_grayScale), bInt(_grayScale), aInt(_a) {
    CalcFloat();
  }
  inline Color255(int _r, int _g, int _b)  // (r, g, b) each (0~255)
      : rInt(_r), gInt(_g), bInt(_b), aInt(255) {
    CalcFloat();
  }
  inline Color255(int _r, int _g, int _b, int _a)  // (r, g, b, alpha) each (0~255)
      : rInt(_r), gInt(_g), bInt(_b), aInt(_a) {
    CalcFloat();
  }
  inline Color255(float _r, float _g, float _b)  // (r, g, b) each (0~255)
      : r(_r), g(_g), b(_b), a(1.f) {
    CalcInt();
  }
  inline Color255(float _r, float _g, float _b,
           float _a)  // (r, g, b, alpha) each (0~255)
      : r(_r), g(_g), b(_b), a(_a) {
    CalcInt();
  }
  inline Color255(double _r, double _g, double _b)  // (r, g, b) each (0~255)
      : r(_r), g(_g), b(_b), a(1.f) {
    CalcInt();
  }
  inline Color255(double _r, double _g, double _b,
           float _a)  // (r, g, b, alpha) each (0~255)
      : r(_r), g(_g), b(_b), a(_a) {
    CalcInt();
  }
  inline Color255(std::string code)  // ("#00ff00"{or "00ff00"})
      : aInt(255) {
    std::string formalCode = code;
    formalCode = SplitSharp(formalCode);
    int value = 0;
    try {
      value = std::stoi(formalCode, nullptr, 16);
    } catch (std::invalid_argument e) {
      value = 0;
    } catch (std::out_of_range e) {
      value = 0;
    }

    rInt = value / (256 * 256);
    gInt = (value / 256) % 256;
    bInt = value % 256;

    CalcFloat();
  }
  inline Color255(std::string code,
           int _a)  // ("#00ff00"{or "00ff00"}, alpha) alpha:(0~255)
      : aInt(_a) {
    std::string formalCode = code;
    formalCode = SplitSharp(formalCode);
    int value = 0;
    try {
      value = std::stoi(formalCode, nullptr, 16);
    } catch (std::invalid_argument e) {
      value = 0;
    } catch (std::out_of_range e) {
      value = 0;
    }

    rInt = value / (256 * 256);
    gInt = (value / 256) % 256;
    bInt = value % 256;

    CalcFloat();
  }

  // パラメータを再計算
  inline void CalcFloat() {
    r = (double)rInt / 255.;
    g = (double)gInt / 255.;
    b = (double)bInt / 255.;
    a = (double)aInt / 255.;
  }

  inline void CalcInt() {
    rInt = (int)(r * 255.f);
    gInt = (int)(g * 255.f);
    bInt = (int)(b * 255.f);
    aInt = (int)(a * 255.f);
  }

  inline Color255 operator*(float v) {
    Color255 res = Color255(r * v, g * v, b * v, a);
    CalcInt();
    return res;
  }
  inline Color255 operator/(float v) {
    float vInv = 1.0f / v;
    Color255 res = Color255(r * vInv, g * vInv, b * vInv, a);
    CalcInt();
    return res;
  }

  inline operator float *() { return (float *)&r; }
  inline operator const float *() { return (const float *)&r; }

  inline Color255 &operator=(const Color255 &color255) {
    r = color255.r;
    g = color255.g;
    b = color255.b;
    a = color255.a;
    rInt = color255.rInt;
    gInt = color255.gInt;
    bInt = color255.bInt;
    aInt = color255.aInt;

    return (*this);
  }

 private:
  inline std::string SplitSharp(std::string code) {
    std::string result = code;
    if (code.find("#") != std::string::npos) {
      result = code.substr(1);
    }
    return result;
  }
};