/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_indicies.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebednar <ebednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 15:14:56 by ebednar           #+#    #+#             */
/*   Updated: 2020/10/23 22:02:08 by ebednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void		check_indecies(t_model *mod, char *line)
{
	char	*ptr1;
	int		count;

	count = 0;
	ptr1 = line + 1;
	while (*ptr1 != '\0')
		if (*ptr1 >= '0' && *ptr1 <= '9')
		{
			while ((*ptr1 >= '0' && *ptr1 <= '9') || *ptr1 == '/')
				ptr1++;
			count++;
		}
		else
			ptr1++;
	if (count == 3)
		mod->i_count++;
	else if (count == 4)
		mod->i_count += 2;
	else
		error(6);
}

#include <stdio.h>

static void	div_square(unsigned int **data, int *numb, int count, int **ind)
{
	int i;
	int j;
	int k;

	j = -1;
	k = 0;
	while (++j < 3)
	{
		i = -1;
		while (++i < 3)
		{
			
			data[*numb][k] = ind[i][j];
			k++;
		}	
	}
	(*numb)++;
	if (count == 4)
	{
		i = -1;
		while (++i < 3)
		{
			data[*numb][0 + i * 3] = ind[2][i];
			data[*numb][1 + i * 3] = ind[3][i];
			data[*numb][2 + i * 3] = ind[0][i];
		}
		(*numb)++;
	}
}

void		read_int(unsigned int **data, int *numb, char *line)
{
	char	*ptr1;
	int		count;
	int		**ind;
	int		i;

	i = -1;
	ind = (int **)malloc(4 * sizeof(int *));
	while (++i < 4)
	{
		ind[i] = (int *)malloc(3 * sizeof(int));
		ft_bzero(ind[i], 12);
	}
	count = 0;
	ptr1 = line + 1;
	while (*ptr1 != '\0')
	{
		if (*ptr1 >= '0' && *ptr1 <= '9')
		{
			ind[count][0] = ft_atoi(ptr1) - 1;
			while ((*ptr1 >= '0' && *ptr1 <= '9'))
				ptr1++;
			if (*ptr1 == '/')
			{
				ptr1++;
				ind[count][1] = ft_atoi(ptr1) - 1;
			}
			else
				ind[count][1] = ind[count][0];
			while ((*ptr1 >= '0' && *ptr1 <= '9'))
				ptr1++;
			if (*ptr1 == '/')
			{
				ptr1++;
				ind[count][2] = ft_atoi(ptr1) - 1;
			}
			else
				ind[count][2] = ind[count][0];
			while ((*ptr1 >= '0' && *ptr1 <= '9'))
				ptr1++;
			count++;
		}
		else
			ptr1++;
	}
	div_square(data, numb, count, ind);
	i = -1;
	while (++i < 4)
		free(ind[i]);
	free(ind);
}
