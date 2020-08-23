/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebednar <ebednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/15 21:39:20 by ebednar           #+#    #+#             */
/*   Updated: 2020/08/23 15:36:50 by ebednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void	free_mem(render *rend, matrices *mat)
{
	free(mat->modelMat);
	free(mat->viewMat);
	free(mat->projMat);
	free(mat->rotMat);
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
	glfwTerminate();
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
	while (!glfwWindowShouldClose(rend->window))
	{
		startFrame(rend);
		drawCycle(rend, mat, mod);
		do_movement(rend, rend->deltaTime);
		glfwPollEvents();
	}
	free_mem(rend, mat);
	return (0);
}
