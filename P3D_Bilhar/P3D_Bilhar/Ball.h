#pragma once

class Ball
{
public:
	Ball(float r, float g, float b, float x, float y, float z, float size);
	~Ball();

	void Draw();

private:
	float red, green, blue;
	float posX, posY, posZ;
	float size;
};