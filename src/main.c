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
	free(mat->modelMat);
	free(mat->viewMat);
	free(mat->projMat);
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
	ft_putendl((char *)glGetString(GL_VERSION));
	float pos[] = {
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f, 0.0f, 1.0f
	};
	unsigned int indicies[] = {
		0, 1, 2,
		2, 3, 0
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

	IndexBuffer(ib, indicies, 6);

	unsigned int texture = LoadImage("res/textures/stones.bmp");

	unsigned int shader = CreateShader();
	int location = glGetUniformLocation(shader, "u_Color");
	int texCoord = glGetUniformLocation(shader, "u_Texture");
	int ortmatlocation = glGetUniformLocation(shader, "u_MVP");

	glBindVertexArray(0);
	glUseProgram(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	float r = 0.0f;
	float increment = 0.05f;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
		/* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.1f, 0.2f, 0.4f, 1.0f);
		
		glUseProgram(shader);
		glUniform4f(location, r, 1 - r, 0.5f, 1.0f);
		glUniform1i(texCoord, 0);

		glBindVertexArray(VAO);
		BindIndex(ib->renderID);
		glBindTexture(GL_TEXTURE_2D, texture);

		ViewMatrix(mat, 0.0, 0.0, -10.0);
		ModelMatrix(mat, 0.0, 0.0, -2.0);
		MultyplyMat(mat->vp, mat->projMat, mat->viewMat);
		MultyplyMat(mat->mvp, mat->vp, mat->modelMat);
		glUniformMatrix4fv(ortmatlocation, 1, GL_TRUE, mat->mvp);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		ModelMatrix(mat, 1.0, 1.0, 0.0);
		MultyplyMat(mat->mvp, mat->vp, mat->modelMat);
		glUniformMatrix4fv(ortmatlocation, 1, GL_TRUE, mat->mvp);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0); 

		if (r > 1.0f)
			increment = -0.05f;
		else if (r < 0.0f)
			increment = 0.05f;
		r += increment;
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
