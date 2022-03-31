#include <GL/glew.h>

#include "stb.h"
#include "Texture.hpp"

void Texture::LoadTextureGif(const char* path) {

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D_ARRAY, texture);

	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE);
	glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_RGB, GL_MODULATE);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	data = stbi_xload_file(path, &x, &y, &frames, &delay);
	timergif = Clock::now();

	if (data)
	{
		glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA, x, y, frames, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}

}

void Texture::LoadTexture2D(const char* path) {

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	data = stbi_load(path, &x, &y, &nrChannels, 0);

	if (data)
	{
		if (nrChannels == 3) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x, y, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		}
		else if(nrChannels == 4){
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		}
		glGenerateMipmap(GL_TEXTURE_2D);
	}
}

void Texture::GifTick(Texture tex, GLuint lay,int* frame){
	auto endTimerGif = Clock::now();
	Duration timeForGif = endTimerGif - tex.timergif;
	*frame = int(Seconds(timeForGif) / 0.06) % tex.frames;
	glUniform1i(lay, *frame);
}

/*void Texture::GifTick(int* frame, int* frameOfGif, int* inAnimation, GLuint tex, GLuint lay, Texture tx1, Texture tx2) {
	if (*frame >= *frameOfGif && *inAnimation == 1) {
		*frame = 0;
		glUniform1i(tex, 0);
		//glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA, x, y, frames, 0, GL_RGBA, GL_UNSIGNED_BYTE, data2);
		*frameOfGif = tx2.frames;
		*inAnimation = 2;
		tx1.timergif = Clock::now();
	}
	else if (*frame >= *frameOfGif && *inAnimation == 2) {
		*frame = 0;
		glUniform1i(tex, 1);
		//glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA, x, y, frames, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		*frameOfGif = tx1.frames;
		*inAnimation = 1;
		tx1.timergif = Clock::now();
	}

	Timestamp endTimerGif = Clock::now();
	Duration timeForGif = endTimerGif - tx1.timergif;
	*frame = Seconds(timeForGif) * 10;
	glUniform1i(lay, *frame);
}*/