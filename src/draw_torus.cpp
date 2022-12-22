#include <GL/glut.h>
void draw_torus(float *a, float *d, float *s)
{
	float shininess[]={25.0};

	glMaterialfv(GL_FRONT,GL_AMBIENT,a);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,d);
	glMaterialfv(GL_FRONT,GL_SPECULAR,s);
	glMaterialfv(GL_FRONT,GL_SHININESS,shininess);

	glutSolidTorus(2.0,6.0,20,20); 
}
