/***********************************PROGRAMA-BASE********************************/
/* Descrição:																	*/
/* Programa base de aplicação OpenGL/freeglut em C++.							*/
/********************************************************************************/

#include "Game1.h"

int main(int argc, char **argv) {

	CreateTable();
	CreateBalls();
	//initLights(); //not doing shit!

	Game1 game;
	int wId = game.gameAddMainWindow(0, 0, 800, 600, "Main Window 1");
	load_tga_image();
	game.gameCameraSetPosition(wId, 2.0f/*eyex*/, 10.0f/*eyey*/, 15.0f/*eyez*/, 0.0f/*lookatx*/, 0.1f/*lookaty*/, 1.0f/*lookatz*/, 0.0f, 1.0f, 0.0f);
	//game.gameCameraSetPosition(wId, 0.0f/*eyex*/, 0.0f/*eyey*/, 0.0/*eyez*/, 0.0/*lookatx*/, 0.0/*lookaty*/, 0.0/*lookatz*/, 0.0, 1.0, 0.0);
	game.gameSetWindowCallbacks(wId);

	// Esta função é geral para o freeglut
	/*glutIdleFunc([](void) {
		// Colocar aqui o código que se pretenda executar sempre que não existires outros eventos
	});*/

	// Definir o FPS (É comum a todas as janelas)
	Game::gameSetTimerFPS(100);
	// Inicia o lançamento de eventos de display, para cada janela, de acordo com o FPS definido
	Game::gameTimerRun(wId);

	// Entra no ciclo de gestão da aplicação por eventos
	Game::gameRun();

	return 0;
}