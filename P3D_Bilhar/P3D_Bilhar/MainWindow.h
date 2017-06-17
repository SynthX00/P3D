#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include "Camera.h"

namespace gameengine {

	class MainWindow {
	public:
		MainWindow(int x, int y, int width, int height, std::string windowName = "");
		~MainWindow();

		int windowId;
		Camera camera;
		int x, y, screenWidth, screenHeight;
		
		GLfloat light_ambient[4];
		GLfloat light_diffuse[4];
		GLfloat light_specular[4];
		GLfloat light_position[4];

		GLfloat mat_ambient_and_diffuse[4];
		GLfloat mat_specular[4];
		GLfloat mat_shininess[1];

	private:
		static int countWindows;
		std::string windowName;

		

	};
}