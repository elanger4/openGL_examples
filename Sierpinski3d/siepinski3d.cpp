#include <iostream>
#include <GL/glut.h>
#include <cstdlib>

// 3D point class.
struct Point 
{
	GLfloat x, y, z;
	Point(GLfloat x, GLfloat y, GLfloat z): x(x), y(y), z(z) {}
	Point midpoint(Point p)
	{
		return Point((x+p.x)/2, (y+p.y)/2, (z+p.z)/2);
	}
};

// Handles reshape requests by setting the viewport to exactly
// match the pixel coordinates. Then sets up a simple perspective 
// viewing volume so pyramid will nevre be distorted and will 
// always be visible in the window
void reshape(GLint w, GLint h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(100.0, GLfloat(w)/GLfloat(h), 10.0, 1500.0);
}

// Handles disaply requests
// Clears viewport when real drawing is done in idle callback
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

// Draws 500 pooints.
void generateMorePoints()
{
	// Shape has 4 vertices. Have to keep track of current point when plotting
	static Point vertices[4] = {

		Point(-250, -225, -200),
		Point(-150, -225, -700),
		Point( 250, -225, -275),
		Point( 0,    450, -500),
	};
	
	static Point lastPoint = vertices[0];

	// draws the points.  THe closer to the camera,
	// the brighter the point
	// makes it pretty
	glBegin(GL_POINTS);
	for(int i=0; i <= 500; i++)
	{
		lastPoint = lastPoint.midpoint(vertices[rand() % 4]);
		GLfloat intensity = (700 + lastPoint.z) / 500.0;
		glColor3f(intensity, intensity, 0.25);
		glVertex3f(lastPoint.x, lastPoint.y, lastPoint.z);
	}
	glEnd();
	glFlush();
}

// depth buffering
void init()
{
	glEnable(GL_DEPTH_TEST);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(1000, 1000);
	glutInitWindowPosition(10, 0);
	glutCreateWindow("Sierpinski Tetrahedron");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(generateMorePoints);

	init();
	glutMainLoop();
}

