/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadShaders.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebednar <ebednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/15 21:39:06 by ebednar           #+#    #+#             */
/*   Updated: 2020/03/15 22:29:15 by ebednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static char* LoadShader()
{
	int fd;
	char *line;

	if ((fd = open("res/shaders/VertexShader", O_RDONLY)) < 0)
		Error(3);
	get_next_line(fd, &line);
	return (line);
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
		glDeleteShader(id);
		return 0;
	}
	return id;
}

unsigned int CreateShader()
{	char *line = LoadShader();
	ft_putendl(line);
	char* vertexShader = 
	"#version 330 core\n  \
	\n \
	layout(location = 0) in vec4 position;\n \
	\n \
	void main()\n\
	{\n\
		gl_Position = position;\n\
	}";
	char* fragmentShader = 
	"#version 330 core\n\
	\n \
	out vec4 color;\n\
	\n \
	void main()\n\
	{\n\
		color = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n\
	}";
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

