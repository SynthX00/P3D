#ifndef POOLCUE_H
#define POOLCUE_H

#include "glm.h"

class Poolcue
{
public:
	Poolcue();
	Poolcue(float r, float g, float b, float x, float y, float z, float size);
	~Poolcue();

	void LoadModel();
	void Draw();

private:

	GLMmodel *cueModel;

	float red, green, blue;
	float posX, posY, posZ;
	float size;
};

#endif // !POOLCUE
