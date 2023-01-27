#pragma once
#include <stdlib.h>

#include <fstream>
#include <iostream>

#include "ImageData.hpp"

class ImageLoader {
 public:
  ImageLoader() {}
  ~ImageLoader() {}

  int Read(std::string _filePath, ImageData& _imageData) {
    FILE* fp;
    if ((fp = fopen(_filePath.c_str(), "r")) == NULL) {
      printf("ERROR:cannot open %s\n", _filePath.c_str());
      exit(-1);
    }
    int width, height;
    int res;
    res = fscanf(fp, "P6\n%d %d\n255\n", &width, &height);
    unsigned char data[height][width][3];
    res = fread(data, width * height * 3, 1, fp);
    fclose(fp);

    if (canPrintInformation) {
      std::cout << "fileName:" << _filePath << std::endl;
      std::cout << "width:" << width << std::endl;
      std::cout << "height:" << height << std::endl;
      std::cout << std::endl;
    }

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

  const bool canPrintInformation = false;
};