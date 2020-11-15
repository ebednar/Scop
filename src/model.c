/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebednar <ebednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 15:14:51 by ebednar           #+#    #+#             */
/*   Updated: 2020/11/05 20:04:11 by ebednar          ###   ########.fr       */
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

static void	read_vert(float **mod_data, float **vt_data, float **vn_data, unsigned int **ind_data,
char *path, t_model *mod)
{
	char	*line;
	int		fd;
	int		vert[4];

	if ((fd = open(path, O_RDONLY)) < 0)
		error(3);
	ft_bzero(vert, 16);
	while (get_next_line(fd, &line))
	{
		if (line[0] == 'v' && line[1] == ' ')
			read_float(mod_data[vert[0]++], line, 0);
		if (line[0] == 'v' && line[1] == 't')
			read_float(vt_data[vert[1]++], line, 0);
		if (line[0] == 'v' && line[1] == 'n')
			read_float(vn_data[vert[2]++], line, 0);
		if (line[0] == 'f')
			read_int(ind_data, &(vert[3]), line);
		free(line);
	}
	if (vert[1] == 0)
		fill_texture(mod_data, mod);
	if (vert[2] == 0)
		fill_normal(mod_data, ind_data, mod->i_count);
	close(fd);
}

static void	init_vert_count(t_model *mod, char *path)
{
	int				fd;
	char			*line;

	if ((fd = open(path, O_RDONLY)) < 0)
		error(3);
	while (get_next_line(fd, &line))
	{
		if (line[0] == 'v' && line[1] == ' ')
			mod->v_count++;
		if (line[0] == 'v' && line[1] == 't')
			mod->vt_count++;
		if (line[0] == 'v' && line[1] == 'n')
			mod->vn_count++;
		if (line[0] == 'f')
			check_indecies(mod, line);
		if (!(ft_strncmp(line, "mtllib", 6)))
			read_material(mod, line);
		free(line);
	}
	close(fd);
}

static void	vert_count(t_model *mod, char *path)
{
	check_file(path);
	mod->is_texture = 1;
	mod->v_count = 0;
	mod->i_count = 0;
	mod->f_count = 0;
	mod->material_name = NULL;
	mod->vt_count = 0;
	mod->vn_count = 0;
	init_vert_count(mod, path);
	if (mod->v_count == 0 || mod->i_count == 0)
		error(6);
}

void		load_model(t_model *mod, char *path)
{
	float			**mod_data;
	float			**vt_data;
	float			**vn_data;
	unsigned int	**ind_data;
	int	i;

	vert_count(mod, path);
	if (!(mod_data = (float **)malloc(mod->v_count * sizeof(float *))))
		error(4);
	if (!(ind_data = (unsigned int **)malloc(mod->i_count
	* sizeof(unsigned int *))))
		error(4);
	i = -1;
	while (++i < (int)mod->v_count)
		if (!(mod_data[i] = (float *)malloc(8 * sizeof(float))))
			error(4);

	if (!(vt_data = (float **)malloc(mod->vt_count * sizeof(float *))))
		error(4);
	if (!(vn_data = (float **)malloc(mod->vn_count * sizeof(float *))))
		error(4);
	i = -1;
	while (++i < (int)mod->vt_count)
		if (!(vt_data[i] = (float *)malloc(2 * sizeof(float))))
			error(4);
	i = -1;
	while (++i < (int)mod->vn_count)
		if (!(vn_data[i] = (float *)malloc(3 * sizeof(float))))
			error(4);
	i = -1;
	while (++i < (int)mod->i_count)
		if (!(ind_data[i] = (unsigned int *)malloc(9 * sizeof(unsigned int))))
			error(4);
	read_vert(mod_data, vt_data, vn_data, ind_data, path, mod);
	if (!(mod->verticies = (float *)malloc((8 * mod->v_count) * sizeof(float))))
		error(4);
	if (!(mod->indicies = (unsigned int *)malloc((3 * mod->i_count)
	* sizeof(unsigned int))))
		error(4);
	fill_verticies(mod, mod_data, vt_data, vn_data, ind_data);
}
