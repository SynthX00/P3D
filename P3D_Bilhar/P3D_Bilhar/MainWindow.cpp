#include <iostream>
#include <gl/freeglut.h>
#include "MainWindow.h"

namespace gameengine {

	int MainWindow::countWindows = 1;

	MainWindow::MainWindow(int x, int y, int width, int height, std::string windowName) : x(x), y(x), screenWidth(width), screenHeight(height), windowName(windowName) {
		if (windowName.empty()) {
			std::ostringstream stringStream;
			stringStream << "Game Window #" << countWindows++;
			windowName = stringStream.str();
		}

		glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
		glutInitWindowPosition(x, y);
		glutInitWindowSize(screenWidth, screenHeight);
		windowId = glutCreateWindow(windowName.c_str());

		/*lighting*/
		light_ambient[0] = 0.1;
		light_ambient[1] = 0.1;
		light_ambient[2] = 0.1;
		light_ambient[3] = 1.0;

		light_diffuse[0] = 1.0;
		light_diffuse[1] = 1.0;
		light_diffuse[2] = 1.0;
		light_diffuse[3] = 1.0;

		light_specular[0] = 1.0;
		light_specular[1] = 1.0;
		light_specular[2] = 1.0;
		light_specular[3] = 1.0;

		light_position[0] = 1.0;
		light_position[1] = 1.0;
		light_position[2] = 1.0;
		light_position[3] = 0.0;

		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);

		glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
		glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

		glLightfv(GL_LIGHT0, GL_POSITION, light_position);
		/*************************/

		/*Materiais*/
		mat_ambient_and_diffuse[0] = 0.4;
		mat_ambient_and_diffuse[1] = 0.4;
		mat_ambient_and_diffuse[2] = 0.4;
		mat_ambient_and_diffuse[3] = 1.0;

		mat_specular[0] = 0.9;
		mat_specular[1] = 0.9;
		mat_specular[2] = 0.9;
		mat_specular[3] = 1.0;

		mat_shininess[0] = 6.0;

		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, mat_ambient_and_diffuse);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
		/**************************/

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);

		glShadeModel(GL_SMOOTH);
		std::cout << "[MainWindow] Create Main Window " << windowId << std::endl;
	}

	MainWindow::~MainWindow() {
		std::cout << "[MainWindow] Destroy Main Window " << windowId << std::endl;
	}
}