#include "scop.h"

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	render* rend;
	float xoffset;
    float yoffset;

	rend = glfwGetWindowUserPointer(window);
	xoffset = xpos - rend->cam->lastX;
	yoffset = rend->cam->lastY - ypos;
    rend->cam->lastX = xpos;
    rend->cam->lastY = ypos;
    xoffset *= 0.05;
    yoffset *= 0.05;
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