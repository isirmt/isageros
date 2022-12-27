#pragma once
#include <GL/glut.h>

#include <stdexcept>
#include <string>

struct Color255 {
 public:
  int rInt;
  int gInt;
  int bInt;
  int aInt;

  float r;
  float g;
  float b;
  float a;
  GLfloat set[4];
  Color255() : rInt(0), gInt(0), bInt(0), aInt(255) { CalcFloat(); }
  Color255(int _grayScale)  // グレースケール(0~255)
      : rInt(_grayScale), gInt(_grayScale), bInt(_grayScale), aInt(255) {
    CalcFloat();
  }
  Color255(int _grayScale, int _a)  // グレースケール(0~255), アルファ(0~255)
      : rInt(_grayScale), gInt(_grayScale), bInt(_grayScale), aInt(_a) {
    CalcFloat();
  }
  Color255(int _r, int _g, int _b)  // (r, g, b) each (0~255)
      : rInt(_r), gInt(_g), bInt(_b), aInt(255) {
    CalcFloat();
  }
  Color255(int _r, int _g, int _b, int _a)  // (r, g, b, alpha) each (0~255)
      : rInt(_r), gInt(_g), bInt(_b), aInt(_a) {
    CalcFloat();
  }
  Color255(float _r, float _g, float _b)  // (r, g, b) each (0~255)
      : r(_r), g(_g), b(_b), a(1.f) {
    CalcInt();
  }
  Color255(float _r, float _g, float _b, float _a)  // (r, g, b, alpha) each (0~255)
      : r(_r), g(_g), b(_b), a(_a) {
    CalcInt();
  }
  Color255(std::string code)  // ("#00ff00"{or "00ff00"})
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
  Color255(std::string code,
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
  void CalcFloat() {
    r = (double)rInt / 255.;
    g = (double)gInt / 255.;
    b = (double)bInt / 255.;
    a = (double)aInt / 255.;
    set[0] = r;
    set[1] = g;
    set[2] = b;
    set[3] = a;
  }

  void CalcInt() {
    rInt = (int)(r * 255.f);
    gInt = (int)(g * 255.f);
    bInt = (int)(b * 255.f);
    aInt = (int)(a * 255.f);
    set[0] = r;
    set[1] = g;
    set[2] = b;
    set[3] = a;
  }

 private:
  std::string SplitSharp(std::string code) {
    std::string result = code;
    if (code.find("#") != std::string::npos) {
      result = code.substr(1);
    }
    return result;
  }
};