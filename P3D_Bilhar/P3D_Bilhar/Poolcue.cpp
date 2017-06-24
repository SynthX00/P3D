#include <gl/freeglut.h>
#include <iostream>
#include "Poolcue.h"

Poolcue::Poolcue() {}

Poolcue::Poolcue(float r, float g, float b, float alpha, float x, float y, float z, float size) :
	red(r), green(g), blue(b), alpha(alpha), posX(x), posY(y), posZ(z), size(size) {

	std::cout << "Cria taco\n";
}

Poolcue::~Poolcue() {
	std::cout << "***************************destroi taco\n";
}

void Poolcue::LoadModel() {

	cueModel = NULL;

	std::cout << "load model\n";
	if (cueModel == NULL)
	{
		cueModel = glmReadOBJ("data/cue.obj");
		if (cueModel == NULL) { exit(0); }
		else
		{
			glmUnitize(cueModel);
			glmLinearTexture(cueModel);
			glmScale(cueModel, 1);
			glmFacetNormals(cueModel);
			glmVertexNormals(cueModel, 90.0);
		}
	}
}

void Poolcue::Draw() {

	//std::cout << "drawing table\n";
	//glLoadIdentity();
	glTranslatef(posX, posY, posZ);
	glRotatef(90.0, 0.0f, 1.0f, 0.0f);
	glScalef(size, size, size);
	glColor4f(red, green, blue, alpha);
	//glTranslatef(posX, posY, posZ);
	//glPushMatrix
	
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glBlendFunc(GL_SRC_ALPHA, GL_SRC_ALPHA);
	glEnable(GL_BLEND); //Transparencia	
	glmDraw(cueModel, GLM_SMOOTH | GLM_MATERIAL);
	
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);
	glDisable(GL_BLEND);

	//glColor3f(red, green, blue);
	//glTranslatef(posX, posY, posZ);
	/*glBegin(GL_QUADS);
	glVertex3f(-20.0f, -1.0f, -30.0f);
	glVertex3f(-20.0f, -1.0f, 30.0f);
	glVertex3f(20.0f, -1.0f, 30.0f);
	glVertex3f(20.0f, -1.0f, -30.0f);
	glEnd();*/
}