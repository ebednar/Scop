/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrices.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebednar <ebednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 15:14:46 by ebednar           #+#    #+#             */
/*   Updated: 2020/10/23 22:21:22 by ebednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	init_mat(t_matrices *mat)
{
	unsigned int i;

	if (!(mat->model_mat = (float *)malloc(16 * sizeof(float))))
		error(4);
	if (!(mat->view_mat = (float *)malloc(16 * sizeof(float))))
		error(4);
	if (!(mat->proj_mat = (float *)malloc(16 * sizeof(float))))
		error(4);
	if (!(mat->rot_mat = (float *)malloc(16 * sizeof(float))))
		error(4);
	if (!(mat->look_at = (float *)malloc(16 * sizeof(float))))
		error(4);
	i = -1;
	while (++i < 16)
	{
		mat->model_mat[i] = 0.0f;
		mat->view_mat[i] = 0.0f;
		mat->proj_mat[i] = 0.0f;
		mat->rot_mat[i] = 0.0f;
		mat->look_at[i] = 0.0f;
	}
}

void	view_matrix(t_matrices *mat, float tx, float ty, float tz)
{
	int	i;

	i = -1;
	while (++i < 16)
		mat->view_mat[i] = 0.0;
	mat->view_mat[0] = 1.0f;
	mat->view_mat[3] = tx;
	mat->view_mat[5] = 1.0f;
	mat->view_mat[7] = ty;
	mat->view_mat[10] = 1.0f;
	mat->view_mat[11] = tz;
	mat->view_mat[15] = 1.0f;
}

void	translate_matrix(float *mat, float tx, float ty, float tz)
{
	int	i;

	i = -1;
	while (++i < 16)
		mat[i] = 0.0;
	mat[0] = 1.0f;
	mat[3] = tx;
	mat[5] = 1.0f;
	mat[7] = ty;
	mat[10] = 1.0f;
	mat[11] = tz;
	mat[15] = 1.0f;
}

float	*multyply_mat(float *result, float *mat1, float *mat2)
{
	float	ptr[16];
	int		j;
	int		i;
	int		k;

	i = 0;
	k = 0;
	while (i < 16)
	{
		j = -1;
		while (++j < 4)
			ptr[k++] = mat1[i] * mat2[j] + mat1[i + 1] * mat2[j + 4]
			+ mat1[i + 2]
			* mat2[j + 8] + mat1[i + 3] * mat2[j + 12];
		i += 4;
	}
	i = -1;
	while (++i < 16)
		result[i] = ptr[i];
	return (result);
}

void	scale_matrix(float *mat, float tx, float ty, float tz)
{
	int		i;
	float	ptr[16];

	i = -1;
	while (++i < 16)
		ptr[i] = 0.0;
	ptr[0] = tx;
	ptr[5] = ty;
	ptr[10] = tz;
	ptr[15] = 1.0f;
	multyply_mat(ptr, mat, ptr);
	i = -1;
	while (++i < 16)
		mat[i] = ptr[i];
}
