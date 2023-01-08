#include "ButtonObject.hpp"

void Obj::Button::Collide() { CollideMouseAsBox(); }

void Obj::Button::Update() {
  //   CheckGUID();
  UpdateEnforcedMouseCollision();

  // アニメーション記述をする場合，ここに記述
  if (mouseHit) {
    SetAnimationColorPoint(&innerAnimation, innerAnimation.current,
                           hoveredInnerColor);
    SetAnimationColorPoint(&outerAnimation, outerAnimation.current,
                           hoveredOuterColor);
    SetAnimationPoint(&innerAlphaAnimation, (float)innerAlphaAnimation.current,
                      (float)hoveredInnerColor.a);
    SetAnimationPoint(&outerAlphaAnimation, (float)outerAlphaAnimation.current,
                      (float)hoveredOuterColor.a);
    SetAnimationPoint(&imageAlphaAnimation, (float)imageAlphaAnimation.current,
                      (float)hoveredImageColor.a);
  } else {
    SetAnimationColorPoint(&innerAnimation, innerAnimation.current, innerColor);
    SetAnimationColorPoint(&outerAnimation, outerAnimation.current, outerColor);
    SetAnimationPoint(&innerAlphaAnimation, (float)innerAlphaAnimation.current,
                      (float)innerColor.a);
    SetAnimationPoint(&outerAlphaAnimation, (float)outerAlphaAnimation.current,
                      (float)outerColor.a);
  }

  if (mouseSelected) {
    SetAnimationColorPoint(&innerAnimation, innerAnimation.current,
                           selectedInnerColor);
    SetAnimationColorPoint(&outerAnimation, outerAnimation.current,
                           selectedOuterColor);
    SetAnimationPoint(&innerAlphaAnimation, (float)innerAlphaAnimation.current,
                      (float)selectedInnerColor.a);
    SetAnimationPoint(&outerAlphaAnimation, (float)outerAlphaAnimation.current,
                      (float)selectedOuterColor.a);
    SetAnimationPoint(&imageAlphaAnimation, (float)imageAlphaAnimation.current,
                      (float)selectedImageColor.a);
  }

  if (mouseClicked) {
    SetAnimationColorPoint(&innerAnimation, innerAnimation.current,
                           clickedInnerColor);
    SetAnimationColorPoint(&outerAnimation, outerAnimation.current,
                           clickedOuterColor);
    SetAnimationPoint(&innerAlphaAnimation, (float)innerAlphaAnimation.current,
                      (float)clickedInnerColor.a);
    SetAnimationPoint(&outerAlphaAnimation, (float)outerAlphaAnimation.current,
                      (float)clickedOuterColor.a);
    SetAnimationPoint(&imageAlphaAnimation, (float)imageAlphaAnimation.current,
                      (float)clickedImageColor.a);
  }

  if (!enabled) {
    SetAnimationColorPoint(&innerAnimation, innerAnimation.current,
                           disabledInnerColor);
    SetAnimationColorPoint(&outerAnimation, outerAnimation.current,
                           disabledOuterColor);
    SetAnimationPoint(&innerAlphaAnimation, (float)innerAlphaAnimation.current,
                      (float)disabledInnerColor.a);
    SetAnimationPoint(&outerAlphaAnimation, (float)outerAlphaAnimation.current,
                      (float)disabledOuterColor.a);
    SetAnimationPoint(&imageAlphaAnimation, (float)imageAlphaAnimation.current,
                      (float)disabledImageColor.a);
  }

  //   EventRectSetVector();
  // if (textObject != nullptr)
  // 	textObject->Update();

  UpdateAnimationColor(&innerAnimation);
  UpdateAnimationColor(&outerAnimation);
  UpdateAnimation(&innerAlphaAnimation);
  UpdateAnimation(&outerAlphaAnimation);
  UpdateAnimation(&imageAlphaAnimation);  // 画像alpha値

  UpdatePointerAnimation();
}

void Obj::Button::Draw() {
  if (enabledOutline) {
    glColor4f(outerAnimation.current.r, outerAnimation.current.g,
              outerAnimation.current.b, outerAlphaAnimation.current);
    glBegin(GL_QUADS);
    glVertex2f(pos.x, pos.y);
    glVertex2f(pos.x + size.x, pos.y);
    glVertex2f(pos.x + size.x, pos.y + size.y);
    glVertex2f(pos.x, pos.y + size.y);
    glEnd();
  }

  if (enabledFill) {
    glColor4f(innerAnimation.current.r, innerAnimation.current.g,
              innerAnimation.current.b, innerAlphaAnimation.current);
    glBegin(GL_QUADS);
    glVertex2f(pos.x + outlineWidth, pos.y + outlineWidth);
    glVertex2f(pos.x + size.x - outlineWidth, pos.y + outlineWidth);
    glVertex2f(pos.x + size.x - outlineWidth, pos.y + size.y - outlineWidth);
    glVertex2f(pos.x + outlineWidth, pos.y + size.y - outlineWidth);
    glEnd();
  }
}

void Obj::Button::CollideMouse() {}
