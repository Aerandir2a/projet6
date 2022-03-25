#include <GL/glew.h>
#include "Texture.hpp"


void Texture::LoadTextureGif(char* path) {

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D_ARRAY, texture);

	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE);
	glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_RGB, GL_MODULATE);

	A1.LoadGif(path);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	if (A1.data)
	{
		glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA, A1.x, A1.y, A1.frames, 0, GL_RGBA, GL_UNSIGNED_BYTE, A1.data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
}

void Texture::LoadTexture2D(char* path) {

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	A1.Load2D(path);

	if (A1.data)
	{
		if (A1.nrChannels == 3) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, A1.x, A1.y, 0, GL_RGB, GL_UNSIGNED_BYTE, A1.data);
		}
		else if(A1.nrChannels == 4){
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, A1.x, A1.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, A1.data);
		}
		glGenerateMipmap(GL_TEXTURE_2D);
	}
}