/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebednar <ebednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 15:14:44 by ebednar           #+#    #+#             */
/*   Updated: 2020/11/16 20:07:57 by ebednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void	read_specular(t_model *mod, char *line)
{
	char	*ptr1;
	char	*ptr2;
	int		i;

	i = -1;
	while (line[++i] != '\0')
	{
		if ((line[i] < '0' || line[i] > '9') && line[i] != '.')
			line[i] = ' ';
	}
	i = -1;
	ptr1 = line + 2;
	while (++i < 3)
	{
		mod->specular[i] = strtof(ptr1, &ptr2);
		ptr1 = ptr2;
	}
}

void		load_material(t_model *mod)
{
	int		fd;
	char	*str;
	char	*line;

	str = ft_strjoin("res/models/", mod->material_name);
	free(mod->material_name);
	if ((fd = open(str, O_RDONLY)) < 0)
	{
		close(fd);
		free(str);
		return ;
	}
	free(str);
	while (get_next_line(fd, &line))
	{
		if (line[0] == 'N' && line[1] == 's')
			mod->shininess = ft_atoi(line + 2);
		if (line[0] == 'K' && line[1] == 's')
			read_specular(mod, line);
		free(line);
	}
	close(fd);
}

void		read_material(t_model *mod, char *str)
{
	int count;

	str = str + 7;
	count = ft_strlen(str);
	if (!(mod->material_name = (char *)malloc(count * sizeof(char) + 1)))
		error(4);
	ft_strcpy(mod->material_name, str);
	ft_putstr("material: ");
	ft_putendl(mod->material_name);
	load_material(mod);
}
