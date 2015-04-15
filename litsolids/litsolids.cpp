#include <iostream>
#include <GL/glut.h>

// Solids placed such that everything is above the x,z plane.
// Rotate scene 20 degrees to see top of objects
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	//rotate so we can see the top of the object
	glRotatef(-20.0, 1.0, 0.0, 0.0);

	// make a taurus floating 0.5 aobve x-z plane.
	// Then, rotate it 90 degree to sit on cone
	glPushMatrix();
	glTranslatef(-0.75, 0.5, 0.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glutSolidTorus(0.275, 0.85, 16, 40);
	glPopMatrix();

	//create cone
	glPushMatrix();
	glTranslatef(-0.75, -0.5, 0.0);
	glRotatef(270.0, 1.0, 0.0, 0.0);
	glutSolidCone(1.0, 2.0, 70, 12);
	glPopMatrix();

	//add sphere
	glPushMatrix();
	glTranslatef(0.75, 0.0, -1.0);
	glutSolidSphere(1.0, 30, 30);
	glPopMatrix();

	glPopMatrix();
	glFlush();
}

//Reshape to maintain proper size around objects
void reshape(GLint w, GLint h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	GLfloat aspect = GLfloat(w) / GLfloat(h);
	glLoadIdentity();
	if (w <= h)
	{
		glOrtho(-2.5, 2.5, -2.5/aspect, 2.5/aspect, -10.0, 10.0);
	} else {
		glOrtho(-2.5*aspect, 2.5*aspect, -2.5, 2.5, -10.0, 10.0);
	}
}

// Performs application specific initialization. If defines lighting
// parameters for light couce GL_LIGHT0: black for ambient, yellow for
// diffuse, white for specualr, and makes it a directional sounce shining
// along <-1, -1, -1>. It also sets a couple material proerties to make
// cyan colored objects with a fairly low shiniess value.  Lighting and 
// depth buffer hidden surface removal are enabled here.
void init()
{
	GLfloat black[]     = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat yellow[]    = { 1.0, 1.0, 0.0, 1.0 };
	GLfloat cyan[]      = { 0.0, 1.0, 1.0, 1.0 };
	GLfloat white[]     = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat direction[] = { 1.0, 1.0, 1.0, 0.0 };
	

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cyan);
	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	glMaterialf(GL_FRONT, GL_SHININESS, 30);

	glLightfv(GL_LIGHT0, GL_AMBIENT, black);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, yellow);
	glLightfv(GL_LIGHT0, GL_SPECULAR, cyan);
	glLightfv(GL_LIGHT0, GL_POSITION, direction);

	glEnable(GL_LIGHTING); //so the renderer considers light
	glEnable(GL_LIGHT0); //turn LIGHT0 on
	glEnable(GL_DEPTH_TEST); // so the renderer considers depth
}

//usual appliaction startip code
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowPosition(80, 80);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Cyan Shapes in Yellow Light");

	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	
	init();
	glutMainLoop();
}


	

	
