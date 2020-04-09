#include "scop.h"

void	initGLFW()
{
	/* Initialize the library */
    if (!glfwInit())
        error(1);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void	makeContext(GLFWwindow* window)
{
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glEnable(GL_DEPTH_TEST);
	ft_putendl((char *)glGetString(GL_VERSION));
}

void	initBaseData(GLFWwindow* window, render* rend, matrices* mat, model* mod)
{
		glfwSetWindowUserPointer(window, rend);
	ft_bzero(rend->keys, 1024);
	int i = -1;
	while (++i < 3)
		rend->switchLight[i] = 1.0;
	rend->texture = loadImage("res/textures/cat.bmp");
	rend->shader.modShader = createShader("res/shaders/VertexShader", "res/shaders/FragmentShader");
	rend->shader.lightShader = createShader("res/shaders/VertexShader", "res/shaders/LightFragShader");
	glUseProgram(rend->shader.modShader);
	lightUniform(rend->shader.modShader, mod);
	camera_init(rend->cam);
	initMat(mat);
	perspMatrix(mat);
}