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

int			main(int argc, char **argv)
{
	render		*rend;
	matrices	*mat;
	model		*mod;

	if (argc != 2)
		error(5);
	initGLFW();
	if (!(rend = (render *)malloc(sizeof(render))))
		error(4);
	if (!(mat = (matrices *)malloc(sizeof(matrices))))
		error(4);
	if (!(mod = (model *)malloc(sizeof(model))))
		error(4);
	makeContext(rend);
	loadModel(mod, argv[1]);
	initBaseData(rend, mat, mod);
	setBuffers(rend, mod);
    while (!glfwWindowShouldClose(rend->window))
    {
		startFrame(rend);
		drawFrame(rend, mat, rend->vao, mod);
		drawPointLight(rend, mat, rend->lightvao, mod);
		unbind();
        glfwSwapBuffers(rend->window);
		do_movement(rend, rend->deltaTime);
        glfwPollEvents();
    }
	freeMem(rend, mat);
    glfwTerminate();
	return 0;
}
