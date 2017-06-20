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
	load_tga_image("PoolBalluv1.tga", 0);
	load_tga_image("PoolBalluv2.tga", 1);
	load_tga_image("PoolBalluv3.tga", 2);
	load_tga_image("PoolBalluv4.tga", 3);
	load_tga_image("PoolBalluv5.tga", 4);
	load_tga_image("PoolBalluv6.tga", 5);
	load_tga_image("PoolBalluv7.tga", 6);
	load_tga_image("PoolBalluv8.tga", 7);
	load_tga_image("PoolBalluv9.tga", 8);
	load_tga_image("PoolBalluv10.tga", 9);
	load_tga_image("PoolBalluv11.tga", 10);
	load_tga_image("PoolBalluv12.tga", 11);
	load_tga_image("PoolBalluv13.tga", 12);
	load_tga_image("PoolBalluv14.tga", 13);
	load_tga_image("PoolBalluv15.tga", 14);
	//load_tga_image("bottom.tga", 15);
	//load_tga_image("back.tga", 16);
	//load_tga_image("front.tga", 17);
	//load_tga_image("left.tga", 18);
	//load_tga_image("right.tga", 19);
	//load_tga_image("top.tga", 20);
	//skybox();

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

/*void skybox()
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	glPushMatrix();


	glLoadIdentity();

	
	glPushAttrib(GL_ENABLE_BIT);
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_BLEND);

	// vertices branco
	glColor4f(1, 1, 1, 1);

	// render a frente
	glBindTexture(GL_TEXTURE_2D,17);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2f(1, 0); glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2f(1, 1); glVertex3f(-0.5f, 0.5f, -0.5f);
	glTexCoord2f(0, 1); glVertex3f(0.5f, 0.5f, -0.5f);
	glEnd();

	// Render da esquerda
	glBindTexture(GL_TEXTURE_2D,18);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2f(1, 0); glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2f(1, 1); glVertex3f(0.5f, 0.5f, -0.5f);
	glTexCoord2f(0, 1); glVertex3f(0.5f, 0.5f, 0.5f);
	glEnd();

	// Render de tras
	glBindTexture(GL_TEXTURE_2D,16);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2f(1, 0); glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2f(1, 1); glVertex3f(0.5f, 0.5f, 0.5f);
	glTexCoord2f(0, 1); glVertex3f(-0.5f, 0.5f, 0.5f);
	glEnd();

	// Render da direita
	glBindTexture(GL_TEXTURE_2D,19);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2f(1, 0); glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2f(1, 1); glVertex3f(-0.5f, 0.5f, 0.5f);
	glTexCoord2f(0, 1); glVertex3f(-0.5f, 0.5f, -0.5f);
	glEnd();

	// Render de cima
	glBindTexture(GL_TEXTURE_2D, 20);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1); glVertex3f(-0.5f, 0.5f, -0.5f);
	glTexCoord2f(0, 0); glVertex3f(-0.5f, 0.5f, 0.5f);
	glTexCoord2f(1, 0); glVertex3f(0.5f, 0.5f, 0.5f);
	glTexCoord2f(1, 1); glVertex3f(0.5f, 0.5f, -0.5f);
	glEnd();

	// Render de baixo
	
	glBindTexture(GL_TEXTURE_2D, 15);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2f(0, 1); glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2f(1, 1); glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2f(1, 0); glVertex3f(0.5f, -0.5f, -0.5f);
	glEnd();

	glPopAttrib();
	glPopMatrix();
}*/