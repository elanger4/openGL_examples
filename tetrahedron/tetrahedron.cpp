#include <iostream>
#include <GL/glut.h>

// Clears window and draws tetrahedron.
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	// draws a plane for the polygon
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINES);
	for (GLfloat i = -2.5; i <= 2.5; i+= 0.25)
	{
		glVertex3f(i,   0, 2.5); glVertex3f(i,    0, -2.5);
		glVertex3f(2.5, 0, i);   glVertex3f(-2.5, 0, i);
	}
	glEnd();

	// Draws shape. Define it as a triangle strip - repeat for the last two vertices
	glBegin(GL_TRIANGLE_STRIP);
		glColor3f(1, 1, 1); glVertex3f(0, 2, 0);
		glColor3f(1, 0, 0); glVertex3f(-1, 0, 1);
		glColor3f(0, 1, 0); glVertex3f(1, 0, 1);
		glColor3f(0, 0, 1); glVertex3f(0, 0, -1.4);
		glColor3f(1, 1, 1); glVertex3f(0, 2, 0);
		glColor3f(1, 0, 0); glVertex3f(-1, 0, 1);
	glEnd();

	glFlush();

}

// Sets up global attributes (clear/drawing color)
// "     "  projection and modelview matrices
// Apparently cleaner to define these operations not in main
void init() 
{
	//Set color to blue and drawing color to white
	glClearColor(0.1, 0.39, 0.88, 1.0);
	glColor3f(1.0, 1.0, 1.0);

	// I have no idea why this is hear, but things don't seem 
	// to work as nice without it
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	//Sets the 'camera lens' such that we have horizontal boundaries 
	//on what we are able to see
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-2, 2, -1.5, 1.5, 1, 40);

	// Sets tetrehderon at origin
	// Rotate it so we can see it better and move it back a bit becuase why not
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0, 0, -3);
	glRotatef(70, 1, 0, 0);
	glRotatef(45, 0, 1, 0);
}

// Initializes GLUT. display mdoe, main window. 
// application initialization and main event loop
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutInitWindowPosition(80, 80);
	glutInitWindowSize(800, 600);
	glutCreateWindow("A Simple Tetrahedron");

	glutDisplayFunc(display);

	init();
	glutMainLoop();
}
