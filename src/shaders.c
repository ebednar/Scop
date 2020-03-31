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

static char* LoadShader(char *filepath)
{
	int fd;
	char *line;
	char *shader;
	char *tmp;

	shader = ft_strnew(0);
	if ((fd = open(filepath, O_RDONLY)) < 0)
		Error(3);
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

static unsigned int CompileShader(unsigned int type, const char* source)
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

unsigned int CreateShader()
{	
	char* vertexShader = LoadShader("res/shaders/VertexShader");
	char* fragmentShader = LoadShader("res/shaders/FragmentShader");
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
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
