#include <SDL.h>
#include "../gc_3d_defs.hpp"
#include "../header/camera.hpp"
#include "../header/controls.hpp"

using namespace GC_3D;

void Camera::CreateCamera()
{
	ViewMatrix = getViewMatrix();
	ProjectionMatrix = getProjectionMatrix();
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
