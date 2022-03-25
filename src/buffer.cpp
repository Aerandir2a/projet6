#include "../header/buffer.hpp"

using namespace GC_3D;

void Buffer::CreateBuffer(const GLfloat* iData, size_t iSize)
{
	glGenBuffers(1, &m_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
	glBufferData(GL_ARRAY_BUFFER, iSize, iData, GL_STATIC_DRAW);
}

void Buffer::BindBuffer(int attribut, int iSize)
{
	glEnableVertexAttribArray(attribut);
	glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
	glVertexAttribPointer(
		attribut,
		iSize,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
	);
}