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
	ft_putendl(line);
	while (*ptr1 != '\0')
	{
		if (*ptr1 >= '0' && *ptr1 <= '9')
		{
			while ((*ptr1 >= '0' && *ptr1 <= '9') || *ptr1 == '/')
			{
				ptr1++;
			}
			count++;
		}
		else
			ptr1++;
	}
	if (count == 3)
		mod->i_count++;
	else if (count == 4)
		mod->i_count += 2;
	else
		error(6);
}

static void	div_square(unsigned int **data, int *numb, int count, int *ind)
{
	int i;

	i = -1;
	while (++i < 3)
		data[*numb][i] = ind[i];
	(*numb)++;
	if (count == 4)
	{
		data[*numb][0] = ind[2];
		data[*numb][1] = ind[3];
		data[*numb][2] = ind[0];
		(*numb)++;
	}
}

void		read_int(unsigned int **data, int *numb, char *line)
{
	char	*ptr1;
	int		count;
	int		ind[4];

	count = 0;
	ptr1 = line + 1;
	ft_putendl("read ind");
	while (*ptr1 != '\0')
	{
		if (*ptr1 >= '0' && *ptr1 <= '9')
		{
			ind[count] = ft_atoi(ptr1) - 1;
			while ((*ptr1 >= '0' && *ptr1 <= '9') || *ptr1 == '/')
				ptr1++;
			count++;
		}
		else
			ptr1++;
	}
	div_square(data, numb, count, ind);
}
