#include <iostream>
#include <GL/glut.h>

// Clears window and draws thing
void display() {
	
	glClear(GL_COLOR_BUFFER_BIT);

	// Taurus of outer r = 3 adn inner r = .5
	// 15 stacks and 80 slices
	glColor3f(1.0, 1.0, 1.0);
	glutWireTorus(0.5, 3, 15, 80);

	// Draw a red x, green y, blue z axis. 10 units long
	glBegin(GL_LINES);
		glColor3f(1, 0, 0); glVertex3f(0, 0, 0); glVertex3f(10, 0, 0);
		glColor3f(0, 1, 0); glVertex3f(0, 0, 0); glVertex3f(0, 10, 0);
		glColor3f(0, 0, 1); glVertex3f(0, 0, 0); glVertex3f(0, 0, 10);
	glEnd();

	glFlush();

}

// Set up clear and drawing colors
// projection and modelview matrices
void init() 
{
	// sets current color to black and drawing color = white
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glColor3f(1.0,  1.0, 1.0);
	
	//Camera lens FoV = 60 degrees
	//aspect ratio = 4/3
	//every closer to than 1 unit to the camera and greater
	//than 40 units distance removed
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, 4.0/3.0, 1, 40);

	//Position camera at (4, 6, 5) looking at (0, 0, 0) with the vector 
	// <0, 1, 0> pointing upward
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(4, 6, 5, 0, 0, 0, 0, 1, 0);
}

//Usual main stuff
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutInitWindowPosition(80, 80);
	glutInitWindowSize(800, 800);
	glutCreateWindow("A Simple Torus");
	glutDisplayFunc(display);
	
	init();
	glutMainLoop();
}
