#include <GL/glut.h>
void draw_sphere(float *a, float *d, float *s)
{
	float ambient[]= {0.3, 0.3, 0.0, 1.0};
	float diffuse[]= {0.7, 0.7, 0.0, 1.0};
	float specular[]={1.0, 1.0, 1.0, 1.0};
	float shininess[]={25.0};

	glMaterialfv(GL_FRONT,GL_AMBIENT,a);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,d);
	glMaterialfv(GL_FRONT,GL_SPECULAR,s);
	glMaterialfv(GL_FRONT,GL_SHININESS,shininess);

	glutSolidSphere(5.,30,30); 
}
