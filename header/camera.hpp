#pragma once

struct SDL_Window;
struct Dirs;

class Camera 
{
public :
	void CreateCamera(SDL_Window* win, GLuint programID, Dirs const& curDirs, int mousePosX, int mousePosY, bool mouseClicRight);
};

