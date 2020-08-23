/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebednar <ebednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/15 23:02:39 by ebednar           #+#    #+#             */
/*   Updated: 2020/08/23 15:15:10 by ebednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void	switchScene(render* rend, int key, int action)
{
		if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
	{
		rend->wire *= -1;
		if (rend->wire == -1)
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	if (key == GLFW_KEY_TAB && action == GLFW_PRESS)
	{
		rend->scene *= -1;
		if (rend->scene == -1) 
			startPos(rend);
	}
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	render* rend = glfwGetWindowUserPointer(window);
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    	glfwSetWindowShouldClose(window, GL_TRUE);
	if(key == GLFW_KEY_1 && action == GLFW_PRESS)
		rend->lightSwitch[0] *= -1;
	if(key == GLFW_KEY_2 && action == GLFW_PRESS)
		rend->lightSwitch[1] *= -1;
	if(key == GLFW_KEY_3 && action == GLFW_PRESS)
		rend->lightSwitch[2] *= -1;
	if (key == GLFW_KEY_T && action == GLFW_PRESS)
	{
		rend->state += 1;
		rend->state %= 3;
	}
	switchScene(rend, key, action);
	if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
            rend->keys[key] = 1;
        else if (action == GLFW_RELEASE)
            rend->keys[key] = 0;
    }
	scancode = 0;
	mode = 0;
}

static void	modContrlos(render* rend)
{
	if (rend->keys[GLFW_KEY_U])
		rend->x += rend->deltaTime * 1.5f;
	if (rend->keys[GLFW_KEY_J])
		rend->x -= rend->deltaTime * 1.5f;
	if (rend->keys[GLFW_KEY_I])
		rend->y += rend->deltaTime * 1.5f;
	if (rend->keys[GLFW_KEY_K])
		rend->y -= rend->deltaTime * 1.5f;
	if (rend->keys[GLFW_KEY_O])
		rend->z += rend->deltaTime * 1.5f;
	if (rend->keys[GLFW_KEY_L])
		rend->z -= rend->deltaTime * 1.5f;
	if (rend->keys[GLFW_KEY_DOWN])
		rend->angX += rend->deltaTime * 40.0f;
	if (rend->keys[GLFW_KEY_UP])
		rend->angX -= rend->deltaTime * 40.0f;
	if (rend->keys[GLFW_KEY_RIGHT])
		rend->angY += rend->deltaTime * 40.0f;
	if (rend->keys[GLFW_KEY_LEFT])
		rend->angY -= rend->deltaTime * 40.0f;
	if (rend->keys[GLFW_KEY_COMMA])
		rend->angZ += rend->deltaTime * 40.0f;
	if (rend->keys[GLFW_KEY_PERIOD])
		rend->angZ -= rend->deltaTime * 40.0f;
}

static void do_movement2(render* rend, float delta)
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

void do_movement(render* rend, float delta)
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
	modContrlos(rend);
}
