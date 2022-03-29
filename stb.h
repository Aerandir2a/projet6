#ifndef STB_H
#define STB_H

#include "header/stb_image.h"
#ifdef __cplusplus
extern "C" {
#endif
	struct stbi__context;

	unsigned char* stbi_xload(stbi__context* s, int* x, int* y, int* frames, int** delays);
	unsigned char* stbi_xload_mem(unsigned char* buffer, int len, int* x, int* y, int* frames, int** delays);
	unsigned char* stbi_xload_file(char const* filename, int* x, int* y, int* frames, int** delays);
#ifdef __cplusplus
}
#endif
#endif