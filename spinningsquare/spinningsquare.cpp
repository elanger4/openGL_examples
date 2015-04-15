#include <iostream>
#include <GL/glut.h>

//true to animate
static bool spinning = true;
//locks FPS
static const int FPS = 60;
//GLobal variable to keep track of orientation of square
static GLfloat currentAngleOfRotation = 0.0;

//Corrects viewport when animating 
void reshape(GLint w, GLint h)
{
	glViewport(0, 0, w, h);
	GLfloat aspect = (GLfloat)w / (GLfloat)h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
	{
		glOrtho(-50.0, 50.0, -50.0/aspect, 50.0/aspect, -1.0, 1.0);
	} else {
		glOrtho(-50.0*aspect, 50.0*aspect, -50.0, 50.0, -1.0, 1.0);
	}
}

// rotates square around z axis
// drawing takes place on back buffer - so we must swap
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glRotatef(currentAngleOfRotation, 0.0, 0.0, 1.0);
	glRectf(-25.0, -25.0, 25.0, 25.0);

	glFlush();
	glutSwapBuffers();
}

// Handles timer by incrementing angle of rotation and makes window
// display again.
void timer(int v)
{
	if (spinning)
	{
		currentAngleOfRotation += 1.0;

		if (currentAngleOfRotation > 360.0)
		{
			currentAngleOfRotation -= 360.0;
		}

		glutPostRedisplay();
	}
	glutTimerFunc(1000/FPS, timer, v);
}

// On left-click =  spin
// On right-click = don't spin
void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		spinning = true;
	} else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		spinning = false;
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	glutInitWindowPosition(80, 80);
	glutInitWindowSize(800, 500);
	glutCreateWindow("Spinning Square");

	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutTimerFunc(100, timer, 0);
	glutMouseFunc(mouse);

	glutMainLoop();
}




