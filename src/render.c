#include "scop.h"

void	vertexBuffer(render* rend, const void* data, unsigned int size)
{
	glGenBuffers(1, &rend->vboID);
	glBindBuffer(GL_ARRAY_BUFFER, rend->vboID);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void	indexBuffer(render* rend, const unsigned int* data, unsigned int count)
{
	glGenBuffers(1, &rend->iboID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rend->iboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}
