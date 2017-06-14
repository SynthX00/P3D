#include <gl/freeglut.h>
#include <iostream>
#include "Ball.h"

Ball::Ball(float r, float g, float b, float x, float y, float z, float size) :
	red(r), green(g), blue(b), posX(x), posY(y), posZ(z), size(size){

	std::cout << "Cria bola\n";
}

Ball::~Ball() {
	std::cout << "Destroi bola\n";
}

void Ball::Draw() {
	//glLoadIdentity();
	glColor3f(red, green, blue);
	glTranslatef(posX, posY, posZ);
	glutWireSphere(size, 60, 60);
}