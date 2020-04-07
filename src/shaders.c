/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadShaders.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebednar <ebednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/15 21:39:06 by ebednar           #+#    #+#             */
/*   Updated: 2020/03/15 22:57:04 by ebednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static char* loadShader(char *filepath)
{
	int fd;
	char *line;
	char *shader;
	char *tmp;

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

static unsigned int compileShader(unsigned int type, const char* source)
{
	unsigned id = glCreateShader(type);
	glShaderSource(id, 1, &source, NULL);
	glCompileShader(id);

	int result;
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

unsigned int createShader(char* vertShader, char* fragShader)
{	
	char* vertexShader = loadShader(vertShader);
	char* fragmentShader = loadShader(fragShader);
	unsigned int program = glCreateProgram();
	unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);
	free(vertexShader);
	free(fragmentShader);
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	int result;
	glGetProgramiv(program, GL_LINK_STATUS, &result);
	if (!result)
	{
		int length;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)malloc(sizeof(char) * length + 1);
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

void	lightUniform(unsigned int shader)
{
	glUniform1i(glGetUniformLocation(shader, "u_Texture"), 0);
	glUniform1i(glGetUniformLocation(shader, "material.diffuse"), 0);
	glUniform3f(glGetUniformLocation(shader, "material.specular"), 0.5f, 0.5f, 0.5f);
	glUniform1f(glGetUniformLocation(shader, "material.shininess"), 32.0f);
	glUniform3f(glGetUniformLocation(shader, "dirLight.direction"), -0.2f, -1.0f, -0.3f);
	glUniform3f(glGetUniformLocation(shader, "dirLight.ambient"), 0.01f, 0.01f, 0.01f);
	glUniform3f(glGetUniformLocation(shader, "dirLight.diffuse"), 0.2f, 0.2f, 0.2f);
	glUniform3f(glGetUniformLocation(shader, "dirLight.specular"), 0.7f, 0.7f, 0.7f);
	glUniform1f(glGetUniformLocation(shader, "pointLight.constant"), 1.0f);
	glUniform1f(glGetUniformLocation(shader, "pointLight.linear"), 0.09f);
	glUniform1f(glGetUniformLocation(shader, "pointLight.quadratic"), 0.032f);
	glUniform3f(glGetUniformLocation(shader, "pointLight.ambient"), 0.1f, 0.1f, 0.1f);
	glUniform3f(glGetUniformLocation(shader, "pointLight.diffuse"), 0.7f, 0.7f, 0.7f);
	glUniform3f(glGetUniformLocation(shader, "pointLight.specular"), 1.0f, 1.0f, 1.0f);
	glUniform3f(glGetUniformLocation(shader, "pointLight.position"), 5.5f, 1.0f, 1.5f);
	glUniform1f(glGetUniformLocation(shader, "spotLight.cutoff"), cos(6.5f * M_PI / 180));
	glUniform1f(glGetUniformLocation(shader, "spotLight.outerCutoff"), cos(12.5f * M_PI / 180));
	glUniform3f(glGetUniformLocation(shader, "spotLight.ambient"), 0.1f, 0.1f, 0.1f);
	glUniform3f(glGetUniformLocation(shader, "spotLight.diffuse"), 0.7f, 0.7f, 0.7f);
	glUniform3f(glGetUniformLocation(shader, "spotLight.specular"), 1.0f, 1.0f, 1.0f);
	glUniform1f(glGetUniformLocation(shader, "spotLight.constant"), 1.0f);
	glUniform1f(glGetUniformLocation(shader, "spotLight.linear"), 0.09f);
	glUniform1f(glGetUniformLocation(shader, "spotLight.quadratic"), 0.032f);
}