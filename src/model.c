/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebednar <ebednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 15:14:51 by ebednar           #+#    #+#             */
/*   Updated: 2020/11/19 18:46:25 by ebednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void	read_vert(float **mod_data, unsigned int **ind_data,
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
			read_float(mod->vt_data[vert[1]++], line, 0);
		if (line[0] == 'v' && line[1] == 'n')
			read_float(mod->vn_data[vert[2]++], line, 0);
		if (line[0] == 'f')
			read_int(ind_data, &(vert[3]), line);
		free(line);
	}
	if (vert[1] == 0)
		fill_texture(mod_data, mod);
	if (vert[2] == 0 || !mod->is_normal)
		fill_normal(mod_data, ind_data, mod->i_count, mod);
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
	mod->is_normal = 1;
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

static void	alloc_vert(t_model *mod, float **mod_data, unsigned int **ind_data)
{
	int	i;

	i = -1;
	while (++i < (int)mod->v_count)
		if (!(mod_data[i] = (float *)malloc(8 * sizeof(float))))
			error(4);
	i = -1;
	while (++i < (int)mod->i_count)
		if (!(ind_data[i] = (unsigned int *)malloc(9 * sizeof(unsigned int))))
			error(4);
	i = -1;
	while (++i < (int)mod->vt_count)
		if (!(mod->vt_data[i] = (float *)malloc(2 * sizeof(float))))
			error(4);
	i = -1;
	while (++i < (int)mod->vn_count)
		if (!(mod->vn_data[i] = (float *)malloc(3 * sizeof(float))))
			error(4);
}

void		load_model(t_model *mod, char *path)
{
	float			**mod_data;
	unsigned int	**ind_data;

	vert_count(mod, path);
	if (!(mod_data = (float **)malloc(mod->v_count * sizeof(float *))))
		error(4);
	if (!(ind_data = (unsigned int **)malloc(mod->i_count
	* sizeof(unsigned int *))))
		error(4);
	if (!(mod->vt_data = (float **)malloc(mod->vt_count * sizeof(float *))))
		error(4);
	if (!(mod->vn_data = (float **)malloc(mod->vn_count * sizeof(float *))))
		error(4);
	alloc_vert(mod, mod_data, ind_data);
	read_vert(mod_data, ind_data, path, mod);
	if (!(mod->verticies = (float *)malloc((8 * mod->v_count) * sizeof(float))))
		error(4);
	if (!(mod->indicies = (unsigned int *)malloc((3 * mod->i_count)
	* sizeof(unsigned int))))
		error(4);
	fill_verticies(mod, mod_data, ind_data);
}
