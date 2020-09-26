/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shaders.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebednar <ebednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/15 21:39:06 by ebednar           #+#    #+#             */
/*   Updated: 2020/08/23 15:15:10 by ebednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static char* load_shader(char *filepath)
{
	int		fd;
	char	*line;
	char	*shader;
	char 	*tmp;

	shader = ft_strnew(0);
	if ((fd = open(filepath, O_RDONLY)) < 0)
		error(3);
	while(get_next_line(fd, &line))
	{
		if (!(tmp = ft_strjoin(shader, line)))
			return (NULL);
		free(shader);
		free(line);
		shader = tmp;
		if (!(tmp = ft_strjoin(shader, "\n")))
			return (NULL);
		free(shader);
		shader = tmp;
	}
	close(fd);
	return (shader);
}

static unsigned int compile_shader(unsigned int type, const char *source)
{
	int			result;
	unsigned	id;

	id = glCreateShader(type);
	glShaderSource(id, 1, &source, NULL);
	glCompileShader(id);
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)malloc(sizeof(char) * length + 1);
		glGetShaderInfoLog(id, length, &length, message);
		type == GL_VERTEX_SHADER ? ft_putstr("vertex ") : ft_putstr("fragment ");
		ft_putstr("shader compilation failed\n");
		ft_putstr(message);
		free(message);
		glDeleteShader(id);
		return 0;
	}
	return id;
}

unsigned int create_shader(char *vertShader, char *fragShader)
{	
	char			*vertexShader;
	char			*fragmentShader;
	unsigned int	program;
	unsigned int	vs;
	unsigned int	fs;
	int				result;

	vertexShader = load_shader(vertShader);
	fragmentShader = load_shader(fragShader);
	program = glCreateProgram();
	vs = compile_shader(GL_VERTEX_SHADER, vertexShader);
	fs = compile_shader(GL_FRAGMENT_SHADER, fragmentShader);
	free(vertexShader);
	free(fragmentShader);
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &result);
	if (!result)
	{
		int length;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
		char* message;
		if (!(message = (char*)malloc(sizeof(char) * length + 1)))
			error(4);
		glGetProgramInfoLog(program, length, &length, message);
		ft_putendl("link error");
		ft_putendl(message);
		free(message);
	}
	glValidateProgram(program);
	glDeleteShader(vs);
	glDeleteShader(fs);
	return program;
}

void	light_uniform(unsigned int shader, model *mod)
{
	glUniform1i(glGetUniformLocation(shader, "u_Texture"), 0);
	glUniform1i(glGetUniformLocation(shader, "u_isText"), mod->isTexture);
	glUniform1i(glGetUniformLocation(shader, "material.diffuse"), 0);
	glUniform3f(glGetUniformLocation(shader, "material.specular"), mod->specular[0], mod->specular[1], mod->specular[2]);
	glUniform1f(glGetUniformLocation(shader, "material.shininess"), mod->shininess);
	glUniform3f(glGetUniformLocation(shader, "dirLight.direction"), -0.2f, -1.0f, -0.3f);
	glUniform3f(glGetUniformLocation(shader, "dirLight.ambient"), 0.05f, 0.05f, 0.05f);
	glUniform3f(glGetUniformLocation(shader, "dirLight.diffuse"), 0.15f, 0.15f, 0.15f);
	glUniform3f(glGetUniformLocation(shader, "dirLight.specular"), 0.3f, 0.3f, 0.3f);
	glUniform1f(glGetUniformLocation(shader, "pointLight.constant"), 1.0f);
	glUniform1f(glGetUniformLocation(shader, "pointLight.linear"), 0.09f);
	glUniform1f(glGetUniformLocation(shader, "pointLight.quadratic"), 0.032f);
	glUniform3f(glGetUniformLocation(shader, "pointLight.ambient"), 0.1f, 0.1f, 0.1f);
	glUniform3f(glGetUniformLocation(shader, "pointLight.diffuse"), 0.8f, 0.8f, 0.8f);
	glUniform3f(glGetUniformLocation(shader, "pointLight.specular"), 1.0f, 1.0f, 1.0f);
	glUniform3f(glGetUniformLocation(shader, "pointLight.position"), 2.5f, 1.0f, 1.5f);
	glUniform1f(glGetUniformLocation(shader, "spotLight.cutoff"), cos(6.5f * M_PI / 180));
	glUniform1f(glGetUniformLocation(shader, "spotLight.outerCutoff"), cos(12.5f * M_PI / 180));
	glUniform3f(glGetUniformLocation(shader, "spotLight.ambient"), 0.1f, 0.1f, 0.1f);
	glUniform3f(glGetUniformLocation(shader, "spotLight.diffuse"), 0.8f, 0.8f, 0.8f);
	glUniform3f(glGetUniformLocation(shader, "spotLight.specular"), 0.9f, 0.9f, 0.9f);
	glUniform1f(glGetUniformLocation(shader, "spotLight.constant"), 1.0f);
	glUniform1f(glGetUniformLocation(shader, "spotLight.linear"), 0.09f);
	glUniform1f(glGetUniformLocation(shader, "spotLight.quadratic"), 0.032f);
}
