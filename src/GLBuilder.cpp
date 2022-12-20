#include "inc/GLBuilder.hpp"
#include "inc/ApplicationPreference.hpp"

void GLSYS::GLBuilder::GLSetup()
{
    glClearColor(ApplicationPreference::defaultWorldColor.r, ApplicationPreference::defaultWorldColor.g, ApplicationPreference::defaultWorldColor.b, 0.0);
    printf("%f", ApplicationPreference::defaultWorldColor.r);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-500.0, 500.0, -500.0, 500.0, -500.0, 500.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glEnable(GL_DEPTH_TEST);
}

void GLSYS::GLBuilder::LightSetup()
{
    float ambient[]= {0.5, 0.5, 0.5, 1.0};
	float diffuse[]= {0.7, 0.7, 0.7, 1.0};
	float specular[]={1.0, 1.0, 1.0, 1.0};
	float position[]={-100.0,50.0,100.0, 1.0};

    glLightfv(GL_LIGHT0,GL_AMBIENT , ambient);
	glLightfv(GL_LIGHT0,GL_DIFFUSE , diffuse);
	glLightfv(GL_LIGHT0,GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0,GL_POSITION, position);

    glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}