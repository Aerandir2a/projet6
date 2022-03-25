#pragma once

struct Dirs
{
	Dirs()
	{
		front = back = left = right = down = up = 0;
	}
	uint32_t front : 1;
	uint32_t back : 1;
	uint32_t left : 1;
	uint32_t right : 1;
	uint32_t up : 1;
	uint32_t down : 1;
};

void computeMatricesFromInputs();
glm::mat4 getViewMatrix();
glm::mat4 getProjectionMatrix();
void moveCamera(Dirs const& iDirs);
void iPosMouse(int xpos, int ypos);
void startPosCamera();
