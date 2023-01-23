#include "ImageObject.hpp"

Obj::Image::Image(PosVec _pos, PosVec _size, std::string _filePath)
    : Object2D(_pos, _size) {
  ImageLoader imageLoader;
  imageLoader.Read(_filePath, imageData);
}

void Obj::Image::Collide() { CollideMouseAsBox(); }

void Obj::Image::Update() {
  //   CheckGUID();
  UpdateEnforcedMouseCollision();
  UpdatePointerAnimation();
}

void Obj::Image::Draw() {
  unsigned char dat[imageData.height][imageData.width][3];

  // 描画時にベクトルの違いにより上下反転で描画されることへの対策
  for (int i = 0; i < imageData.height; i++)
    for (int j = 0; j < imageData.width; j++)
      for (int k = 0; k < 3; k++)
        dat[imageData.height - 1 - i][j][k] = imageData.data[i][j][k];

  glPixelZoom(size.x / (float)imageData.width,
              size.y / (float)imageData.height);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glRasterPos2f(pos.x, pos.y);

  glDrawPixels(imageData.width, imageData.height, GL_RGB, GL_UNSIGNED_BYTE,
               dat);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
  glPixelZoom(1, 1);
  glRasterPos2f(0, 0);
}

void Obj::Image::CollideMouse() {}
