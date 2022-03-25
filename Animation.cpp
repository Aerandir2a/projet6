#include "stb.h"
#include "Animation.hpp"

Animation Animation::LoadGif(char* path){

	data = stbi_xload_file(path, &x, &y, &frames, &delay);
	return Animation();
}

Animation Animation::Load2D(char* path)
{
	data = stbi_load(path, &x, &y, &nrChannels, 0);
	return Animation();
}
