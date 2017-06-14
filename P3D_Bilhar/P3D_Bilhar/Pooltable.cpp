#include <gl/freeglut.h>
#include <iostream>
#include "Pooltable.h"

Pooltable::Pooltable() {}

Pooltable::Pooltable(float r, float g, float b, float x, float y, float z, float size) :
	red(r), green(g), blue(b), posX(x), posY(y), posZ(z), size(size) {

	std::cout << "Cria mesa\n";
}

Pooltable::~Pooltable() {
	std::cout << "***************************destroi mesa\n";
}

void Pooltable::LoadModel() {

	tableModel = NULL;

	std::cout << "load model\n";
	if (tableModel == NULL)
	{
		tableModel = glmReadOBJ("data/pooltableModel.obj");
		if (tableModel == NULL) { exit(0); }
		else
		{
			glmUnitize(tableModel);
			glmLinearTexture(tableModel);
			glmScale(tableModel, 1.0);
			glmFacetNormals(tableModel);
			glmVertexNormals(tableModel, 90.0);
		}
	}
}

void Pooltable::Draw() {

	//std::cout << "drawing table\n";
	//glLoadIdentity();
	//glTranslatef(posX, posY, posZ);
	glRotatef(15, 0.0f, 1.0f, 0.0f);
	glScalef(size, size, size);
	glTranslatef(posX, posY, posZ);
	//glPushMatrix
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glmDraw(tableModel, GLM_SMOOTH | GLM_MATERIAL);
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);

	//glColor3f(red, green, blue);
	//glTranslatef(posX, posY, posZ);
	/*glBegin(GL_QUADS);
	glVertex3f(-20.0f, -1.0f, -30.0f);
	glVertex3f(-20.0f, -1.0f, 30.0f);
	glVertex3f(20.0f, -1.0f, 30.0f);
	glVertex3f(20.0f, -1.0f, -30.0f);
	glEnd();*/
}