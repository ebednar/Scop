#include "scop.h"

void	unbind()
{
	glBindVertexArray(0);
	glUseProgram(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

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

void	setBuffers(render* rend, model* mod)
{
	glGenVertexArrays(1, &rend->vao);
	glBindVertexArray(rend->vao);
	vertexBuffer(rend, mod->verticies, mod->vCount * 8 * sizeof(float));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)(5 * sizeof(float)));
	indexBuffer(rend, mod->indicies, mod->iCount * 3);
	glBindVertexArray(0);
	glGenVertexArrays(1, &rend->lightvao);
	glBindVertexArray(rend->lightvao);
	glBindBuffer(GL_ARRAY_BUFFER, rend->vboID);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT,GL_FALSE, 8 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
	unbind();
}

void	startFrame(render* rend)
{
		rend->currentFrame = glfwGetTime();
		rend->deltaTime = rend->currentFrame - rend->oldFrame;
		rend->oldFrame = rend->currentFrame;
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}