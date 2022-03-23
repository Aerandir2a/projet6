#include <SDL_opengl.h>
#pragma one

class Texture {
public:
	GLuint texture;
	void LoadTextureGif(char* path);
	void LoadTexture2D(char* path);
};