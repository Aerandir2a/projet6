#include <SDL.h>
#include "../gc_3d_defs.hpp"
#include "../header/camera.hpp"
#include "../header/controls.hpp"

using namespace GC_3D;

void Camera::CreateCamera(/*SDL_Window* win, GLuint programID, Dirs const& curDirs, int mousePosX, int mousePosY, bool mouseClicRight*/)
{
	//Camera
	ViewMatrix = getViewMatrix();
	/*if (mouseClicRight) {
		SDL_WarpMouseInWindow(win, 1024 / 2, 768 / 2);
		iPosMouse(mousePosX, mousePosY);
	}
	moveCamera(curDirs);*/
	ProjectionMatrix = getProjectionMatrix();
	/*
	glm::mat4 mvp = ProjectionMatrix * ViewMatrix * ModelMatrix;

	// Get a handle for our "MVP" uniform
			// Only during the initialisation
	GLuint MatrixID = glGetUniformLocation(programID, "MVP");

	// Send our transformation to the currently bound shader, in the "MVP" uniform
	// This is done in the main loop since each model will have a different MVP matrix (At least for the M part)
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
	*/
}

void Camera::UpdateCamera(SDL_Window* win, Dirs const& curDirs, int mousePosX, int mousePosY, bool mouseClicRight)
{
	ViewMatrix = getViewMatrix();
	if (mouseClicRight) {
		SDL_WarpMouseInWindow(win, 1024 / 2, 768 / 2);
		iPosMouse(mousePosX, mousePosY);
	}
	moveCamera(curDirs);
	ProjectionMatrix = getProjectionMatrix();
}
