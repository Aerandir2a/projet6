#include <GL/glew.h>
#include "Texture.hpp"

void Texture::LoadTextureGif(char* path, char* path2, GLuint tex) {

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D_ARRAY, texture);

	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE);
	glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_RGB, GL_MODULATE);

	anim.LoadGif(path);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D_ARRAY, texture);
	glUniform1i(tex, 0);
	Anim.push_back(anim);

	anim.LoadGif(path2);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D_ARRAY, texture);
	glUniform1i(tex, 0);
	Anim.push_back(anim);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	if (Anim[0].data)
	{
		glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA, Anim[0].x, Anim[0].y, Anim[0].frames, 0, GL_RGBA, GL_UNSIGNED_BYTE, Anim[0].data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	timergif = std::chrono::high_resolution_clock::now();
	frameOfGif = Anim[0].frames;
}

void Texture::LoadTexture2D(char* path) {

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	anim.Load2D(path);

	if (anim.data)
	{
		if (anim.nrChannels == 3) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, anim.x, anim.y, 0, GL_RGB, GL_UNSIGNED_BYTE, anim.data);
		}
		else if(anim.nrChannels == 4){
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, anim.x, anim.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, anim.data);
		}
		glGenerateMipmap(GL_TEXTURE_2D);
	}
}

void Texture::GifTick(GLuint tex, GLuint lay){
	if (frame >= frameOfGif && inAnimation == 1) {
		frame = 0;
		glUniform1i(tex, 0);
		//glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA, x, y, frames, 0, GL_RGBA, GL_UNSIGNED_BYTE, data2);
		frameOfGif = Anim[1].frames;
		inAnimation = 2;
		timergif = std::chrono::high_resolution_clock::now();
	}
	else if (frame >= frameOfGif && inAnimation == 2) {
		frame = 0;
		glUniform1i(tex, 1);
		//glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA, x, y, frames, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		frameOfGif = Anim[0].frames;
		inAnimation = 1;
		timergif = std::chrono::high_resolution_clock::now();
	}

	std::chrono::steady_clock::time_point endTimerGif = std::chrono::high_resolution_clock::now();
	std::chrono::high_resolution_clock::duration timeForGif = endTimerGif - timergif;
	frame = std::chrono::duration_cast<std::chrono::duration<float>>(timeForGif).count() / 0.06;
	glUniform1i(lay, frame);
}
