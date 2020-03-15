/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadShaders.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebednar <ebednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/15 21:39:06 by ebednar           #+#    #+#             */
/*   Updated: 2020/03/15 22:11:06 by ebednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

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
		glDeleteShader(id);
		return 0;
	}
	return id;
}

unsigned int CreateShader(const char* vertexShader, const char* fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
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
	}
	glValidateProgram(program);
	glDeleteShader(vs);
	glDeleteShader(fs);
	return program;
}

