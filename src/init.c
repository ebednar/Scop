/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebednar <ebednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 15:14:38 by ebednar           #+#    #+#             */
/*   Updated: 2020/08/23 15:41:52 by ebednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void		init_glfw(void)
{
	if (!glfwInit())
		error(1);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void		make_context(render *rend)
{
	int	width;
	int	height;

	if (!(rend->window = glfwCreateWindow(WIDTH, HEIGHT, "Scop", NULL, NULL)))
		error(2);
	glfwMakeContextCurrent(rend->window);
	glfwSwapInterval(1);
	glfwGetFramebufferSize(rend->window, &width, &height);
	glViewport(0, 0, width, height);
	glfwSetInputMode(rend->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetWindowUserPointer(rend->window, rend);
	glfwSetKeyCallback(rend->window, key_callback);
	glfwSetCursorPosCallback(rend->window, mouse_callback);
	if (!(rend->cam = (camera *)malloc(sizeof(camera))))
		error(4);
	glfwSetCursorPos(rend->window, rend->cam->lastX, rend->cam->lastY);
	glEnable(GL_DEPTH_TEST);
	ft_putendl((char *)glGetString(GL_VERSION));
}

void		start_pos(render *rend)
{
	rend->x = 0.0f;
	rend->y = 0.0f;
	rend->z = 0.0f;
	rend->angX = 0.0f;
	rend->angY = 0.0f;
	rend->angZ = 0.0f;
}

static void	init_material(model *mod)
{
	int i;

	if (mod->materialName == NULL)
	{
		i = -1;
		while (++i < 3)
			mod->specular[i] = 0.5f;
		mod->shininess = 32.0f;
	}
	if (mod->shininess < 32)
		mod->shininess = 32.0f;
}

void		init_base_data(render *rend, matrices *mat, model *mod)
{
	int i;

	rend->oldFrame = 0.0f;
	start_pos(rend);
	rend->state = 0;
	rend->wire = -1;
	rend->scene = -1;
	ft_bzero(rend->keys, 1024);
	i = -1;
	while (++i < 3)
		rend->lightSwitch[i] = -1.0f;
	init_material(mod);
	rend->texture = load_image("res/textures/cat.bmp");
	rend->shader.modShader =
	create_shader("res/shaders/VertexShader", "res/shaders/FragmentShader");
	rend->shader.lightShader =
	create_shader("res/shaders/VertexShader", "res/shaders/LightFragShader");
	glUseProgram(rend->shader.modShader);
	light_uniform(rend->shader.modShader, mod);
	camera_init(rend->cam);
	init_mat(mat);
	persp_matrix(mat);
	set_buffers(rend, mod);
}
