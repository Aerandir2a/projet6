#pragma once

struct SDL_Window;
struct Dirs;

class Camera 
{
public :
	glm::mat4 ViewMatrix;
	glm::mat4 ProjectionMatrix;

	void CreateCamera();
	void UpdateCamera(SDL_Window* win, Dirs const& curDirs, int mousePosX, int mousePosY, bool mouseClicRight);
};

