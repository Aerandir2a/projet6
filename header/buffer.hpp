#pragma once

#include "../gc_3d_defs.hpp"

class Buffer
{
	unsigned int m_buffer;
	int attribut;

public:
	void CreateBuffer(const GLfloat* iData, size_t iSize);
	void BindBuffer(int attribut, int iSize);

};