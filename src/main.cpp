#include <cstdio>
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

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(2, 2, 2,    lookX, lookY, lookZ,    0, 1 ,0);
	//      xyz camera      xyz onde olhar      xyz "para cima"


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
		printf("%d\n", (state == GLUT_DOWN));
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


	if(true)
	{
		lookX += (double) deltaX / 100;
		lookY += (double) deltaY / 100;
	}

	mouseX += deltaX;
	mouseY += deltaY;
}
