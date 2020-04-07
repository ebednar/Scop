/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebednar <ebednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/15 23:02:39 by ebednar           #+#    #+#             */
/*   Updated: 2020/03/15 23:05:56 by ebednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	render* rend = glfwGetWindowUserPointer(window);
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    	glfwSetWindowShouldClose(window, GL_TRUE);
	if(key == GLFW_KEY_1 && action == GLFW_PRESS)
		rend->switchLight[0] *= -1;
	if(key == GLFW_KEY_2 && action == GLFW_PRESS)
		rend->switchLight[1] *= -1;
	if(key == GLFW_KEY_3 && action == GLFW_PRESS)
		rend->switchLight[2] *= -1;
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

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	render* rend = glfwGetWindowUserPointer(window);
	GLfloat xoffset = xpos - rend->cam->lastX;
    GLfloat yoffset = rend->cam->lastY - ypos; 
    rend->cam->lastX = xpos;
    rend->cam->lastY = ypos;

    GLfloat sensitivity = 0.05;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    rend->cam->yaw   += xoffset;
    rend->cam->pitch += yoffset;

    if(rend->cam->pitch > 89.0f)
        rend->cam->pitch = 89.0f;
    if(rend->cam->pitch < -89.0f)
        rend->cam->pitch = -89.0f;

    rend->cam->front[0] = cos(rend->cam->yaw * M_PI / 180) * cos(rend->cam->pitch * M_PI / 180);
    rend->cam->front[1] = sin(rend->cam->pitch * M_PI / 180);
    rend->cam->front[2] = sin(rend->cam->yaw * M_PI / 180) * cos(rend->cam->pitch * M_PI / 180);
    normalize(rend->cam->front);
}

void do_movement(render* rend, float delta)
{
    float cameraSpeed = 1.5f * delta;
	float vec[3];
    if (rend->keys[GLFW_KEY_W])
	{
        rend->cam->pos[0] += cameraSpeed * rend->cam->front[0];
		rend->cam->pos[1] += cameraSpeed * rend->cam->front[1];
		rend->cam->pos[2] += cameraSpeed * rend->cam->front[2];
	}
    if (rend->keys[GLFW_KEY_S])
	{
        rend->cam->pos[0] -= cameraSpeed * rend->cam->front[0];
		rend->cam->pos[1] -= cameraSpeed * rend->cam->front[1];
		rend->cam->pos[2] -= cameraSpeed * rend->cam->front[2];
	}    
	if (rend->keys[GLFW_KEY_A])
	{
		cross(vec, rend->cam->front, rend->cam->up);
		normalize(vec);
		rend->cam->pos[0] -= cameraSpeed * vec[0];
		rend->cam->pos[1] -= cameraSpeed * vec[1];
		rend->cam->pos[2] -= cameraSpeed * vec[2];
	}
    if (rend->keys[GLFW_KEY_D])
	{
        cross(vec, rend->cam->front, rend->cam->up);
		normalize(vec);
		rend->cam->pos[0] += cameraSpeed * vec[0];
		rend->cam->pos[1] += cameraSpeed * vec[1];
		rend->cam->pos[2] += cameraSpeed * vec[2];
	}
}
