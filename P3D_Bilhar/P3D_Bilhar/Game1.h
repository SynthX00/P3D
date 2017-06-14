#pragma once

#include<vector>
#include "Game.h"
#include "Ball.h"
#include "Pooltable.h"

using namespace gameengine;
using namespace std;

Pooltable table;
std::vector<Ball>balls;


static float angle = 0.0;
static float red = 1.0, blue = 1.0, green = 1.0;

static float oldX, oldY;
static bool rot = false;
static float theta = 0, phi = 0;

void CreateTable() {
	
	table = Pooltable(0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,10.0f);
	table.LoadModel();
}

void initLights(void) {
	// Define a luz ambiente global
	GLfloat global_ambient[] = { 0.1f, 0.1f, 0.1f, 1.0f };
	// Define a luz light0. Existem 8 fontes de luz no total.
	GLfloat light0_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat light0_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	GLfloat light0_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	// Define a luz light1. Existem 8 fontes de luz no total.
	GLfloat light1_ambient[] = { 0.1f, 0.1f, 0.1f, 1.0f };
	GLfloat light1_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat light1_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat spot_angle = 45.0f;
	GLfloat spot_exp = 12.0f; // Maior valor = maior concentração de luz no centro

							  // Fonte de luz ambiente
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);

	// Fonte de luz posicional
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.1f);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.05f);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.05f);

	// Fonte de luz cónica
	glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, spot_angle);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, spot_exp);

	// Activa a utilização de iluminação
	glEnable(GL_LIGHTING);
	// Activa a fonte de luz light0
	glEnable(GL_LIGHT0);
	// Activa a fonte de luz light1
	glEnable(GL_LIGHT1);
}

void applylights(void) {
	// Define a posição de light0
	GLfloat light0_position[] = { 0.0f, 3.0f, 0.0f, 1.0f };
	// Define a posição de direcção de light1
	GLfloat spot_position[] = { 0.0f, 3.0f, -10.0f, 1.0f };
	GLfloat spot_direction[] = { 0.0f, -1.0f, 0.0f };

	// Aplica a light0
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);

	// Aplica a light1
	glLightfv(GL_LIGHT1, GL_POSITION, spot_position);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);

	glDisable(GL_LIGHTING);
	glEnable(GL_LIGHTING);
}

void applymaterial(int type) {
	// Define as propriedades dos materiais
	// Type: 0 (Branco); 1 (Amarelo); 2 (Ciano); 3 (Branco-Emissor)
	GLfloat mat_ambient[4][4] = { { 1.0f, 1.0f, 1.0f, 1.0f },{ 1.0f, 1.0f, 0.0f, 1.0f },{ 0.0f, 1.0f, 1.0f, 1.0f },{ 1.0f, 1.0f, 1.0f, 1.0f } };
	GLfloat mat_diffuse[4][4] = { { 0.5f, 0.5f, 0.5f, 1.0f },{ 0.5f, 0.5f, 0.0f, 1.0f },{ 0.0f, 0.5f, 0.5f, 1.0f },{ 0.5f, 0.5f, 0.5f, 1.0f } };
	GLfloat mat_specular[4][4] = { { 1.0f, 1.0f, 1.0f, 1.0f },{ 1.0f, 1.0f, 0.0f, 1.0f },{ 0.0f, 1.0f, 1.0f, 1.0f },{ 1.0f, 1.0f, 1.0f, 1.0f } };
	GLfloat mat_emission[4][4] = { { 0.0f, 0.0f, 0.0f, 0.0f },{ 0.0f, 0.0f, 0.0f, 0.0f },{ 0.0f, 0.0f, 0.0f, 0.0f },{ 1.0f, 1.0f, 1.0f, 1.0f } };
	GLfloat mat_shininess[4][1] = { { 20.0f },{ 20.0f },{ 20.0f },{ 20.0f } };

	if ((type >= 0) && (type < 4))
	{
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient[type]); // GL_FRONT, GL_FRONT_AND_BACK , GL_BACK, 
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse[type]);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular[type]);
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, mat_emission[type]);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess[type]);
	}
}

void CreateBalls() {

	int count=0;
	float y = 3.0f;


	balls.push_back(Ball(1.0f, 1.0f, 1.0f, -10.0f, y, 15.0f, 0.5f));

	for (int i = 0; i <= 5; i++)
	{
		for (int j = 0; j < i; j++)
		{
			if (count % 2)
			{
				balls.push_back(Ball(1.0f,0.0f,0.0f,j*1.0f,y,i*1.0f,0.5f));
			}
			else if (count == 12)
			{
				balls.push_back(Ball(0.0f, 0.0f, 0.0f, j*1.0f, y, i*1.0f, 0.5f));
			}
			else
			{
				balls.push_back(Ball(0.0f, 0.0f, 1.0f, j*1.0f, y, i*1.0f, 0.5f));
			}
			count++;
		}
	}

	/*Ball ball(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	balls.push_back(ball);*/
}

void drawSceneGame1(void) {

	//draw table
	glPushMatrix();
	table.Draw();
	glPopMatrix();

	//draw balls
	for (vector<Ball>::iterator it = balls.begin(); it != balls.end(); it++){
		glPushMatrix();
		glRotatef(60, 0.0f, 1.0f, 0.0f);
		glTranslatef(-10.0f, 0.0f, -5.0f);

		it->Draw();
		glPopMatrix();
	}

}

class Game1 : public Game { public: void gameSetWindowCallbacks(int windowID); };

void Game1::gameSetWindowCallbacks(int windowID) {
	for (int i = 0; i < int(gameMainWindows.size()); i++) {
		if (gameMainWindows[i].windowId == windowID) {
			glutSetWindowData((void *)&gameMainWindows[i]);
			break;
		}
	}

	glutDisplayFunc([](void) {
		MainWindow *currentWindow = (MainWindow *)glutGetWindowData();
		glutSetWindow(currentWindow->windowId);
		if (currentWindow->windowId == 1)
			currentWindow->windowId = currentWindow->windowId;
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		currentWindow->camera.cameraUpdate(theta, phi);

		drawSceneGame1();

		glutSwapBuffers();
	});

	glutReshapeFunc([](int w, int h) {
		MainWindow *currentWindow = (MainWindow *)glutGetWindowData();
		glutSetWindow(currentWindow->windowId);

		// Previne a divisão por zero
		if (h == 0) h = 1;
		double ratio = 1.0 * double(w) / double(h);

		// O viewport ocupará toda a janela
		glViewport(0, 0, w, h);

		// Efetua o reset do sistema de coordenadas
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		// Aplica a perspectiva
		gluPerspective(45.0, ratio, 0.1, 100.0);

		// Altera o sistema de coordenadas, para GL_MODELVIEW
		glMatrixMode(GL_MODELVIEW);
	});

	glutKeyboardFunc([](unsigned char key, int x, int y) {
		MainWindow *currentWindow = (MainWindow *)glutGetWindowData();
		glutSetWindow(currentWindow->windowId);

		if (key == 27 /* ESC */) glutLeaveMainLoop();

	});

	glutKeyboardUpFunc([](unsigned char key, int x, int y) {
		
	});

	glutSpecialFunc([](int key, int x, int y) {
		if (key == GLUT_KEY_F1) glutFullScreen();
		if (key == GLUT_KEY_F2) glutReshapeWindow(800, 600);
		
		MainWindow*currentwindow = (MainWindow *)glutGetWindowData();
		glutSetWindow(currentwindow->windowId);

			switch (key)
			{
			case GLUT_KEY_LEFT:
				currentwindow->camera.cameraPan(-0.01);
					break;
			case GLUT_KEY_RIGHT:
				currentwindow->camera.cameraPan(0.01);
				break;
			case GLUT_KEY_UP:
				currentwindow->camera.cameraTilt(0.01);
				break;
			case GLUT_KEY_DOWN:
				currentwindow->camera.cameraTilt(-0.01);
				break;
			default:
				break;
			}

	});


	glutSpecialUpFunc([](int key, int x, int y) {
		MainWindow*currentwindow = (MainWindow *)glutGetWindowData();
		glutSetWindow(currentwindow->windowId);
		switch (key)
		{
		case GLUT_KEY_LEFT:
			currentwindow->camera.cameraPan(0);
			break;
		case GLUT_KEY_RIGHT:
			currentwindow->camera.cameraPan(0);
			break;
		case GLUT_KEY_UP:
			currentwindow->camera.cameraTilt(0);
			break;
		case GLUT_KEY_DOWN:
			currentwindow->camera.cameraTilt(0);
			break;
		default:
			break;
		}
	});

	glutMouseFunc([](int button, int state, int x, int y) {

		/*rot = false;
		if (button == GLUT_LEFT_BUTTON)
		{
			oldX = x;
			oldY = y;
			rot = true;
		}*/
	});

	glutMotionFunc([](int x, int y) {
		/*if (rot)
		{
			theta += (x - oldX)*0.01;
			phi += (y - oldY)*0.01;
		}
		oldX = x;
		oldY = y;
		glutPostRedisplay();*/
	});

	glutPassiveMotionFunc([](int x, int y) {

	});

	glutEntryFunc([](int state) {

	});

	glutMouseWheelFunc([](int wheel, int direction, int x, int y) {
		MainWindow*currentwindow = (MainWindow *)glutGetWindowData();
		glutSetWindow(currentwindow->windowId);
		if (direction < 0)
		{
			currentwindow->camera.cameraMove(-20);
		}
		else if (direction>0)
		{
			currentwindow->camera.cameraMove(20);
		}
		glutPostRedisplay();
	});
}
