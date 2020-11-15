/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_verticies.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebednar <ebednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 15:14:35 by ebednar           #+#    #+#             */
/*   Updated: 2020/10/23 22:14:07 by ebednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void	free_data(t_model *mod, float **mod_data, unsigned int **ind_data)
{
	int i;

	i = -1;
	while (++i < (int)mod->v_count)
		free(mod_data[i]);
	i = -1;
	while (++i < (int)mod->i_count)
		free(ind_data[i]);
	free(mod_data);
	free(ind_data);
}

static void offset_mod(t_model *mod, float x, float z)
{
	int i;
	int	j;

	i = 0;
	j = -1;
	while (++j < (int)mod->v_count)
	{
		mod->verticies[i] -= x;
		i += 2;
		mod->verticies[i] -= z;
		i += 6;
	}
}

static void recenter(t_model *mod)
{
	int		i;
	int		j;
	float	min[2];
	float	max[2];

	min[0] = 1.0f;
	min[1] = 1.0f;
	max[0] = -1.0f;
	max[1] = -1.0f;
	i = 0;
	j = -1;
	while (++j < (int)mod->v_count)
	{
		if (mod->verticies[i] < min[0])
			min[0] = mod->verticies[i];
		if (mod->verticies[i] > max[0])
			max[0] = mod->verticies[i];
		i += 2;
		if (mod->verticies[i] < min[1])
			min[1] = mod->verticies[i];
		if (mod->verticies[i] > max[1])
			max[1] = mod->verticies[i];
		i += 6;
	}
	offset_mod(mod, (max[0] + min[0]) / 2, (max[1] + min[1]) / 2);
}

void		fill_verticies(t_model *mod, float **mod_data,
unsigned int **ind_data)
{
	int i;
	int j;
	int k;

	i = -1;
	k = -1;
	while (++i < (int)mod->v_count)
	{
		j = -1;
		while (++j < 8)
			mod->verticies[++k] = mod_data[i][j];
	}
	i = -1;
	k = -1;
	while (++i < (int)mod->i_count)
	{
		j = -1;
		while (++j < 3)
		{
			if (ind_data[i][j] > mod->v_count)
				error(6);
			mod->indicies[++k] = ind_data[i][j];
		}
	}
	free_data(mod, mod_data, ind_data);
	recenter(mod);
}
