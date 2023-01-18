#include "ObjectLoader.hpp"

char *GetDirectoryName(const char *filename, char *dest) {
  char *strings = NULL;
  char *dir;
  dir = new char[strlen(filename) + 1];
  strcpy(dir, filename);
  if (strings = strrchr(dir, '/'))
    strings[1] = '\0';
  else if (strings = strrchr(dir, '\\'))
    strings[1] = '\0';
  else
    dir[0] = '\0';
  strcpy(dest, dir);
  return dest;
}

char *SetDirectoryName(char *dest, char *directory) {
  char *s = (char *)"";
  s = new char[strlen(directory) + strlen(dest) + 1];
  strcpy(s, directory);
  strcat(s, dest);
  return s;
}

Obj::Mesh::Mesh() {
  vertexNum = 0;
  normalNum = 0;
  faceNum = 0;
  materialNum = 0;
  listID = 0;
}

Obj::Mesh::~Mesh() { Release(); }

void Obj::Mesh::Release() {
  // FIXME: pointerの解放は未記述
  if (listID != 0) {
    glDeleteLists(listID, 1);
    listID = 0;
  }
  vertexNum = 0;
  normalNum = 0;
  faceNum = 0;
  materialNum = 0;
}

void Obj::Mesh::AddVertex(Vertex &vert) {
  vertexNum++;
  vertex = (Vertex *)realloc(vertex, vertexNum * sizeof(Vertex));
  vertex[vertexNum - 1] = vert;
}

void Obj::Mesh::AddNormal(Vertex &norm) {
  normalNum++;
  normal = (Vertex *)realloc(normal, normalNum * sizeof(Vertex));
  normal[normalNum - 1] = norm;
}

void Obj::Mesh::AddFace(Face &surf) {
  faceNum++;
  face = (Face *)realloc(face, faceNum * sizeof(Face));
  face[faceNum - 1] = surf;
}

void Obj::Mesh::AddMaterial(Material &mat) {
  materialNum++;
  material = (Material *)realloc(material, materialNum * sizeof(Material));
  material[materialNum - 1] = mat;
}

void Obj::Mesh::PrintInformation() {
  std::cout << "fileName:" << objFileName << std::endl;
  std::cout << "mtlFileName:" << materialFileName << std::endl;
  std::cout << "vertexNum:" << vertexNum << std::endl;
  std::cout << "normalNum:" << normalNum << std::endl;
  std::cout << "faceNum:" << faceNum << std::endl;
  std::cout << "materialNum:" << materialNum << std::endl;
  std::cout << std::endl;
}

bool Obj::Mesh::LoadOBJFile(const char *filename) {
  std::ifstream file;
  int cmi = 0;
  char tmpChar[ApplicationPreference::ObjectNameLength];
  char buf[ApplicationPreference::ObjectBufferLength];
  char *pbuf;
  float minSize = 0.0;
  float maxSize = 0.0;
  bool sizeFlag = false;

  strcpy(objFileName, filename);

  file.open(filename, std::ios::in);
  if (!file.is_open()) {
    std::cout << "Error: cannot open designated OBJ file.\n";
    std::cout << "File Name : " << filename << std::endl;
    return false;
  }

  while (!file.eof()) {
    Vertex tmpVertex(0.0, 0.0, 0.0);
    Vertex tmpNormal(0.0, 0.0, 0.0);
    Face tmpFace;
    int tmpInt = 0;

    file.getline(buf, sizeof(buf));

    switch (buf[0]) {
      case 'v':
        switch (buf[1]) {
          case ' ':
            if (sscanf(buf + 2, "%f %f %f %d", &tmpVertex.x, &tmpVertex.y,
                       &tmpVertex.z, &tmpInt) != 4) {
              if (sscanf(buf + 2, "%f %f %f", &tmpVertex.x, &tmpVertex.y,
                         &tmpVertex.z) != 3) {
                std::cout << "Error: The number of vertex is incorrect.\n";
                return false;
              }
            }
            if (!sizeFlag) {
              minSize = tmpVertex.x;
              maxSize = tmpVertex.x;
              sizeFlag = true;
            }
            for (int i = 0; i < 3; i++) {
              if (minSize > tmpVertex.v[i]) minSize = tmpVertex.v[i];
              if (maxSize < tmpVertex.v[i]) maxSize = tmpVertex.v[i];
            }
            AddVertex(tmpVertex);
            break;
          case 'n':
            if (sscanf(buf + 2, "%f %f %f", &tmpNormal.x, &tmpNormal.y,
                       &tmpNormal.z) != 3) {
              std::cout
                  << "Error : The number of normal vectors is incorrect.\n";
              return false;
            }
            AddNormal(tmpNormal);
            break;
        }
        break;

      case 'f':
        pbuf = buf;
        while (*pbuf) {
          if (*pbuf == ' ') tmpFace.element++;
          pbuf++;
        }
        if (tmpFace.element < 3) {
          std::cout << "Error : The number of face is incorrect.\n";
          return false;
        }
        switch (tmpFace.element) {
          case 3:
            tmpFace.type = GL_TRIANGLES;
            break;

          case 4:
            tmpFace.type = GL_QUADS;
            break;

          default:
            tmpFace.type = GL_POLYGON;
            break;
        }
        tmpFace.vertexIndex = new int[tmpFace.element];
        tmpFace.normalIndex = new int[tmpFace.element];
        pbuf = buf;
        for (int i = 0; i < tmpFace.element; i++) {
          pbuf = strchr(pbuf, ' ');
          pbuf++;

          if (sscanf(pbuf, "%d/%d/%d", &tmpFace.vertexIndex[i], &tmpInt,
                     &tmpFace.normalIndex[i]) != 3) {
            if (sscanf(pbuf, "%d//%d", &tmpFace.vertexIndex[i],
                       &tmpFace.normalIndex[i]) != 2) {
              if (sscanf(pbuf, "%d/%d", &tmpFace.vertexIndex[i], &tmpInt) !=
                  2) {
                sscanf(pbuf, "%d", &tmpFace.vertexIndex[i]);
                tmpFace.usingNormal = false;
              } else {
                tmpFace.usingNormal = false;
              }
            } else {
              tmpFace.usingNormal = true;
            }
          } else {
            tmpFace.usingNormal = true;
          }
          tmpFace.vertexIndex[i]--;
          if (tmpFace.usingNormal) tmpFace.normalIndex[i]--;
        }
        tmpFace.materialIndex = cmi;
        AddFace(tmpFace);
        break;
      case 'u':
        strcpy(tmpChar, " ");
        sscanf(buf, "usemtl %s", tmpChar);
        for (int i = 0; i < materialNum; i++) {
          if (strcmp(material[i].name, tmpChar) == 0) cmi = i;
        }
        break;
      case 'm':
        strcpy(tmpChar, " ");
        sscanf(buf, "mtllib %s", tmpChar);
        if (!LoadMTLFile(SetDirectoryName(tmpChar, directoryName)))
          return false;
        break;

      default:
        break;
    }
  }
  size = maxSize - minSize;
  file.close();

  return true;
}

bool Obj::Mesh::LoadMTLFile(const char *filename) {
  std::ifstream file;
  int cmi = -1;
  char buf[ApplicationPreference::ObjectBufferLength];
  float tmpFloat = 0.0f;
  Material tmpMaterial;

  strcpy(materialFileName, filename);

  file.open(filename, std::ios::in);
  if (!file.is_open()) {
    std::cout << "Error: Error: cannot open designated MTL file.\n";
    std::cout << "fileName: " << filename << std::endl;
    return false;
  }

  while (!file.eof()) {
    file.getline(buf, sizeof(buf));

    switch (buf[0]) {
      case 'n':
        cmi++;
        if (cmi != 0) AddMaterial(tmpMaterial);
        sscanf(buf, "newmtl %s", tmpMaterial.name);
        break;
      case 'K':
        switch (buf[1]) {
          case 'a':
            sscanf(buf, "Ka %f %f %f", &tmpMaterial.ambient.r,
                   &tmpMaterial.ambient.g, &tmpMaterial.ambient.b);
            tmpMaterial.color = tmpMaterial.diffuse;
            break;
          case 'd':
            sscanf(buf, "Kd %f %f %f", &tmpMaterial.diffuse.r,
                   &tmpMaterial.diffuse.g, &tmpMaterial.diffuse.b);
            break;
          case 's':
            sscanf(buf, "Ks %f %f %f", &tmpMaterial.specular.r,
                   &tmpMaterial.specular.g, &tmpMaterial.specular.b);
            break;
        }
        break;
      case 'd':
        if (sscanf(buf, "d %f", &tmpFloat) == 1) {
          tmpMaterial.color.a = tmpFloat;
          tmpMaterial.ambient.a = tmpFloat;
          tmpMaterial.diffuse.a = tmpFloat;
          tmpMaterial.specular.a = tmpFloat;
          tmpMaterial.emission.a = tmpFloat;
        }
        break;
      case 'T':
        if (buf[1] == 'r') {
          sscanf(buf, "Tr %f %f %f", &tmpMaterial.emission.r,
                 &tmpMaterial.emission.g, &tmpMaterial.emission.b);
        }
        break;
      case 'N':
        if (buf[1] == 'i') {
          sscanf(buf, "Ni %f", &tmpMaterial.shininess);
        }
        break;
      default:
        break;
    }
  }

  AddMaterial(tmpMaterial);
  file.close();

  return true;
}

bool Obj::Mesh::Load(const char *objfilename) {
  Release();

  vertex = (Vertex *)malloc(1 * sizeof(Vertex));
  normal = (Vertex *)malloc(1 * sizeof(Vertex));
  face = (Face *)malloc(1 * sizeof(Face));
  material = (Material *)malloc(1 * sizeof(Material));

  GetDirectoryName(objfilename, directoryName);

  if (!LoadOBJFile(objfilename)) return false;

  return true;
}

void Obj::Mesh::Render(float scale) {
  int preMaterial = -1, curMaterial = 0;

  for (int i = 0; i < faceNum; i++) {
    if (materialNum > 0) {
      curMaterial = face[i].materialIndex;

      if (preMaterial != curMaterial) {
        glColor4fv(material[curMaterial].color);

        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,
                     material[curMaterial].ambient);

        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,
                     material[curMaterial].diffuse);

        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,
                     material[curMaterial].specular);

        glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION,
                     material[curMaterial].emission);

        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS,
                    material[curMaterial].shininess);

        preMaterial = curMaterial;
      }
    }

    glBegin(face[i].type);
    for (int j = 0; j < face[i].element; j++) {
      // 法線ベクトル
      if (face[i].usingNormal) glNormal3fv(normal[face[i].normalIndex[j]]);
      // 頂点
      glVertex3fv(vertex[face[i].vertexIndex[j]] * scale / size);
    }
    glEnd();
  }
}

GLuint Obj::Mesh::MakeDisplayList(float scale) {
  listID = glGenLists(1);
  glNewList(listID, GL_COMPILE);
  Render(scale);
  glEndList();
  return listID;
}