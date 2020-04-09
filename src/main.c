/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebednar <ebednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/15 21:39:20 by ebednar           #+#    #+#             */
/*   Updated: 2020/03/15 23:03:53 by ebednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void	freeMem(render* rend, matrices *mat)
{
	unsigned int i;

	i = -1;
	while (++i < mat->modelCount)
		free(mat->modelMat[i]);
	free(mat->modelMat);
	free(mat->viewMat);
	free(mat->projMat);
	free(mat->rotMat);
	free(mat->vp);
	free(mat->mvp);
	free(mat->lookAt);
	free(mat);
	free(rend->cam->direction);
	free(rend->cam->front);
	free(rend->cam->pos);
	free(rend->cam->up);
	free(rend->cam->right);
	free(rend->cam);
	glDeleteProgram(rend->shader.modShader);
	glDeleteProgram(rend->shader.lightShader);
	free(rend);
}

void		error(int code)
{
	if (code == 1)
		ft_putendl("glwf init error");
	if (code == 2)
		ft_putendl("glwf window creation error");
	if (code == 3)
		ft_putendl("can't read file");
	if (code == 4)
		ft_putendl("memory allocation failed");
	if (code == 5)
		ft_putendl("Usage: ./scop [.obj file name]");
	glfwTerminate();
	exit(code);
}

static void unbind()
{
	glBindVertexArray(0);
	glUseProgram(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

int			main(int argc, char **argv)
{
	GLFWwindow	*window;
	render		*rend;
	matrices	*mat;
	model		*mod;

	if (argc != 2)
		/*error(5)*/;
	initGLFW();
    /* Create a windowed mode window and its OpenGL context */
    if (!(window = glfwCreateWindow(WIDTH, HEIGHT, "Hello World", NULL, NULL)))
        error(2);
    /* Make the window's context current */
	makeContext(window);
	if (!(rend = (render *)malloc(sizeof(render))))
		error(4);
	if (!(mat = (matrices *)malloc(sizeof(matrices))))
		error(4);
	if (!(rend->cam = (camera *)malloc(sizeof(camera))))
		error(4);
	if (!(mod = (model *)malloc(sizeof(model))))
		error(4);
	initBaseData(window, rend, mat);
	
	loadModel(mod, argv[1]);

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

	float deltaTime;
	float oldFrame = 0.0;
	float currentFrame;
	glfwSetCursorPos(window, rend->cam->lastX, rend->cam->lastY);
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
		currentFrame = glfwGetTime();
		deltaTime = currentFrame - oldFrame;
		oldFrame = currentFrame;
		/* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

		glUseProgram(rend->shader.modShader);
		glUniform3f(glGetUniformLocation(rend->shader.modShader, "u_lightSwitch"), rend->switchLight[0], rend->switchLight[1], rend->switchLight[2]);
		glUniform3f(glGetUniformLocation(rend->shader.modShader, "u_viewPos"), rend->cam->pos[0], rend->cam->pos[1], rend->cam->pos[2]);
		glUniform3f(glGetUniformLocation(rend->shader.modShader, "spotLight.direction"), rend->cam->front[0], rend->cam->front[1], rend->cam->front[2]);
		glBindVertexArray(rend->vao);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rend->iboID);
		glBindTexture(GL_TEXTURE_2D, rend->texture);
		camera_(rend->cam, mat);

		glUniformMatrix4fv(glGetUniformLocation(rend->shader.modShader, "u_P"), 1, GL_TRUE, mat->projMat);
		glUniformMatrix4fv(glGetUniformLocation(rend->shader.modShader, "u_V"), 1, GL_TRUE, mat->lookAt);

		translateMatrix(mat->modelMat[0], 0.0f, 0.0f, 0.0f);
		rotateZMatrix(mat->modelMat[0], (float)glfwGetTime() * 40.0f);
		glUniformMatrix4fv(glGetUniformLocation(rend->shader.modShader, "u_M"), 1, GL_TRUE, mat->modelMat[0]);
		glDrawElements(GL_TRIANGLES, mod->iCount * 3, GL_UNSIGNED_INT, 0);

		/*int i = -1;
		while (++i < 10)
		{
			translateMatrix(mat->modelMat[0], 2.0f * (i % 4), 0.0f, 2.0f * (i / 3));
			float angle = 20.0f * i;
			rotateYMatrix(mat->modelMat[0], angle);
			angle = 10.0f * i;
			rotateXMatrix(mat->modelMat[0], angle);
			rotateZMatrix(mat->modelMat[0], (float)glfwGetTime() * 40.0f);
			glUniformMatrix4fv(glGetUniformLocation(rend->shader.modShader, "u_M"), 1, GL_TRUE, mat->modelMat[0]);
			glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		}*/
		glBindVertexArray(0);

		/*glUseProgram(rend->shader.lightShader);
		glUniform1i(glGetUniformLocation(rend->shader.lightShader, "u_Texture"), 0);
		glBindVertexArray(rend->lightvao);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rend->iboID);
		glUniformMatrix4fv(glGetUniformLocation(rend->shader.lightShader, "u_P"), 1, GL_TRUE, mat->projMat);
		glUniformMatrix4fv(glGetUniformLocation(rend->shader.lightShader, "u_V"), 1, GL_TRUE, mat->lookAt);
		translateMatrix(mat->modelMat[1], 5.5, 1.0, 1.5);
		scaleMatrix(mat->modelMat[1], 0.25, 0.25, 0.25);
		glUniformMatrix4fv(glGetUniformLocation(rend->shader.lightShader, "u_M"), 1, GL_TRUE, mat->modelMat[1]);

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);*/
		unbind();
        /* Swap front and back buffers */
        glfwSwapBuffers(window);
		do_movement(rend, deltaTime);
        /* Poll for and process events */
        glfwPollEvents();
    }
	freeMem(rend, mat);
    glfwTerminate();
	return 0;
}
