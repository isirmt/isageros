#include <GL/glut.h>

void draw_cube(float *a, float *d, float *s)
{
	float shininess[]={25.0};

	glMaterialfv(GL_FRONT,GL_AMBIENT,a);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,d);
	glMaterialfv(GL_FRONT,GL_SPECULAR,s);
	glMaterialfv(GL_FRONT,GL_SHININESS,shininess);

	glutSolidCube(10.0);
}

