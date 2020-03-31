#include "scop.h"

void	VertexBuffer(vertexBuf* vb, const void* data, unsigned int size)
{
	glGenBuffers(1, &vb->renderID);
	glBindBuffer(GL_ARRAY_BUFFER, vb->renderID);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void	BindBuffer(unsigned int renderID)
{
	glBindBuffer(GL_ARRAY_BUFFER, renderID);
}

void	IndexBuffer(indexBuf* ib, const unsigned int* data, unsigned int count)
{
	glGenBuffers(1, &ib->renderID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib->renderID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}

void	BindIndex(unsigned int renderID)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderID);
}