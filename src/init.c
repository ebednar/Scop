#include "scop.h"

void	initGLFW()
{
	/* Initialize the library */
    if (!glfwInit())
        Error(1);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void	MakeContext(GLFWwindow* window)
{
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
}