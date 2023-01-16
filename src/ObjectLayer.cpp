#include "ObjectLayer.hpp"

void Obj::ObjectLayer::AddObject(Object2D* _object) {
  for (auto& item : layer) {
    if (item.object == _object) return;
  }
  layer.push_back(ObjectFunc(_object));
}

void Obj::ObjectLayer::DeleteObject(Object2D* _object) {
  for (auto it = layer.begin(); it != layer.end(); it++) {
    if (it->object == _object) {
      layer.erase(it);
      break;
    }
  }
}

void Obj::ObjectLayer::Clear() { layer.clear(); }

void Obj::ObjectLayer::SetTopLayer(Object2D* _object, int _shift) {
  int i = 0;
  for (auto& item : layer) {
    if (item.object == _object) break;
    i++;
  }
  if (i == (int)layer.size()) return;

  for (int k = i; k < (int)layer.size() - 1; k++) {
    std::iter_swap(layer.begin() + k, layer.begin() + k + 1);
  }
}

void Obj::ObjectLayer::SetButtomLayer(Object2D* _object, int _shift) {
  int i = 0;
  for (auto& item : layer) {
    if (item.object == _object) break;
    i++;
  }
  if (i == (int)layer.size()) return;

  for (int k = i; k > 0; k--) {
    std::iter_swap(layer.begin() + k, layer.begin() + k - 1);
  }
}

void Obj::ObjectLayer::MoveLayer(Object2D* _object, int _distance) {}

void Obj::ObjectLayer::Collide() {
  for (auto& item : layer) {
    item.object->Collide();
  }
}

void Obj::ObjectLayer::Update() {
  for (auto& item : layer) {
    item.object->Update();
  }
}

void Obj::ObjectLayer::Draw() {
  for (auto& item : layer) {
    item.object->Draw();
  }
}
