#pragma once
#include <vector>

// for .PPM
struct ImageData {
 public:
  std::vector<std::vector<std::vector<unsigned char>>> data;
  int width;
  int height;

  ImageData() {}
  ImageData(int _width, int _height) : height(_height), width(_width) {
    data = std::vector<std::vector<std::vector<unsigned char>>>(
        height, std::vector<std::vector<unsigned char>>(
                    width, std::vector<unsigned char>(3)));
  }
};
