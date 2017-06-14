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
		
	private:
		static int countWindows;
		std::string windowName;
	};
}