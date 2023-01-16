#pragma once
#include <stdlib.h>

#include <fstream>

#include "ImageData.hpp"

class ImageLoader {
 public:
  ImageLoader() {}
  ~ImageLoader() {}

  // P6画像に対応，現状最大1920x1080まで読み込むことが出来る
  int Read(std::string _filePath, ImageData& _imageData) {
    constexpr int mWidth = 1920;
    constexpr int mHeight = 1080;
    unsigned char data[mWidth][mHeight][3];
    FILE* fp;
    if ((fp = fopen(_filePath.c_str(), "rb")) == NULL) {
      printf("ERROR:cannot open %s\n", _filePath.c_str());
      exit(-1);
    }
    int width, height;
    fscanf(fp, "P6\n%d %d\n255\n", &width, &height);
    fread(data, sizeof(char), width * height * 3, fp);
    fclose(fp);

    _imageData = ImageData(width, height);

    for (int i = 0; i < _imageData.height; i++) {
      for (int j = 0; j < _imageData.width; j++) {
        for (int k = 0; k < 3; k++) {
          _imageData.data[i][j][k] = data[i][j][k];
        }
      }
    }

    return 0;
  }
};