#include <iostream>
#include <GL/glut.h>
#include <cmath>

//cube has opposite corners at (0,0,0) and (1,1,1) which
//are respectively black and white.  x-red, y-green, z-blue
//cubes position and colors are fixed
namespace Cube
{
	const int NUM_VERTICES = 8;
	const int NUM_FACES = 6;

	GLint vertices[NUM_VERTICES][3] = {
		{0, 0, 0}, {0, 0, 1}, {0, 1, 0}, {0, 1, 1},
		{1, 0, 0}, {1, 0, 1}, {1, 1, 0}, {1, 1, 1}
	};

	GLint faces[NUM_FACES][4] = {
		{1, 5, 7, 3}, {5, 4, 6, 7}, {4, 0, 2, 6},
		{3, 7, 6, 2}, {0, 1, 3, 2}, {0, 4, 5, 1}
	};
	
	GLfloat vertexColors[NUM_VERTICES][3] = {
		{0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 1.0, 0.0}, {0.0, 1.0, 1.0},
		{1.0, 0.0, 0.0}, {1.0, 0.0, 1.0}, {1.0, 1.0, 0.0}, {1.0, 1.0, 1.0}
	};

	void draw() 
	{
		glBegin(GL_QUADS);
		for (int i = 0; i < NUM_FACES; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				glColor3fv((GLfloat*)&vertexColors[faces[i][j]]);
				glVertex3iv((GLint*)&vertices[faces[i][j]]);
			}
		}
		glEnd();
	}
}

// Display and animation
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	Cube::draw();
	glFlush();
	glutSwapBuffers();
}

// Keep cube stationary and fly camera around it in
// a funky curve
// // Keep cube stationary and fly camera around it in
// a funky curve. Camera always looks at center and we 
// vary the up vector to tumble
void timer(int v)
{
	static GLfloat u = 0.0;
	u+= 0.015;
	glLoadIdentity();
	gluLookAt(8*cos(u), 7*cos(u)-1, 4*cos(u/3)+2, .5, .5, .5, cos(u), 1, 0);
	glutPostRedisplay();
	glutTimerFunc(1000/60.0, timer, v);
}

//recompute settings to match new window shape
//set the viewport to (0,0)-(w,h)
//camera FoV = 60 degrees, aspect ratio w/h
//near clipping plane d=0.5
//clipping plane d=	40
void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, GLfloat(w) / GLfloat(h), 0.5, 40.0);
	glMatrixMode(GL_MODELVIEW);
}

//allow culling on the backside of polygon
void init()
{
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(750, 750);
	glutCreateWindow("The Color Cube");
	glutReshapeFunc(reshape);
	glutTimerFunc(100, timer, 0);
	glutDisplayFunc(display);

	init();
	glutMainLoop();
}






