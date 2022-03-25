#include <SDL_opengl.h>
#include "Animation.hpp"
#include <chrono>
#include <vector>;

#pragma one

class Texture {
public:
	std::vector<Animation> Anim;
	Animation anim;
	GLuint texture;
	int inAnimation = 1;
	int frame = 0;
	int frameOfGif = 0;
	std::chrono::steady_clock::time_point timergif;
	void LoadTextureGif(char* path, char* path2, GLuint tex);
	void LoadTexture2D(char* path);
	void GifTick(GLuint tex, GLuint lay);
};