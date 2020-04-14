#include "scop.h"

void	drawFrame(render* rend, matrices* mat, unsigned int vao, model* mod)
{
	glUseProgram(rend->shader.modShader);
	glUniform3f(glGetUniformLocation(rend->shader.modShader, "u_lightSwitch"), rend->lightSwitch[0], rend->lightSwitch[1], rend->lightSwitch[2]);
	glUniform1i(glGetUniformLocation(rend->shader.modShader, "u_state"), rend->state);
	glUniform3f(glGetUniformLocation(rend->shader.modShader, "u_viewPos"), rend->cam->pos[0], rend->cam->pos[1], rend->cam->pos[2]);
	glUniform3f(glGetUniformLocation(rend->shader.modShader, "spotLight.direction"), rend->cam->front[0], rend->cam->front[1], rend->cam->front[2]);
	glBindVertexArray(vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rend->iboID);
	glBindTexture(GL_TEXTURE_2D, rend->texture);
	camera_(rend->cam, mat);
	glUniformMatrix4fv(glGetUniformLocation(rend->shader.modShader, "u_P"), 1, GL_TRUE, mat->projMat);
	glUniformMatrix4fv(glGetUniformLocation(rend->shader.modShader, "u_V"), 1, GL_TRUE, mat->lookAt);
	translateMatrix(mat->modelMat, rend->x, rend->y, rend->z);
	rotateMatrix(mat->modelMat, rend->angX, rend->angY, rend->angZ);
	glUniformMatrix4fv(glGetUniformLocation(rend->shader.modShader, "u_M"), 1, GL_TRUE, mat->modelMat);
	glDrawElements(GL_TRIANGLES, mod->iCount * 3, GL_UNSIGNED_INT, 0);
	// int i = -1;
	// while (++i < 10)
	// {
	// 	translateMatrix(mat->modelMat, 2.0f * (i % 4), 0.0f, 2.0f * (i / 3));
	// 	float angle = 20.0f * i;
	// 	rotateYMatrix(mat->modelMat, angle);
	// 	angle = 10.0f * i;
	// 	rotateXMatrix(mat->modelMat, angle);
	// 	rotateZMatrix(mat->modelMat, (float)glfwGetTime() * 40.0f);
	// 	glUniformMatrix4fv(glGetUniformLocation(rend->shader.modShader, "u_M"), 1, GL_TRUE, mat->modelMat);
	// 	glDrawElements(GL_TRIANGLES, mod->iCount * 3, GL_UNSIGNED_INT, 0);
	// }
}

void	drawPointLight(render* rend, matrices* mat, unsigned int vao, model* mod)
{
	glUseProgram(rend->shader.lightShader);
	glUniform1i(glGetUniformLocation(rend->shader.lightShader, "u_Texture"), 0);
	glBindVertexArray(vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rend->iboID);
	glUniformMatrix4fv(glGetUniformLocation(rend->shader.lightShader, "u_P"), 1, GL_TRUE, mat->projMat);
	glUniformMatrix4fv(glGetUniformLocation(rend->shader.lightShader, "u_V"), 1, GL_TRUE, mat->lookAt);
	translateMatrix(mat->modelMat, 2.5, 1.0, 1.5);
	scaleMatrix(mat->modelMat, 0.25, 0.25, 0.25);
	glUniformMatrix4fv(glGetUniformLocation(rend->shader.lightShader, "u_M"), 1, GL_TRUE, mat->modelMat);
	glDrawElements(GL_TRIANGLES, mod->iCount * 3, GL_UNSIGNED_INT, 0);
}