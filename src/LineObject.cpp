#include "LineObject.hpp"

void Obj::Line::Collide() {}

void Obj::Line::Update() { UpdatePointerAnimation(); }

void Obj::Line::Draw() {
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  if (enabledOutline) {
    glColor4f(outerAnimation.current.r, outerAnimation.current.g,
              outerAnimation.current.b, outerAlphaAnimation.current);
    glLineWidth(outlineWidth);
    glBegin(GL_LINES);
    glVertex2f(pos.x, pos.y);
    glVertex2f(pos.x + size.x, pos.y + size.y);
    glEnd();
    glLineWidth(1.f);
  }
  glDisable(GL_BLEND);
}
