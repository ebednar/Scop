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

void Error(int code)
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

int		main(void)
{
	GLFWwindow* window;
	vertexBuf* vb;
	indexBuf* ib;

	if (!(vb = (vertexBuf *)malloc(sizeof(vertexBuf))))
		Error(4);
	if (!(ib = (indexBuf *)malloc(sizeof(indexBuf))))
		Error(4);
	initGLFW();
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(960, 540, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        Error(2);
    }
    /* Make the window's context current */
	MakeContext(window);
	ft_putendl((char *)glGetString(GL_VERSION));
	float pos[] = {
		100.5f, 100.5f, 0.0f, 0.0f,
		200.5f, 100.5f, 1.0f, 0.0f,
		200.5f, 200.5f, 1.0f, 1.0f,
		100.5f, 200.5f, 0.0f, 1.0f
	};
	unsigned int indicies[] = {
		0, 1, 2,
		2, 3, 0
	};
	float* ortMat = OrtMatrix();
	float* viewMat = ViewMatrix();
	float* mvp = MultyplyMat(ortMat, viewMat);
	unsigned int  VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	VertexBuffer(vb, pos, 4 * 4 * sizeof(float));

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT,GL_FALSE, 4 * sizeof(float), (GLvoid*)(2 * sizeof(GLfloat)));

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
		
		glUseProgram(shader);
		glUniform4f(location, r, 1 - r, 0.5f, 1.0f);
		glUniform1i(texCoord, 0);
		glUniformMatrix4fv(ortmatlocation, 1, GL_TRUE, mvp);

		glBindVertexArray(VAO);
		BindIndex(ib->renderID);
		glBindTexture(GL_TEXTURE_2D, texture);

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
	glDeleteProgram(shader);
	free(mvp);
	free(vb);
	free(ib);
    glfwTerminate();
	return 0;
}
