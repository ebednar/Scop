/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_verticies.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebednar <ebednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 15:14:35 by ebednar           #+#    #+#             */
/*   Updated: 2020/11/19 19:00:34 by ebednar          ###   ########.fr       */
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
	i = -1;
	while (++i < (int)mod->vt_count)
		free(mod->vt_data[i]);
	i = -1;
	while (++i < (int)mod->vn_count)
		free(mod->vn_data[i]);
	free(mod_data);
	free(ind_data);
	free(mod->vt_data);
	free(mod->vn_data);
}

static void	set_vtn_data(t_model *mod, float **mod_data,
unsigned int **ind_data, int i)
{
	if (mod->vt_count)
	{
		mod_data[ind_data[i][0]][3] = mod->vt_data[ind_data[i][3]][0];
		mod_data[ind_data[i][0]][4] = mod->vt_data[ind_data[i][3]][1];
		mod_data[ind_data[i][1]][3] = mod->vt_data[ind_data[i][4]][0];
		mod_data[ind_data[i][1]][4] = mod->vt_data[ind_data[i][4]][1];
		mod_data[ind_data[i][2]][3] = mod->vt_data[ind_data[i][5]][0];
		mod_data[ind_data[i][2]][4] = mod->vt_data[ind_data[i][5]][1];
	}
	if (mod->vn_count && mod->is_normal)
	{
		mod_data[ind_data[i][0]][5] = mod->vn_data[ind_data[i][6]][0];
		mod_data[ind_data[i][0]][6] = mod->vn_data[ind_data[i][6]][1];
		mod_data[ind_data[i][0]][7] = mod->vn_data[ind_data[i][6]][2];
		mod_data[ind_data[i][1]][5] = mod->vn_data[ind_data[i][7]][0];
		mod_data[ind_data[i][1]][6] = mod->vn_data[ind_data[i][7]][1];
		mod_data[ind_data[i][1]][7] = mod->vn_data[ind_data[i][7]][2];
		mod_data[ind_data[i][2]][5] = mod->vn_data[ind_data[i][8]][0];
		mod_data[ind_data[i][2]][6] = mod->vn_data[ind_data[i][8]][1];
		mod_data[ind_data[i][2]][7] = mod->vn_data[ind_data[i][8]][2];
	}
}

static void	set_v_data(t_model *mod, float **mod_data)
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
}

void		fill_verticies(t_model *mod, float **mod_data,
unsigned int **ind_data)
{
	int i;
	int j;
	int k;

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
		set_vtn_data(mod, mod_data, ind_data, i);
	}
	set_v_data(mod, mod_data);
	recenter(mod);
	free_data(mod, mod_data, ind_data);
}
