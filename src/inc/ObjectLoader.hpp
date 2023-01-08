#pragma once
#include <GL/glut.h>

#include <cstring>
#include <fstream>
#include <iostream>

#include "ApplicationPreference.hpp"
#include "Color255.hpp"

namespace Obj {
class Vertex {
 public:
  union {
    struct {
      float x, y, z;
    };
    float v[3];
  };
  Vertex(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
  Vertex() : x(0.0), y(0.0), z(0.0) {}

  operator float *() { return (float *)&x; }
  operator const float *() { return (const float *)&x; }
  Vertex &operator=(const Vertex &vertex) {
    x = vertex.x;
    y = vertex.y;
    z = vertex.z;
    return (*this);
  }
  Vertex operator*(float v) { return Vertex(x * v, y * v, z * v); }
  Vertex operator/(float v) {
    float sInv = 1.0f / v;
    return Vertex(x * sInv, y * sInv, z * sInv);
  }
};

class Face {
 public:
  GLenum type;
  int element;
  int materialIndex;
  int *vertexIndex;
  int *normalIndex;
  bool usingNormal;
  Face &operator=(const Face &surface) {
    type = surface.type;
    element = surface.element;
    materialIndex = surface.materialIndex;
    vertexIndex = new int[element];
    normalIndex = new int[element];
    usingNormal = surface.usingNormal;
    for (int i = 0; i < element; i++) {
      vertexIndex[i] = surface.vertexIndex[i];
      if (usingNormal)
        normalIndex[i] = surface.normalIndex[i];
      else
        normalIndex[i] = -1;
    }
    return (*this);
  }
  Face(GLenum _type = 0, int _element = 0, int *_vertexIndex = NULL,
       int *_normalIndex = NULL, bool _useNormal = false)
      : type(_type),
        element(_element),
        vertexIndex(_vertexIndex),
        normalIndex(_normalIndex),
        usingNormal(_useNormal) {}
};

class Material {
 public:
  char name[ApplicationPreference::ObjectNameLength];
  Color255 color;
  Color255 ambient;
  Color255 diffuse;
  Color255 specular;
  Color255 emission;
  float shininess;
  Material &operator=(const Material &mat) {
    strcpy(name, mat.name);
    color = mat.color;
    ambient = mat.ambient;
    diffuse = mat.diffuse;
    specular = mat.specular;
    emission = mat.emission;
    shininess = mat.shininess;
    return (*this);
  }
  Material(char materialName[ApplicationPreference::ObjectNameLength] =
               (char *)"default",
           Color255 materialColor = Color255(1.0f, 1.0, 1.0, 1.0),
           Color255 amb = Color255(1.0f, 1.0, 1.0, 1.0),
           Color255 dif = Color255(1.0f, 1.0, 1.0, 1.0),
           Color255 spe = Color255(1.0f, 1.0, 1.0, 1.0),
           Color255 emi = Color255(0.0f, 0.0, 0.0, 0.0), float power = 5.0f)
      : color(materialColor),
        ambient(amb),
        diffuse(dif),
        specular(spe),
        emission(emi),
        shininess(power) {
    strcpy(name, materialName);
  }
};

class Mesh {
 protected:
  int vertexNum;
  int normalNum;
  int faceNum;
  int materialNum;
  float size;
  Vertex *vertex;
  Vertex *normal;
  Face *face;
  Material *material;
  bool LoadOBJFile(const char *filename);
  bool LoadMTLFile(const char *filename);
  char objFileName[ApplicationPreference::ObjectNameLength];
  char materialFileName[ApplicationPreference::ObjectNameLength];
  char directoryName[ApplicationPreference::ObjectNameLength];

 public:
  GLuint listID;
  Mesh();
  ~Mesh();
  void Release();
  void Render(float scale = 1.0f);
  bool Load(const char *objfilename);
  GLuint MakeDisplayList(float scale = 1.0f);
  void AddVertex(Vertex &vert);
  void AddNormal(Vertex &norm);
  void AddFace(Face &surf);
  void AddMaterial(Material &mat);

  int GetVertexSize() { return vertexNum; }
  int GetNormalSize() { return normalNum; }
  int GetFaceSize() { return faceNum; }
  int GetMaterialSize() { return materialNum; }

  void PrintInformation();
};
}  // namespace Obj
