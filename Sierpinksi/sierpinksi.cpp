#include <iostream>
#include <GL/glut.h>
#include <cstdlib>

// 2d point class to simplfy things
// refernce x and y points instead of an array
// Easy midpoint function
struct Point {
	GLfloat x, y;
	Point(GLfloat x = 0, GLfloat y = 0): x(x), y(y) {}
	Point midpoint(Point p) 
	{
		return Point((x + p.x) / 2.0, (y + p.y) / 2.0);
	}
};

// Draws fancy triangle
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	static Point vertices[] = {Point(0, 0), Point(200, 500), Point(500, 0)};

	// Computes and plots 100,000 new points
	// Each point is midway between the previous point
	// and any an random vertex
	static Point p = vertices[0];
	glBegin(GL_POINTS);
	for (int k = 0; k < 100000; k++)
		{
			p = p.midpoint(vertices[rand() % 3]);
			glVertex2f(p.x, p.y);
		}
	glEnd();

	glFlush();
}

// Sets color and orthographic projection
void init()
{
	// Deep Purple background and draw in greenish yellow
	glClearColor(0.25, 0.0, 0.2, 1.0);
	glColor3f(1.0, 1.0, 0.0);

	// Set up the viewing volume: 500 x 500 x 1 with origin in lower left
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 500.0, 0.0, 500.0, 0.0, 1.0);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutInitWindowSize(1000, 1000);
	glutInitWindowPosition(40, 40);
	glutCreateWindow("Sierpinski Triangle");
	glutDisplayFunc(display);

	init();
	glutMainLoop();
}

