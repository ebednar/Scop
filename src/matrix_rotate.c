/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_rotate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebednar <ebednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 15:14:49 by ebednar           #+#    #+#             */
/*   Updated: 2020/08/23 15:15:10 by ebednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void	rotate_x_matrix(float *mat, float angle)
{
	float	ptr[16];
	int		i;

	i = -1;
	while (++i < 16)
		ptr[i] = 0.0;
	angle = angle * M_PI / 180.0;
	ptr[0] = 1;
	ptr[5] = cos(angle);
	ptr[6] = -sin(angle);
	ptr[9] = sin(angle);
	ptr[10] = cos(angle);
	ptr[15] = 1;
	multyply_mat(ptr, mat, ptr);
	i = -1;
	while (++i < 16)
		mat[i] = ptr[i];
}

static void	rotate_y_matrix(float *mat, float angle)
{
	float	ptr[16];
	int		i;

	i = -1;
	while (++i < 16)
		ptr[i] = 0.0;
	angle = angle * M_PI / 180.0;
	ptr[0] = cos(angle);
	ptr[2] = sin(angle);
	ptr[5] = 1;
	ptr[8] = -sin(angle);
	ptr[10] = cos(angle);
	ptr[15] = 1;
	multyply_mat(ptr, mat, ptr);
	i = -1;
	while (++i < 16)
		mat[i] = ptr[i];
}

static void	rotate_z_matrix(float *mat, float angle)
{
	float	ptr[16];
	int		i;

	i = -1;
	while (++i < 16)
		ptr[i] = 0.0;
	angle = angle * M_PI / 180.0;
	ptr[0] = cos(angle);
	ptr[1] = -sin(angle);
	ptr[4] = sin(angle);
	ptr[5] = cos(angle);
	ptr[10] = 1;
	ptr[15] = 1;
	multyply_mat(ptr, mat, ptr);
	i = -1;
	while (++i < 16)
		mat[i] = ptr[i];
}

void	rotate_matrix(float *mat, float a, float b, float c)
{
	rotate_x_matrix(mat, a);
	rotate_y_matrix(mat, b);
	rotate_z_matrix(mat, c);
}
