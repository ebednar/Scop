/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shaders.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebednar <ebednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/15 21:39:06 by ebednar           #+#    #+#             */
/*   Updated: 2020/10/23 22:02:34 by ebednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static char			*load_shader(char *filepath)
{
	int		fd;
	char	*line;
	char	*shader;
	char	*tmp;

	shader = ft_strnew(0);
	if ((fd = open(filepath, O_RDONLY)) < 0)
		error(3);
	while (get_next_line(fd, &line))
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

static unsigned int	compile_shader(unsigned int type, const char *source)
{
	int			result;
	unsigned	id;
	int			length;
	char		*message;

	id = glCreateShader(type);
	glShaderSource(id, 1, &source, NULL);
	glCompileShader(id);
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		message = (char *)malloc(sizeof(char) * length + 1);
		glGetShaderInfoLog(id, length, &length, message);
		type == GL_VERTEX_SHADER ? ft_putstr("vertex ")
		: ft_putstr("fragment ");
		ft_putstr("shader compilation failed\n");
		ft_putstr(message);
		free(message);
		glDeleteShader(id);
		return (0);
	}
	return (id);
}

static void			error_shader(unsigned int program, int result)
{
	int		length;
	char	*message;

	if (!result)
	{
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
		if (!(message = (char *)malloc(sizeof(char) * length + 1)))
			error(4);
		glGetProgramInfoLog(program, length, &length, message);
		ft_putendl("link error");
		ft_putendl(message);
		free(message);
	}
}

unsigned int		create_shader(char *vert_shader, char *frag_shader)
{
	char			*vertex_shader;
	char			*fragment_shader;
	unsigned int	program;
	unsigned int	s[2];
	int				result;

	vertex_shader = load_shader(vert_shader);
	fragment_shader = load_shader(frag_shader);
	program = glCreateProgram();
	s[0] = compile_shader(GL_VERTEX_SHADER, vertex_shader);
	s[1] = compile_shader(GL_FRAGMENT_SHADER, fragment_shader);
	free(vertex_shader);
	free(fragment_shader);
	glAttachShader(program, s[0]);
	glAttachShader(program, s[1]);
	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &result);
	error_shader(program, result);
	glValidateProgram(program);
	glDeleteShader(s[0]);
	glDeleteShader(s[1]);
	return (program);
}
