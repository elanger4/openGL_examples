#include <iostream>
#include "GL/glut.h"

// Clears current window and draws a triangle
void display()
{
	// Set every pixel in the frame buffer to the current clear color
	glClear(GL_COLOR_BUFFER_BIT);

	// Drawing is done by specifiying a sequence of vertices. They way the vertices 
	// conncet relate to the arguements of glBegin().  
	// GL_POLYGON constructs a filled polygon
	glBegin(GL_POLYGON);
		glColor3f(1, 0, 0); glVertex3f(-0.6, -0.75, 0.5);
		glColor3f(0, 1, 0); glVertex3f( 0.6, -0.75, 0);
		glColor3f(1, 1, 1.5); glVertex3f(0,     0.75, 0);
	glEnd();

	// Flush drawing command buffer ASAP and drwaw triangle
	glFlush();
}

// Initializes GLUT, the display mode, and main window. REgister callbacks and main event loop
int main(int argc, char** argv)
{
	// Single buffer in RGB
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	// sets position and location of window
	glutInitWindowPosition(80, 80);
	glutInitWindowSize(400, 300);
	glutCreateWindow("A Simple Triangle");

	// i.e., whener the window needs to be repainted, refer to display()
	glutDisplayFunc(display);

	// Tell GLUT to start working.  No return on this function.  Window is only closed by user
	glutMainLoop();
}


