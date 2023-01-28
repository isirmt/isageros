#pragma once
#include "PositionVector.hpp"
// #include "ObjectOverlapping.h"
#include "AnimationPointerData.hpp"
#include "ApplicationPreference.hpp"
#include "Color255.hpp"
#include "ColorTypes.hpp"
#include "MouseInput.hpp"
#include "Time.hpp"
#include "VectorTypes.hpp"
// Mouse Input系の管理変数が必要
#include <GL/glut.h>

#include <vector>

namespace Obj {
/// <summary>
/// <para>オブジェクトを設置する際の基本となる抽象クラス。このクラス単体ではインスタンス化できないので注意。</para>
/// <para>複数のオブジェクトの種類を1つにまとめて配列化したい時には型名をObjectBase*にすることを推奨。</para>
/// </summary>
/// <param name="_pos">オブジェクトの左上座標(2次元)</param>
/// <param name="_size">オブジェクトの大きさ(2次元)</param>
class Object2D {
 public:
  Object2D(PosVec _pos, PosVec _size)
      : pos(_pos),
        size(_size),
        enabled(true),
        mouseHit(false),
        mouseClicked(false),
        mouseSelected(false),
        children{},
        beCalledNoMouse(false),
        guid(),
        canvasOwner(false),
        canvasId(-1),
        innerAnimation(AnimationColorStatus()),
        outerAnimation(AnimationColorStatus()),
        innerAlphaAnimation(AnimationStatus()),
        outerAlphaAnimation(AnimationStatus()),
        parent(nullptr),
        enforcedCollision(1),
        imageAngle(0),
        expandedNum(false),
        imageHandle(-1),
        enforcedHovered(false),
        enforcedClicked(false),
        enforcedSelected(false) {
    // UUIDGenerator uuidGenerator;
    // guid = uuidGenerator.GetGUID();

    // ここの処理をどう書くか，ObjectBaseで管理すべきか (OverLapping)
  }

  Object2D()
      : pos(PosVec()),
        size(PosVec()),
        enabled(true),
        mouseHit(false),
        mouseClicked(false),
        mouseSelected(false),
        children{},
        beCalledNoMouse(false),
        guid(),
        canvasOwner(false),
        canvasId(-1),
        innerAnimation(AnimationColorStatus()),
        outerAnimation(AnimationColorStatus()),
        innerAlphaAnimation(AnimationStatus()),
        outerAlphaAnimation(AnimationStatus()),
        parent(nullptr),
        enforcedCollision(1),
        imageAngle(0),
        expandedNum(false),
        imageHandle(-1),
        enforcedHovered(false),
        enforcedClicked(false),
        enforcedSelected(false) {
    // UUIDGenerator uuidGenerator;
    // guid = uuidGenerator.GetGUID();
  }

  virtual ~Object2D();

 protected:
  inline void CheckGUID() { /*if (ObjectOverlapping::GetGUID() != guid)
                        SetNoMouseWithClick();*/
  }  // オブジェクト重なり判定において一番上ではなかった場合選択を解除する(推奨呼び出し)
  void UpdateEnforcedMouseCollision();

  // アニメーションカラー初期設定
  void SetAnimationColorPoint(AnimationColorStatus* type, Color255 _start,
                              Color255 _goal);
  // SetAnimationColorPoint()で設定された値の更新処理(推奨呼び出し)
  void UpdateAnimationColor(AnimationColorStatus* type);
  // アニメーション初期設定
  void SetAnimationPoint(AnimationStatus* type, float _start, float _goal);
  // SetAnimationPoint()で設定された値の更新処理(推奨呼び出し)
  void UpdateAnimation(AnimationStatus* type);

  // pColorAnimation,
  // pAnimationに追加された(座標系等々)のパラメータの更新処理(推奨呼び出し)
  void UpdatePointerAnimation();
  // 当たり判定が矩形の場合はこれを用いることを推奨する
  void CollideMouseAsBox();

  // アルファ，エリア設定含む
  void DrawImage();

  PosVec pos;   // 左上座標
  PosVec size;  // 大きさ

  bool enabled;  // 有効状態(false時は判定，更新処理が基本ない)

  bool mouseHit;       // マウスホバー時
  bool mouseSelected;  // マウスがアクティブな時
  bool mouseClicked;  // マウスがオブジェクト上でクリックされた時
  bool beCalledNoMouse;

  bool expandedNum;  // 当たり判定をクリック時に拡張するか

  std::string guid;  // 識別コード(これを用いて重複判定を行う)

  AnimationColorStatus innerAnimation;  // 内側色アニメーション構造体
  AnimationColorStatus outerAnimation;  // 外側色アニメーション構造体
  AnimationStatus innerAlphaAnimation;  // 内側透過アニメーション構造体
  AnimationStatus outerAlphaAnimation;  // 外側透過アニメーション構造体

  int canvasId;  // キャンバスのハンドル
  // Trueの場合，canvasIdは自身のハンドルとして扱われる(CanvasObject時に有効)
  bool canvasOwner;
  std::vector<Object2D*> children;  // 子オブジェクト(追従などが可能になる)
  // 親属性の設定(Canvasを設定すると当たり判定などを得ることが出来るようになる)
  Object2D* parent;

  int enforcedCollision;  // 当たり判定で優先順位をつける場合，これを用いる(乱用禁止)
  // (自動取得処理はしないため，あらかじめハンドルを得ておく必要がある)
  // 画像ハンドル
  int imageHandle;

  PosVec imageOffset;  // posから指定量だけ画像の左上座標を動かす
  PosVec imageSize;     // 目標サイズ(拡大縮小される)
  double imageAngle;    // 画像の回転角(ラジアン)
  bool imageTurnFlagX;  // X方向に反転するか
  bool imageTurnFlagY;  // Y方向に反転するか
  PosVec imageCenter;   // 回転の中心

  AnimationStatus imageAlphaAnimation;

  Color255 defaultImageColor;
  Color255 hoveredImageColor;
  Color255 clickedImageColor;
  Color255 selectedImageColor;

  Color255 disabledImageColor;

  std::string tag;

 private:
  virtual void CollideMouse() = 0;  // マウス判定処理

 private:
  std::vector<AnimationColorPointer> pColorAnimation;
  std::vector<AnimationPointer> pAnimation;
  std::vector<AnimationPointerInt> pAnimationInt;

  bool enforcedHovered;
  bool enforcedClicked;
  bool enforcedSelected;

 public:
  virtual void Update() = 0;
  virtual void Draw() = 0;
  virtual void Collide() = 0;

  inline PosVec GetPos() { return pos; }
  PosVec GetLocalPos();
  inline PosVec GetSize() { return size; }

  inline PosVec* GetVectorPointer(VectorType type) {
    switch (type) {
      case VectorType::POS:
        return &pos;
      case VectorType::SIZE:
        return &size;
      case VectorType::IMAGE_OFFSET:
        return &imageOffset;
      case VectorType::IMAGE_SIZE:
        return &imageSize;
      default:
        return nullptr;
    }
  }

  inline bool GetCanvasOwner() { return canvasOwner; }
  inline int GetCanvasId() { return canvasId; }

  inline bool SetEnabled(bool _enabled) {
    enabled = _enabled;
    return true;
  }
  inline bool SetEnabled() { return enabled; }

  // 上にレイヤが重なっていた場合の解除処理
  inline bool SetNoMouse() {
    mouseHit = false;
    return true;
  }
  inline bool SetNoMouseWithClick() {
    mouseHit = false;
    mouseClicked = false; /*beCalledNoMouse = true;*/
    return true;
  }

  // マウス入力解除(Selectedなどの任意の分岐後に呼び出し等)
  inline bool SetMouseOff() {
    mouseClicked = false;
    mouseSelected = false;
    return true;
  }

  // マウス判定系取得
  inline bool GetMouseHit() { return mouseHit; }
  inline bool GetMouseClicked() { return mouseClicked; }
  inline bool GetMouseSelected() { return mouseSelected; }

  inline void SetMouseHit(bool flag) { enforcedHovered = flag; }
  inline void SetMouseClicked(bool flag) { enforcedClicked = flag; }
  inline void SetMouseSelected(bool flag) { enforcedSelected = flag; }

  void ChangeColorWithAnimation(Color255* pColor, Color255* endColor,
                                float duration);
  void ChangeValueWithAnimation(float* pValue, float endValue, float duration);
  void ChangeValueWithAnimation(int* pValue, int endValue, float duration);

  void SetCanvasId(int id);

  inline void SetImageHandle(int handle = -1) { imageHandle = handle; }
  inline int GetImageHandle() { return imageHandle; }

  inline void SetImageOffset(PosVec offset) { imageOffset = offset; }
  inline void SetImageSize(PosVec size) { imageSize = size; }
  inline void SetImageAngle(double angle) { imageAngle = angle; }
  inline void SetImageTurnFlag(bool turnX = false, bool turnY = false) {
    imageTurnFlagX = turnX;
    imageTurnFlagY = turnY;
  }
  inline void SetImageCenter(PosVec center) { imageCenter = center; }

  inline void SetEnforcedCollision(int _enforcedCollision = 1) {
    enforcedCollision = _enforcedCollision;
  }

  // アニメーション設定
  inline bool SetInnerAnimation(float _duration) {
    innerAnimation.animationEnabled = true;
    innerAnimation.duration = _duration;
    innerAnimation.durationRemain = _duration;
    innerAnimation.elapsedTime = 0.f;
    innerAlphaAnimation.animationEnabled = true;
    innerAlphaAnimation.duration = _duration;
    innerAlphaAnimation.durationRemain = _duration;
    innerAlphaAnimation.elapsedTime = 0.f;
    imageAlphaAnimation.animationEnabled = true;
    imageAlphaAnimation.duration = _duration;
    imageAlphaAnimation.durationRemain = _duration;
    imageAlphaAnimation.elapsedTime = 0.f;
    return true;
  }
  inline bool SetInnerAnimation() {
    innerAnimation.animationEnabled = false;
    innerAlphaAnimation.animationEnabled = false;
    return true;
  }

  inline bool SetOuterAnimation(float _duration) {
    outerAnimation.animationEnabled = true;
    outerAnimation.duration = _duration;
    outerAnimation.durationRemain = _duration;
    outerAnimation.elapsedTime = 0.f;
    outerAlphaAnimation.animationEnabled = true;
    outerAlphaAnimation.duration = _duration;
    outerAlphaAnimation.durationRemain = _duration;
    outerAlphaAnimation.elapsedTime = 0.f;
    return true;
  }
  inline bool SetOuterAnimation() {
    outerAnimation.animationEnabled = false;
    outerAlphaAnimation.animationEnabled = false;
    return true;
  }

  // alpha値のみ適用される
  inline bool SetImageAlpha(Color255 _alpha) {
    defaultImageColor = _alpha;
    hoveredImageColor = _alpha;
    clickedImageColor = _alpha;
    selectedImageColor = _alpha;
    imageAlphaAnimation.current = (float)defaultImageColor.a;

    disabledImageColor = Color255(0, _alpha.a);

    return true;
  }

  // alpha値のみ適用される
  inline bool SetImageAlpha(Color255 _alpha, Color255 _hoveredColor,
                     Color255 _clickedColor, Color255 _selectedColor) {
    defaultImageColor = _alpha;
    hoveredImageColor = _hoveredColor;
    clickedImageColor = _clickedColor;
    selectedImageColor = _selectedColor;
    imageAlphaAnimation.current = (float)defaultImageColor.a;

    disabledImageColor = Color255(0, _alpha.a);

    return true;
  }

  // 親(自分)のみ移動(絶対値)
  inline bool SetPos(PosVec _pos) {
    pos = _pos;
    return true;
  }
  void SetLocalPos(PosVec _localPos);

  inline bool SetSize(PosVec _size) {
    size = _size;
    return true;
  }

  // オブジェクト移動系(子要素含む)
  virtual bool Move(PosVec _delta, bool _involvedParent = true);

  // 子要素登録
  virtual bool RegisterChildren(Object2D* _object);
  inline virtual bool DeleteAllChildren() {
    children.clear();
    return true;
  }
  // 自分のポインタを放り込むように(キャンバス用)(描画先決定用)
  // ※childrenの関数を呼ぶため予めRegisterChildrenが必要
  virtual bool RegisterParent(Object2D* _object);

  inline void SetTag(std::string _tag) { tag = _tag; }
  inline std::string GetTag() { return tag; }
};
}  // namespace Obj