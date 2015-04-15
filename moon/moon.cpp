#include <iostream>
#include <GL/glut.h>
#include <cmath>

//A class for the moon.
//Sphere of radius 1 at origin, build from 25 slices and 25 stacks
// lit with GL_LIGHT0 pointing along <1, 1, 1>
class Moon
{
	int displayListId;
	
	public:
		void create() {
			displayListId = glGenLists(1);
			glNewList(displayListId, GL_COMPILE);
			GLfloat direction[] = {-1.0, -1.0, -1.0, 0.0};
			glLightfv(GL_LIGHT0, GL_POSITION, direction);
			glutSolidSphere(1.0, 25, 25);
			glEndList();
		}

		void draw() {
			glCallList(displayListId);
		}
};

//The moon is a friend for the lonesome to talk to
static Moon moon;

// An orbiter is an object taht flies on a circle of a certain 
// radius on teh x-z plane.
class Orbiter
{
	double radius;
	double u;

	public:
		Orbiter(double radius): radius(radius), u(0.0) {}
		
		void advance(double delta) {
			u += delta;
		}
		void getPosition(double& x, double& y, double& z) 
		{
			x = radius * cos(u);
			y = 0;
			z = radius * sin(u);
		}
};

// Classic Orbiter
static Orbiter orbiter(5.0);

// Clears window and draws moon as viewed from the 
// current position of orbiter
void display() 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	
	double x, y, z;

	orbiter.getPosition(x, y, z);

	gluLookAt(x,y,z, 0.0,0.0,0.0, 0.0,1.0,0.0);

	moon.draw();
	glPopMatrix();
	glutSwapBuffers();
}

// Advances the orbiter and request to draw the next frame
void timer(int v)
{
	orbiter.advance(0.01);
	glutPostRedisplay();
	glutTimerFunc(1000/60, timer, v);
}

// Fixes projection matrix such that we always see a sphere instead of ellipsoid
void reshape(GLint w, GLint h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40.0, GLfloat(w) / GLfloat(h), 1.0, 10.0);
}

//Enables lighting for a yellow-ish light - i.e., the moon
void init()
{
	glEnable(GL_DEPTH_TEST);
	GLfloat yellow[] = {1.0, 1.0, 0.5, 1.0};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, yellow);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	moon.create();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowPosition(80, 80);
	glutInitWindowSize(500, 500);
	glutCreateWindow("The Moon");

	glutDisplayFunc(display);
	glutTimerFunc(100, timer, 0);
	glutReshapeFunc(reshape);

	init();
	glutMainLoop();
}








