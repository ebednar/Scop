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

void		fill_texture(float **mod_data, t_model *mod)
{
	int i;

	mod->is_texture = 0;
	i = 0;
	while (i < (int)mod->v_count)
	{
		if (i % 3 == 0)
		{
			mod_data[i][3] = 0.9f;
			mod_data[i][4] = 0.1f;
		}
		else if (i % 3 == 1)
		{
			mod_data[i][3] = 0.1f;
			mod_data[i][4] = 0.9f;
		}
		else if (i % 3 == 2)
		{
			mod_data[i][3] = 0.02f;
			mod_data[i][4] = 0.02f;
		}
		i++;
	}
}

void		fill_normal(float **mod_data, unsigned int **ind_data, int i_count)
{
	int		i;
	float	vec1[3];
	float	vec2[3];
	float	norm[3];

	i = -1;
	while (++i < i_count)
	{
		vec1[0] = mod_data[ind_data[i][1]][0] - mod_data[ind_data[i][0]][0];
		vec1[1] = mod_data[ind_data[i][1]][1] - mod_data[ind_data[i][0]][1];
		vec1[2] = mod_data[ind_data[i][1]][2] - mod_data[ind_data[i][0]][2];
		vec2[0] = mod_data[ind_data[i][2]][0] - mod_data[ind_data[i][0]][0];
		vec2[1] = mod_data[ind_data[i][2]][1] - mod_data[ind_data[i][0]][1];
		vec2[2] = mod_data[ind_data[i][2]][2] - mod_data[ind_data[i][0]][2];
		cross(norm, vec1, vec2);
		mod_data[ind_data[i][0]][5] = norm[0];
		mod_data[ind_data[i][1]][5] = norm[0];
		mod_data[ind_data[i][2]][5] = norm[0];
		mod_data[ind_data[i][0]][6] = norm[1];
		mod_data[ind_data[i][1]][6] = norm[1];
		mod_data[ind_data[i][2]][6] = norm[1];
		mod_data[ind_data[i][0]][7] = norm[2];
		mod_data[ind_data[i][1]][7] = norm[2];
		mod_data[ind_data[i][2]][7] = norm[2];
	}
}

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
}
