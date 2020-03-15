/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebednar <ebednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/15 21:39:20 by ebednar           #+#    #+#             */
/*   Updated: 2020/03/15 22:25:34 by ebednar          ###   ########.fr       */
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
	exit(code);
}

int		main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
    if (!glfwInit())
        Error(1);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        Error(2);
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
	ft_putendl((char *)glGetString(GL_VERSION));
	float pos[6] = {
		-0.5f, -0.5f,
		0.0f,  0.5f,
		0.5f, -0.5f
	};

	unsigned int buffer;
	glGenBuffers(1, &buffer);
	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), pos, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
	
	unsigned int shader = CreateShader();
	
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
		/* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shader);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0); 

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    glfwTerminate();
	return 0;
}
