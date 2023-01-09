#include "RectangleObject.hpp"

void Obj::Rectangle::Collide() { CollideMouseAsBox(); }

void Obj::Rectangle::Update() {
  //   CheckGUID();
  UpdateEnforcedMouseCollision();

  currentInnerColor = innerColor;
  UpdatePointerAnimation();

  CheckGUID();
  SetAnimationColorPoint(&innerAnimation, innerAnimation.current, innerColor);
  SetAnimationColorPoint(&outerAnimation, outerAnimation.current, outerColor);
  SetAnimationPoint(&innerAlphaAnimation, (float)innerAlphaAnimation.current,
                    (float)innerColor.a);
  SetAnimationPoint(&outerAlphaAnimation, (float)outerAlphaAnimation.current,
                    (float)outerColor.a);

  UpdateAnimationColor(&innerAnimation);
  UpdateAnimationColor(&outerAnimation);
  UpdateAnimation(&innerAlphaAnimation);
  UpdateAnimation(&outerAlphaAnimation);

  UpdatePointerAnimation();
}

void Obj::Rectangle::Draw() {
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

void Obj::Rectangle::CollideMouse() {}
