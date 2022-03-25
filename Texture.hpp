#include <SDL_opengl.h>
#include "Animation.hpp"
#pragma one

class Texture {
public:
	Animation A1;
	GLuint texture;
	void LoadTextureGif(char* path);
	void LoadTexture2D(char* path);
};