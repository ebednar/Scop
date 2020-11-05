/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebednar <ebednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/15 23:02:39 by ebednar           #+#    #+#             */
/*   Updated: 2020/11/05 19:58:49 by ebednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void	switch_light(t_render *rend)
{
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
}

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
	switch_light(rend);
	if (rend->keys[GLFW_KEY_T] && !rend->fkeys[GLFW_KEY_T])
	{
		rend->state = (rend->state + 1) % 3;
		rend->fkeys[GLFW_KEY_T] = 1;
	}
	switch_scene(rend);
}
