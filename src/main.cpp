#define _USE_MATH_DEFINES
#include <cstdio>
#include <math.h>
#include <GL/glut.h>
#include "Vector3d.h"



#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

const GLdouble ASPECT = (GLdouble) WINDOW_WIDTH / WINDOW_HEIGHT;
const int CENTER_X = WINDOW_WIDTH / 2;
const int CENTER_Y = WINDOW_HEIGHT / 2;

const int FRAME_TIME = 1000 / 30;



void onTimerTick(int step);
void onDisplay();
void onMouseClick(int button, int state, int x, int y);
void onMouseMove(int x, int y);

// Parametrização em coordenadas esféricas
GLdouble r = 5; // Distância do entre o observador (camera) e o ponto
GLdouble theta = 0.0; // Angulo em torno do eixo Y
GLdouble phi   = 0.0; // Angulo em torno do eixo X relativo a camera

GLdouble turn_speed = 0.5;
GLdouble move_speed = 0.1;
GLdouble move_direction = 0;

Vector3d player = {0, 0, 0};



int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(300, 100);
	glutCreateWindow("Trabalho 3");

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glutTimerFunc(FRAME_TIME, onTimerTick, 0);
	glutDisplayFunc(onDisplay);

	glutSetCursor(GLUT_CURSOR_NONE);
	glutMouseFunc(onMouseClick);
	glutMotionFunc(onMouseMove);
	glutPassiveMotionFunc(onMouseMove);

	glutMainLoop();

	return 0;
}



void onTimerTick(int step)
{
	glutPostRedisplay();
	glutTimerFunc(FRAME_TIME, onTimerTick, step + 1);
}



void onDisplay()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, ASPECT, 1.0, 100.0);


	double phi_up = phi + M_PI/2;

	// Desloca o jogador (move_direction pode ser 0)
	player += move_direction * coords(-move_speed, theta, phi);

	// Calcula vetores da camera
	Vector3d cam_pos = coords(r, theta, phi) + player;
	Vector3d cam_up  = coords(r, theta, phi_up);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
			cam_pos.x, cam_pos.y, cam_pos.z,
			player.x, player.y, player.z,
			cam_up.x, cam_up.y , cam_up.z);

    /*
	printf("theta = %f\n", theta);
    printf("phi   = %f\n", phi);
    printf("x     = %f\n", r*sin(phi)*cos(theta));
	printf("y     = %f\n", r*sin(phi)*sin(theta));
    printf("z     = %f\n", r*cos(theta));
	*/


	glLineWidth(1);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
		glVertex3f(-100.0, 0.0, 0.0);
		glVertex3f(100, 0, 0);
	glEnd();

	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINES);
		glVertex3f(0.0, -100.0, 0.0);
		glVertex3f(0.0, 100.0, 0);
	glEnd();

	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINES);
		glVertex3f(0.0, 0.0, -100.0);
		glVertex3f(0.0, 0.0, 100.0);
	glEnd();


	// Desenha o cubo vermelho de tamanho 1, na posicao (0, 0, 0)
	glColor3f(0.0f, 0.0f, 0.0f);
	glutWireCube(1.0);

	glColor3f(1.0f, 0.0f, 0.0f);
	glutSolidCube(1.0);


	// Desenha o cubo azul na posicao em que a camera esta olhando
	glTranslatef(player.x, player.y, player.z);

	glColor3f(0.0f, 0.0f, 0.0f);
	glutWireCube(0.5);

	glColor3f(0.0f, 0.0f, 1.0f);
	glutSolidCube(0.5);

	glutSwapBuffers();
}


void onMouseClick(int button, int state, int x, int y)
{
	(void) x;
	(void) y;

	if(button == GLUT_LEFT_BUTTON)
	{
		// Anda para frente
		move_direction = 1.0 * (state == GLUT_DOWN);
	}
	else if(button == GLUT_RIGHT_BUTTON)
	{
		// Anda para tras
		move_direction = (-1.0) * (state == GLUT_DOWN);
	}
}

void onMouseMove(int x, int y)
{
	int centerX = WINDOW_WIDTH / 2;
	int centerY = WINDOW_HEIGHT / 2;

	// Converte a partir das coordenadas do dispositivo
	y = WINDOW_HEIGHT - y;

	int deltaX = x - centerX;
	int deltaY = y - centerY;

	printf("THETA = %f\n", theta);
	printf("PHI   = %f\n", phi);

	theta -= turn_speed * deltaX * (2*M_PI / WINDOW_WIDTH);
	phi   -= turn_speed * deltaY * (2*M_PI / WINDOW_HEIGHT);

	theta = fmod(theta, 2 * M_PI);
	phi = fmod(phi, 2 * M_PI);

	// Mantem o cursor no centro da tela
	if(x != centerX || y != centerY)
	{
		glutWarpPointer(centerX, centerY);
	}
}
