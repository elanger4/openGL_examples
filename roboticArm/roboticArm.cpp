#include <iostream>
#include <GL/glut.h>

// Arm is specified by the angle that the upper arm
// makes relative to the x-axis, called shoulderAngle, and 
// the angle that the lower arm makes realtive to the 
// upper arm, called elbowAngle
static int shoulderAngle = 0, elbowAngle = 0;

// Handles keyboard event: L/R arrows bend elbow
// Up/down bend the shoulder
void special(int key, int, int)
{
	switch (key) 
	{
		case GLUT_KEY_LEFT:   (elbowAngle += 5) %= 360; 
			break;
		case GLUT_KEY_RIGHT: (elbowAngle -= 5) %= 360; 
			break;
		case GLUT_KEY_UP:     (shoulderAngle += 5) %= 360; 
			break;
		case GLUT_KEY_DOWN:   (shoulderAngle -= 5) %= 360; 
			break;
		default: return;
	}
	glutPostRedisplay();
}

// uses GLUT wirefram box with width w, height h, and depth d at the origin
void wireBox(GLdouble width, GLdouble height, GLdouble depth)
{
	glPushMatrix();
	glScalef(width, height, depth);
	glutWireCube(1.0);
	glPopMatrix();
}

//dispalys arm in current position
// Pushes and pops matrix off stack to
// keep track of camera setting
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();

	// Draw upper arm, rotate shoulder around z-axis
	// we have to shift origin of box 1 unit in the x
	glRotatef((GLfloat)shoulderAngle, 0.0, 0.0, 1.0);
	glTranslatef(1.0, 0.0, 0.0);
	wireBox(2.0, 0.4, 1.0);

	///draw lower arm. All rotations are done relative
	//to the upper arm. Rotate ellbow about z-axis
	//Continue to translate box to keep both parts of 
	//arm touching correctly
	glTranslatef(1.0, 0.0, 0.0);
	glRotatef((GLfloat)elbowAngle, 0.0, 0.0, 1.0);
	glTranslatef(1.0, 0.0, 0.0);
	wireBox(2.0, 0.4, 1.0);

	glPopMatrix();
	glFlush();
}

// Makes a nice, comfy viewport.
// sets proper aspect ratio
void reshape(GLint w, GLint h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(65.0, GLfloat(w)/GLfloat(h), 1.0, 20.0);
}

void init()
{
	glShadeModel(GL_FLAT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(1,2,8, 0,0,0, 0,1,0);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutInitWindowPosition(80, 80);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Robot Arm");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutSpecialFunc(special);

	init();
	glutMainLoop();
}








