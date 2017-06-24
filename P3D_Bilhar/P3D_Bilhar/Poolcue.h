#ifndef POOLCUE_H
#define POOLCUE_H

#include "glm.h"

class Poolcue
{
public:
	Poolcue();
	Poolcue(float r, float g, float b, float alpha, float x, float y, float z, float size);
	~Poolcue();

	void LoadModel();
	void Draw();

private:

	GLMmodel *cueModel;

	float red, green, blue, alpha;
	float posX, posY, posZ;
	float size;
};

#endif // !POOLCUE
