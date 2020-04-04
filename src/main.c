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

void		Error(int code)
{
	if (code == 1)
		ft_putendl("glwf init error");
	if (code == 2)
		ft_putendl("glwf window creation error");
	if (code == 3)
		ft_putendl("can't read file");
	if (code == 4)
		ft_putendl("memory allocation failed");
	exit(code);
}

static void	FreeMem(matrices *mat, unsigned int shader)
{
	int i;

	i = -1;
	free(mat->modelMat[0]);
	free(mat->modelMat);
	free(mat->viewMat);
	free(mat->projMat);
	free(mat->rotMat);
	free(mat->vp);
	free(mat->mvp);
	free(mat);
	glDeleteProgram(shader);
}

int			main(void)
{
	GLFWwindow	*window;
	vertexBuf	*vb;
	indexBuf	*ib;
	matrices	*mat;

	if (!(vb = (vertexBuf *)malloc(sizeof(vertexBuf))))
		Error(4);
	if (!(ib = (indexBuf *)malloc(sizeof(indexBuf))))
		Error(4);
	if (!(mat = (matrices *)malloc(sizeof(matrices))))
		Error(4);
	initGLFW();
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(WIDTH, HEIGHT, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        Error(2);
    }
    /* Make the window's context current */
	MakeContext(window);
	glEnable(GL_DEPTH_TEST);
	ft_putendl((char *)glGetString(GL_VERSION));
	float pos[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f
		};
	unsigned int indicies[] = {
		0, 1, 2,
		2, 3, 0,
		4, 5, 6,
		6, 7, 4,
		8, 9, 10,
		10, 11, 8,
		12, 13, 14,
		14, 15, 12,
		16, 17, 18,
		18, 19, 16,
		20, 21, 22,
		22, 23, 20
	};
	InitMat(mat);
	PerspMatrix(mat);
	unsigned int  VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	VertexBuffer(vb, pos, sizeof(pos));

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT,GL_FALSE, 5 * sizeof(float), (GLvoid*)(3 * sizeof(float)));

	IndexBuffer(ib, indicies, 36);

	unsigned int texture = LoadImage("res/textures/cat.bmp");

	unsigned int shader = CreateShader();
	int texCoord = glGetUniformLocation(shader, "u_Texture");
	int ortmatlocation = glGetUniformLocation(shader, "u_MVP");

	glBindVertexArray(0);
	glUseProgram(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
		/* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.1f, 0.2f, 0.4f, 1.0f);
		
		glUseProgram(shader);
		glUniform1i(texCoord, 0);
		glBindVertexArray(VAO);
		BindIndex(ib->renderID);
		glBindTexture(GL_TEXTURE_2D, texture);
		ViewMatrix(mat, 0.0, -1.0, -8.0);

		TranslateMatrix(mat->modelMat[0], 0.0, 0.0, 0.0);
		MultyplyMat(mat->vp, mat->projMat, mat->viewMat);
		RotateYMatrix(mat->modelMat[0], (float)glfwGetTime() * 40.0f);
		RotateZMatrix(mat->modelMat[0], (float)glfwGetTime() * 40.0f);
		MultyplyMat(mat->mvp, mat->vp, mat->modelMat[0]);
		glUniformMatrix4fv(ortmatlocation, 1, GL_TRUE, mat->mvp);

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		
		TranslateMatrix(mat->modelMat[1], 1.0, -1.0, 0.0);
		RotateXMatrix(mat->modelMat[1], (float)glfwGetTime() * 80.0f);
		MultyplyMat(mat->mvp, mat->vp, mat->modelMat[1]);
		glUniformMatrix4fv(ortmatlocation, 1, GL_TRUE, mat->mvp);

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0); 
        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        /* Poll for and process events */
		glfwSetKeyCallback(window, key_callback);
        glfwPollEvents();
    }
	FreeMem(mat, shader);
	free(vb);
	free(ib);
    glfwTerminate();
	return 0;
}
