#include <iostream>
#include <GL/glut.h>
#include <cmath>
#include <unistd.h>

// the polar regions were on the x,z axis - big stupid idiots
// change that to the x,y axis
void myWireSphere(GLfloat radius, int slices, int stacks)
{
	glPushMatrix();
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	glutWireSphere(radius, slices, stacks);
	glPopMatrix();
}

// Keep track of the current "year" and "day" in 
// our 'solar system' in global variables. 
static int year = 0, day = 0;


void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();

	// Draw sun! yellow sphere of readius 1 at origin
	glColor3f(1.0, 1.0, 0.0);
	myWireSphere(1.0, 15, 15);

	//draw planet. blue sphere of radius 0.2, 2 units
	//away from the sun, with a white 'pole' as axis
	glRotatef((GLfloat)year, 0.0, 1.0, 0.0);
	glTranslatef(2.0, 0.0, 0.0);
	glRotatef((GLfloat)day, 0.0, 1.0, 0.0);
	glColor3f(0.0, 0.0, 1.0);

	myWireSphere(0.2, 15, 15);
	glColor3f(1, 1, 1);

	glBegin(GL_LINES);
		glVertex3f(0, -0.3, 0);
		glVertex3f(0,  0.3, 0);
	glEnd();

	glPopMatrix();
	glFlush();
	glutSwapBuffers();
//	usleep(100000);
}

// Basically, the camer is sitting on a comet orbiting
// the sun with a "year" 8 times that of the planet.
// Incriments u to move the camera and ticks off another
// portion of the year
// Reorients camera and refreshes display
static GLfloat u = 0.0; // curve parameter for comet position
static GLfloat du = 0.1; // amt to increment u each frame

void timer(int v)
{
	u += du;
	day = (day + 1) % 360;
	year = (year + 2) % 360;

	glLoadIdentity();

	gluLookAt(20*cos(u/8.0)+12,5*sin(u/8.0)+1,10*cos(u/8.0)+2, 0,0,0, 0,1,0);

	glutPostRedisplay();
	glutTimerFunc(1000/60, timer, v);
}

// reset projection transformation whenever window is reshaped
// set current matrixMode to GL_PROJECTION, then setting matrix
// Then set perspective camera FoV = 60 degree vertical
// Finally, reset matrixMode = GL_MODELVIEW
void reshape(GLint w, GLint h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)w/(GLfloat)h, 1.0, 40.0);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(800, 600);
	glutCreateWindow("Comet Ride");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutTimerFunc(100, timer, 0);

	glEnable(GL_DEPTH_TEST);

	glutMainLoop();
}




