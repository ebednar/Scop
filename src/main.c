/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebednar <ebednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/15 21:39:20 by ebednar           #+#    #+#             */
/*   Updated: 2020/11/05 20:09:25 by ebednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void	free_mem(t_render *rend, t_matrices *mat)
{
	free(mat->model_mat);
	free(mat->view_mat);
	free(mat->proj_mat);
	free(mat->rot_mat);
	free(mat->look_at);
	free(mat);
	free(rend->cam->direction);
	free(rend->cam->front);
	free(rend->cam->pos);
	free(rend->cam->up);
	free(rend->cam->right);
	free(rend->cam);
	glDeleteProgram(rend->shader.mod_shader);
	glDeleteProgram(rend->shader.light_shader);
	free(rend);
	glfwTerminate();
}

int			main(int argc, char **argv)
{
	t_render	*rend;
	t_matrices	*mat;
	t_model		*mod;

	if (argc != 2)
		error(5);
	init_glfw();
	if (!(rend = (t_render *)malloc(sizeof(t_render))))
		error(4);
	if (!(mat = (t_matrices *)malloc(sizeof(t_matrices))))
		error(4);
	if (!(mod = (t_model *)malloc(sizeof(t_model))))
		error(4);
	make_context(rend);
	load_model(mod, argv[1]);
	init_base_data(rend, mat, mod);
	while (!glfwWindowShouldClose(rend->window))
	{
		key_callback(rend);
		draw_cycle(rend, mat, mod);
		do_movement(rend, rend->delta_time);
		glfwPollEvents();
	}
	free_mem(rend, mat);
	return (0);
}
