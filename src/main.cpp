#define _USE_MATH_DEFINES
#include <cstdio>
#include <math.h>
#include <GL/glut.h>



#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

const int CENTER_X = WINDOW_WIDTH / 2;
const int CENTER_Y = WINDOW_HEIGHT / 2;

const int FRAME_TIME = 1000 / 30;



void onTimerTick(int step);
void onDisplay();
void onMouseClick(int button, int state, int x, int y);
void onMouseMove(int x, int y);


// Posicao onde a camera foca
GLdouble lookX = 0.0;
GLdouble lookY = 0.0;
GLdouble lookZ = 0.0;

int up = 1;

// Parametrização em coordenadas esféricas
GLdouble r = 2;		 // Distância do entre o observador (camera) e o ponto
GLdouble theta = 0.0;	 // valores entre 0 a 2pi
GLdouble phi   = 0.0; // valores entre 0 a pi

// Estado do mouse
bool is_pressed = false;
int mouseX = CENTER_X;
int mouseY = CENTER_Y;

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(300, 100);
	glutCreateWindow("Trabalho 3");

	glEnable(GL_DEPTH_TEST);

	glutTimerFunc(FRAME_TIME, onTimerTick, 0);
	glutDisplayFunc(onDisplay);
	glutMouseFunc(onMouseClick);
	glutMotionFunc(onMouseMove);
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


	// Parte 1: desenha os cubos no "mundo" 3d
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(
			60.0,     // angulo vertical de abertura
			(double) WINDOW_WIDTH / WINDOW_HEIGHT, // aspecto (proporcao largura/altura)
			1.0,     // distancia minima da origem(camera) para o pixel poder ser desenhado
			1000.0); // distancia maxima da origem(camera) para o pixel poder ser desenhado


	double upx, upy, upz;

	double phi_up = phi + M_PI/2;

	upx = sin(phi_up)*cos(theta);
	upy = sin(phi_up)*sin(theta);
	upz = cos(phi_up);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
			r*sin(phi)*cos(theta), r*sin(phi)*sin(theta), r*cos(phi), // camera
			lookX, lookY, lookZ, // alvo
			upx, upy , upz); // vetor up

    //printf("theta = %f\n", theta);
    //printf("phi   = %f\n", phi);
    /*printf("x     = %f\n", r*sin(phi)*cos(theta));
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
	glClear(GL_DEPTH_BUFFER_BIT); // Pra fazer ele sempre ser desenhado por cima do cubo vermelho
	glTranslatef(lookX, lookY, lookZ);

	glColor3f(0.0f, 0.0f, 0.0f);
	glutWireCube(0.1);

	glColor3f(0.0f, 0.0f, 1.0f);
	glutSolidCube(0.1);



	// Parte 2: desenha o quadrado verde na posicao do mouse
	// Se botar esse trecho antes da parte 1, o cubinho azul eh
	// desenhado por cima do quadrado verde, mas o vermelho nao;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, WINDOW_WIDTH, 0.0, WINDOW_HEIGHT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

	glBegin(GL_QUADS);
	{
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex2f(mouseX + 10, mouseY + 10);
		glVertex2f(mouseX - 10, mouseY + 10);
		glVertex2f(mouseX - 10, mouseY - 10);
		glVertex2f(mouseX + 10, mouseY - 10);
	}
	glEnd();


	glutSwapBuffers();
}



void onMouseClick(int button, int state, int x, int y)
{
	(void) x;
	(void) y;

	if(button == GLUT_LEFT_BUTTON)
	{
		//printf("%d\n", (state == GLUT_DOWN));
		fflush(stdout);
		is_pressed = (state == GLUT_DOWN);

		mouseX = x;
		mouseY = WINDOW_HEIGHT - y;
	}
}

void onMouseMove(int x, int y)
{
	y = WINDOW_HEIGHT - y;

	int deltaX = x - mouseX;
	int deltaY = y - mouseY;
	GLdouble theta_old;
	GLdouble phi_old;

	if(true)
	{

		printf("THETA = %f\n", theta);
		printf("PHI   = %f\n", phi);

		theta_old = theta;
		phi_old = phi;

		theta += (double)(deltaX * (2*M_PI / WINDOW_WIDTH));
		phi   += (double)(deltaY * (2*M_PI / WINDOW_HEIGHT));

		if (phi_old * phi < 0)
			up *= -1;

		if ((phi_old - M_PI) * (phi - M_PI) < 0)
			up *= -1;

		if ((phi_old - 2*M_PI) * (phi - 2*M_PI) < 0)
			up *= -1;

		theta = fmod(theta, 2 * M_PI);
		phi = fmod(phi, 2 * M_PI);

		if (phi < 0)
			phi += 2*M_PI;

		/*if (theta > (2*M_PI))
			theta -= 2*M_PI;
		else if (theta < 0)
			theta += 2*M_PI;

		if (phi > (2*M_PI))
			phi -= 2*M_PI;
		else if (phi < 0)
			phi += 2*M_PI;*/
	}

	mouseX += deltaX;
	mouseY += deltaY;
}
