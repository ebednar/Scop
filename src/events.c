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
	camera* cam = glfwGetWindowUserPointer(window);
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    	glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
            cam->keys[key] = 1;
        else if (action == GLFW_RELEASE)
            cam->keys[key] = 0;
    }
	scancode = 0;
	mode = 0;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	camera* cam = glfwGetWindowUserPointer(window);
	GLfloat xoffset = xpos - cam->lastX;
    GLfloat yoffset = cam->lastY - ypos; 
    cam->lastX = xpos;
    cam->lastY = ypos;

    GLfloat sensitivity = 0.05;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    cam->yaw   += xoffset;
    cam->pitch += yoffset;

    if(cam->pitch > 89.0f)
        cam->pitch = 89.0f;
    if(cam->pitch < -89.0f)
        cam->pitch = -89.0f;

    cam->front[0] = cos(cam->yaw * M_PI / 180) * cos(cam->pitch * M_PI / 180);
    cam->front[1] = sin(cam->pitch * M_PI / 180);
    cam->front[2] = sin(cam->yaw * M_PI / 180) * cos(cam->pitch * M_PI / 180);
    Normalize(cam->front);
}

void Do_movement(camera* cam, char* keys, float delta)
{
    // Camera controls
    float cameraSpeed = 1.5f * delta;
	float vec[3];
    if (keys[GLFW_KEY_W])
	{
        cam->pos[0] += cameraSpeed * cam->front[0];
		cam->pos[1] += cameraSpeed * cam->front[1];
		cam->pos[2] += cameraSpeed * cam->front[2];
	}
    if (keys[GLFW_KEY_S])
	{
        cam->pos[0] -= cameraSpeed * cam->front[0];
		cam->pos[1] -= cameraSpeed * cam->front[1];
		cam->pos[2] -= cameraSpeed * cam->front[2];
	}    
	if (keys[GLFW_KEY_A])
	{
		Cross(vec, cam->front, cam->up);
		Normalize(vec);
		cam->pos[0] -= cameraSpeed * vec[0];
		cam->pos[1] -= cameraSpeed * vec[1];
		cam->pos[2] -= cameraSpeed * vec[2];
	}
    if (keys[GLFW_KEY_D])
	{
        Cross(vec, cam->front, cam->up);
		Normalize(vec);
		cam->pos[0] += cameraSpeed * vec[0];
		cam->pos[1] += cameraSpeed * vec[1];
		cam->pos[2] += cameraSpeed * vec[2];
	}
}
