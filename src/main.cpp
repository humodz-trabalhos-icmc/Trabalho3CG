#include <GL/glut.h>



#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600



void onDisplay()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor3f(0.0f, 0.0f, 0.0f);
	glutWireCube(1);

	glColor3f(1.0f, 0.0f, 0.0f);
	glutSolidCube(1);

	glutSwapBuffers();
}



int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(300, 100);
	glutCreateWindow("Trabalho 3");

	glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0f, 4.0f / 3.0f, 1.0f, 1000.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(2, 2, 2,    0, 0, 0,    0, 1 ,0);



	glutDisplayFunc(onDisplay);
	glutMainLoop();

	return 0;
}
