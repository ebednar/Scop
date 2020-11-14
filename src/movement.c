/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebednar <ebednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 19:56:36 by ebednar           #+#    #+#             */
/*   Updated: 2020/11/14 20:30:32 by ebednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

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
	rend->ang_y += rend->delta_time * 40.0f;
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
