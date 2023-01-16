#include "TextObject.hpp"

void Obj::Text::Collide() {}

void Obj::Text::Update() {
  //   CheckGUID();
  UpdateEnforcedMouseCollision();

  currentInnerColor = innerColor;
  UpdatePointerAnimation();

  CheckGUID();
  SetAnimationColorPoint(&innerAnimation, innerAnimation.current, innerColor);
  SetAnimationPoint(&innerAlphaAnimation, (float)innerAlphaAnimation.current,
                    (float)innerColor.a);

  UpdateAnimationColor(&innerAnimation);
  UpdateAnimation(&innerAlphaAnimation);

  UpdatePointerAnimation();
}

void Obj::Text::Draw() {

  if (enabledFill) {
    glColor4f(innerAnimation.current.r, innerAnimation.current.g,
              innerAnimation.current.b, innerAlphaAnimation.current);
    JpRender::render_jstring(pos.x, pos.y, strdup(text.c_str()));
  }
}

void Obj::Text::CollideMouse() {}
