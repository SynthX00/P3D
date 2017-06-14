#pragma once

#include "glm.h"

class Pooltable
{
public:
	Pooltable();
	Pooltable(float r, float g, float b, float x, float y, float z, float size);
	~Pooltable();

	void LoadModel();
	void Draw();

private:

	GLMmodel *tableModel;

	float red, green, blue;
	float posX, posY, posZ;
	float size;
};