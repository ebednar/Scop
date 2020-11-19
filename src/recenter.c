/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recenter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebednar <ebednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 18:49:31 by ebednar           #+#    #+#             */
/*   Updated: 2020/11/19 18:53:53 by ebednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void	offset_mod(t_model *mod, float x, float z)
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

void		recenter(t_model *mod)
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
