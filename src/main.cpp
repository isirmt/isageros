#include <stdio.h>
#include <GL/glut.h>
#include "../inc/ConvertColor.hpp"

int main(int argc, char** argv)
{
    GLSYS::ConvertColor col(100,255,30,20); // r g b a
    printf("%f, %f, %f, %f\n", col.GetColor().r, col.GetColor().g, col.GetColor().b, col.GetColor().a);
    return 0;
}