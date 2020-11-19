/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_vert.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebednar <ebednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 18:31:14 by ebednar           #+#    #+#             */
/*   Updated: 2020/11/19 18:59:21 by ebednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void		read_float(float *data, char *line, int offset)
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
