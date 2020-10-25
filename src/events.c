/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebednar <ebednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/15 23:02:39 by ebednar           #+#    #+#             */
/*   Updated: 2020/10/23 22:29:32 by ebednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void	switch_scene(t_render *rend)
{
	if (rend->keys[GLFW_KEY_SPACE] && !rend->fkeys[GLFW_KEY_SPACE])
	{
		rend->wire *= -1;
		if (rend->wire == -1)
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		rend->fkeys[GLFW_KEY_SPACE] = 1;
	}
	if (rend->keys[GLFW_KEY_TAB] && !rend->fkeys[GLFW_KEY_TAB])
	{
		rend->scene *= -1;
		if (rend->scene == -1)
			start_pos(rend);
		rend->fkeys[GLFW_KEY_TAB] = 1;
	}
}

void		key_callback(t_render *rend)
{
	int i;

	i = -1;
	while (++i <= 1024)
	{
		if (glfwGetKey(rend->window, i) == GLFW_PRESS && !rend->keys[i])
			rend->keys[i] = 1;
		else if (glfwGetKey(rend->window, i) == GLFW_RELEASE && rend->keys[i])
		{
			rend->keys[i] = 0;
			rend->fkeys[i] = 0;
		}
	}
	if (rend->keys[GLFW_KEY_ESCAPE])
		glfwSetWindowShouldClose(rend->window, GL_TRUE);
	if (rend->keys[GLFW_KEY_1] && !rend->fkeys[GLFW_KEY_1])
	{
		rend->light_switch[0] *= -1;
		rend->fkeys[GLFW_KEY_1] = 1;
	}
	if (rend->keys[GLFW_KEY_2] && !rend->fkeys[GLFW_KEY_2])
	{
		rend->light_switch[1] *= -1;
		rend->fkeys[GLFW_KEY_2] = 1;
	}
	if (rend->keys[GLFW_KEY_3] && !rend->fkeys[GLFW_KEY_3])
	{
		rend->light_switch[2] *= -1;
		rend->fkeys[GLFW_KEY_3] = 1;
	}
	if (rend->keys[GLFW_KEY_T] && !rend->fkeys[GLFW_KEY_T])
	{
		rend->state = (rend->state + 1) % 3;
		rend->fkeys[GLFW_KEY_T] = 1;
	}
	switch_scene(rend);
}

static void	mod_contrlos(t_render *rend)
{
	if (rend->keys[GLFW_KEY_U])
		rend->x += rend->delta_time * 1.5f;
	if (rend->keys[GLFW_KEY_J])
		rend->x -= rend->delta_time * 1.5f;
	if (rend->keys[GLFW_KEY_I])
		rend->y += rend->delta_time * 1.5f;
	if (rend->keys[GLFW_KEY_K])
		rend->y -= rend->delta_time * 1.5f;
	if (rend->keys[GLFW_KEY_O])
		rend->z += rend->delta_time * 1.5f;
	if (rend->keys[GLFW_KEY_L])
		rend->z -= rend->delta_time * 1.5f;
	if (rend->keys[GLFW_KEY_DOWN])
		rend->ang_x += rend->delta_time * 40.0f;
	if (rend->keys[GLFW_KEY_UP])
		rend->ang_x -= rend->delta_time * 40.0f;
	if (rend->keys[GLFW_KEY_RIGHT])
		rend->ang_y += rend->delta_time * 40.0f;
	if (rend->keys[GLFW_KEY_LEFT])
		rend->ang_y -= rend->delta_time * 40.0f;
	if (rend->keys[GLFW_KEY_COMMA])
		rend->ang_z += rend->delta_time * 40.0f;
	if (rend->keys[GLFW_KEY_PERIOD])
		rend->ang_z -= rend->delta_time * 40.0f;
}

static void	do_movement2(t_render *rend, float delta)
{
	float vec[3];

	if (rend->keys[GLFW_KEY_A])
	{
		cross(vec, rend->cam->front, rend->cam->up);
		normalize(vec);
		rend->cam->pos[0] -= delta * 1.5f * vec[0];
		rend->cam->pos[1] -= delta * 1.5f * vec[1];
		rend->cam->pos[2] -= delta * 1.5f * vec[2];
	}
	if (rend->keys[GLFW_KEY_D])
	{
		cross(vec, rend->cam->front, rend->cam->up);
		normalize(vec);
		rend->cam->pos[0] += delta * 1.5f * vec[0];
		rend->cam->pos[1] += delta * 1.5f * vec[1];
		rend->cam->pos[2] += delta * 1.5f * vec[2];
	}
}

void		do_movement(t_render *rend, float delta)
{
	if (rend->keys[GLFW_KEY_W])
	{
		rend->cam->pos[0] += delta * 1.5f * rend->cam->front[0];
		rend->cam->pos[1] += delta * 1.5f * rend->cam->front[1];
		rend->cam->pos[2] += delta * 1.5f * rend->cam->front[2];
	}
	if (rend->keys[GLFW_KEY_S])
	{
		rend->cam->pos[0] -= delta * 1.5f * rend->cam->front[0];
		rend->cam->pos[1] -= delta * 1.5f * rend->cam->front[1];
		rend->cam->pos[2] -= delta * 1.5f * rend->cam->front[2];
	}
	do_movement2(rend, delta);
	mod_contrlos(rend);
}
