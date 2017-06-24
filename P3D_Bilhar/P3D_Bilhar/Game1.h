#pragma once

#include<vector>
#include "Game.h"
#include "tga.h"
#include "Ball.h"
#include "Pooltable.h"
#include "Poolcue.h"
#include <stdio.h>
#include <gl/freeglut.h>

using namespace gameengine;
using namespace std;

Pooltable table;
Poolcue cue;
std::vector<Ball>balls;

tgaInfo *im;
GLuint texture[15];
GLUquadric *mysolid[15];

static float angle = 0.0;
static float red = 1.0, blue = 1.0, green = 1.0;

static float oldX, oldY;
static bool rot = false;
static float theta = 0, phi = 0;

/*************************************SKYBOX***************************************/
// Protótipos de funções
void init(void);
void initDL(void);
void funcmyDL(void);
void load_cube_images(void);


// Variáveis globais
tgaInfo *image[6];
GLuint textures[6];
int myDL;

//void init(void)
//{
//	// Define técnica de shading: GL_FLAT, GL_SMOOTH
//	glShadeModel(GL_SMOOTH);
//
//	// Activa o teste de profundidade
//	glEnable(GL_DEPTH_TEST);
//
//	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
//	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
//}


void initDL(void)
{
	// Compila o modelo
	funcmyDL();
}

void funcmyDL(void)
{
	myDL = glGenLists(1);

	glNewList(myDL, GL_COMPILE);

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	float x = 25.0f;

	// back
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-x, -x, x);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-x, x, x);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, x, x);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, -x, x);
	glEnd();
	//frente
	glBindTexture(GL_TEXTURE_2D, textures[1]);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-x, -x, -x);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, -x, -x);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, x, -x);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-x, x, -x);
	glEnd();
	//direita
	glBindTexture(GL_TEXTURE_2D, textures[2]);
	glBegin(GL_QUADS);
	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, x, -x);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, -x, -x);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, -x, x);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x, x, x);
	glEnd();
	//esquerda
	glBindTexture(GL_TEXTURE_2D, textures[3]);
	glBegin(GL_QUADS);
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-x, -x, -x);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-x, x, -x);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-x, x, x);
	glTexCoord2f(1.0f,0.0f); glVertex3f(-x, -x, x);
	glEnd();
	// cima
	glBindTexture(GL_TEXTURE_2D, textures[4]);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, x, -x);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x, x, x);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-x, x, x);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-x, x, -x);
	glEnd();
	// baixo
	glBindTexture(GL_TEXTURE_2D, textures[5]);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-x, -x, x);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, -x, x);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, -x, -x);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-x, -x, -x);
	glEnd();

	glEndList();
}


void load_cube_images(void)
{
	char *impathfiles[6] = { "cm_front.tga", "cm_back2.tga", "cm_left.tga", "cm_right.tga", "cm_top.tga", "cm_bottom.tga" };


	// Carrega as imagens de textura
	for (int j = 0; j<6; j++)
	{
		image[j] = tgaLoad(impathfiles[j]);

		printf("IMAGE INFO: %s\nstatus: %d\ntype: %d\npixelDepth: %d\nsize%d x %d\n", impathfiles[j], image[j]->status, image[j]->type, image[j]->pixelDepth, image[j]->width, image[j]->height); fflush(stdout);
	}

	// Cria nomes de texturas
	glGenTextures(6, textures);

	for (int j = 0; j<6; j++)
	{
		// Selecciona uma textura
		glBindTexture(GL_TEXTURE_2D, textures[j]);

		// Selecciona a mistura da textura com a cor
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

		// Cria textura de mipmaps
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, image[j]->width, image[j]->height, GL_RGB, GL_UNSIGNED_BYTE, image[j]->imageData);

	}

	// Destrói as imagens
	for (int j = 0; j<6; j++)
	{
		tgaDestroy(image[j]);
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
}

/*************************************FIM***************************************/

//Objects
void CreateTable() {

	table = Pooltable(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 10.0f);
	table.LoadModel();
}

void CreatePoolCue() {

	cue = Poolcue(0.0f, 0.0f, 0.0f, 0.50f, 0.0f, 0.50f, 0.0f, 1.0f);
	cue.LoadModel();
}

void CreateBalls() {

	int count = 0;
	float size = 0.3;
	float y = 2.5;


	balls.push_back(Ball(1.0f, 1.0f, 1.0f, -6.0f, y, 10.0f, size));

	for (int i = 0; i <= 5; i++)
	{
		for (int j = 0; j < i; j++)
		{
			if (count % 2)
			{
				balls.push_back(Ball(1.0f, 0.0f, 0.0f, j*0.7f, y, i*0.7f, size));
			}
			else if (count == 12)
			{
				balls.push_back(Ball(0.0f, 0.0f, 0.0f, j*0.7f, y, i*0.7f, size));
			}
			else
			{
				balls.push_back(Ball(0.0f, 0.0f, 1.0f, j*0.7f, y, i*0.7f, size));
			}
			count++;
		}
	}

	/*Ball ball(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	balls.push_back(ball);*/
}


//**Objects

//textures
void load_tga_image(char *impathfile, int id) {

	//char impathfile[255] = "PoolBalluv1.tga";

	im = tgaLoad(impathfile);
	printf("IMAGE INFO: %s\nstatus: %d\ntype: %d\npixelDepth: %d\nsize%d x %d\n", impathfile, im->status, im->type, im->pixelDepth, im->width, im->height);

	glGenTextures(1, &texture[id]);

	glBindTexture(GL_TEXTURE_2D, texture[id]);

	//gerar coordenadas automaticamente
	mysolid[id] = gluNewQuadric();
	gluQuadricDrawStyle(mysolid[id], GLU_FILL);
	gluQuadricTexture(mysolid[id], GL_TRUE);
	gluQuadricNormals(mysolid[id], GLU_SMOOTH);
	gluQuadricOrientation(mysolid[id], GLU_OUTSIDE);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, im->width, im->height, 0, GL_RGB, GL_UNSIGNED_BYTE, im->imageData);

	tgaDestroy(im);
}
//**textures

void drawSceneGame1(void) {

	//draw table
	glPushMatrix();
	table.Draw();
	cue.Draw();
	glPopMatrix();

	//draw balls
	int _i = -1;
	for (vector<Ball>::iterator it = balls.begin(); it != balls.end(); it++) {
		glPushMatrix();

		glTranslatef(-2.5f, 0.0f, -5.0f);
		glRotatef(44, 0.0f, 1.0f, 0.0f);

		if (_i == -1)
			it->Draw();
		else
		{
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, texture[_i]);
			it->Draw(mysolid[_i]);
			glDisable(GL_TEXTURE_2D);
		}

		glPopMatrix();
		_i++;
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

		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, currentWindow->mat_ambient_and_diffuse);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, currentWindow->mat_specular);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, currentWindow->mat_shininess);
		drawSceneGame1();

		glEnable(GL_TEXTURE_2D);

		// Cubo
		//init();
		//load_cube_images();
		//initDL();
		glCallList(myDL);
		glDisable(GL_TEXTURE_2D);


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
		//glLoadIdentity();

	});


	glutKeyboardFunc([](unsigned char key, int x, int y) {
		MainWindow *currentWindow = (MainWindow *)glutGetWindowData();
		glutSetWindow(currentWindow->windowId);

		if (key == 27 /* ESC */) glutLeaveMainLoop();

	});

	glutKeyboardUpFunc([](unsigned char key, int x, int y) {

	});

	glutSpecialFunc([](int key, int x, int y) {

		MainWindow*currentwindow = (MainWindow *)glutGetWindowData();
		glutSetWindow(currentwindow->windowId);

		if (key == GLUT_KEY_F1) glutFullScreen();
		if (key == GLUT_KEY_F2) glutReshapeWindow(800, 600);
		if (key == GLUT_KEY_F3) currentwindow->camera.cameraSetPosition(2.0, 10.0, 15.0, 0.0, 0.1, 1.0, 0.0, 1.0, 0.0);

		switch (key)
		{
		case GLUT_KEY_LEFT:
			currentwindow->camera.cameraPan(-0.05);
			break;
		case GLUT_KEY_RIGHT:
			currentwindow->camera.cameraPan(0.05);
			break;
		case GLUT_KEY_UP:
			currentwindow->camera.cameraTilt(0.05);
			break;
		case GLUT_KEY_DOWN:
			currentwindow->camera.cameraTilt(-0.05);
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
