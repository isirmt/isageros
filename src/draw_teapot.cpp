#include <GL/glut.h>
void draw_teapot(float *a, float *d, float *s)
{
	float shininess[]={50.0};

	glMaterialfv(GL_FRONT,GL_AMBIENT,a);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,d);
	glMaterialfv(GL_FRONT,GL_SPECULAR,s);
	glMaterialfv(GL_FRONT,GL_SHININESS,shininess);

	glutSolidTeapot(5.0);
}

