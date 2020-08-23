/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebednar <ebednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 15:14:51 by ebednar           #+#    #+#             */
/*   Updated: 2020/08/23 15:35:08 by ebednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void	read_float(float *data, char *line, int offset)
{
	char	*ptr1;
	char	*ptr2;
	int		i;

	i = -1;
	while (line[++i] != '\0')
	{
		if ((line[i] < '0' || line[i] > '9') && line[i] != '.'
		&& line[i] != '-' && line[i] != '+')
			line[i] = ' ';
	}
	i = -1;
	ptr1 = line + 2;
	while (++i < (offset == 3 ? 2 : 3))
	{
		data[i + offset] = strtof(ptr1, &ptr2);
		ptr1 = ptr2;
	}
}

static void	read_vert(float **mod_data, unsigned int **ind_data,
char *path, model *mod)
{
	char	*line;
	int		fd;
	int		vert[4];
	int		i;

	if ((fd = open(path, O_RDONLY)) < 0)
		error(3);
	i = -1;
	while (++i < 4)
		vert[i] = 0;
	while (get_next_line(fd, &line))
	{
		if (line[0] == 'v' && line[1] == ' ')
			readFloat(mod_data[vert[0]++], line, 0);
		if (line[0] == 'v' && line[1] == 't')
			readFloat(mod_data[vert[1]++], line, 3);
		if (line[0] == 'v' && line[1] == 'n')
			readFloat(mod_data[vert[2]++], line, 5);
		if (line[0] == 'f')
			readInt(ind_data, &(vert[3]), line);
		free(line);
	}
	if (vert[1] == 0)
		fillTexture(mod_data, mod);
	if (vert[2] == 0)
		fillNormal(mod_data, ind_data, mod->iCount);
	close(fd);
}

static void	vert_count(model *mod, char *path)
{
	int				fd;
	char			*line;
	unsigned int	vt_count;
	unsigned int	vn_count;

	checkFile(path);
	mod->isTexture = 1;
	mod->vCount = 0;
	mod->iCount = 0;
	vt_count = 0;
	vn_count = 0;
	mod->materialName = NULL;
	if ((fd = open(path, O_RDONLY)) < 0)
		error(3);
	while(get_next_line(fd, &line))
	{
		if (line[0] == 'v' && line[1] == ' ')
			mod->vCount++;
		if (line[0] == 'v' && line[1] == 't')
			vt_count++;
		if (line[0] == 'v' && line[1] == 'n')
			vn_count++;
		if (line[0] == 'f')
			checkIndecies(mod, line);
		if (!(ft_strncmp(line, "mtllib", 6)))
			readMaterial(mod, line);
		free(line);
	}
	close(fd);
	if (mod->vCount == 0 || mod->iCount == 0 || vn_count > mod->vCount || vt_count > mod->vCount)
		error(6);
}

void		load_model(model *mod, char *path)
{
	float			**mod_data;
	unsigned int	**ind_data;
	unsigned int	i;

	vert_count(mod, path);
	if (!(mod_data = (float **)malloc(mod->vCount * sizeof(float *))))
		error(4);
	if (!(ind_data = (unsigned int **)malloc(mod->iCount * sizeof(unsigned int *))))
		error(4);
	i = -1;
	while (++i < mod->vCount)
		if (!(mod_data[i] = (float *)malloc(8 * sizeof(float))))
			error(4);
	i = -1;
	while (++i < mod->iCount)
		if (!(ind_data[i] = (unsigned int *)malloc(3 * sizeof(unsigned int))))
			error(4);
	readVert(mod_data, ind_data, path, mod);
	if (!(mod->verticies = (float *)malloc((8 * mod->vCount) * sizeof(float))))
			error(4);
	if (!(mod->indicies = (unsigned int *)malloc((3 * mod->iCount) * sizeof(unsigned int))))
			error(4);
	fillVerticies(mod, mod_data, ind_data);
}
