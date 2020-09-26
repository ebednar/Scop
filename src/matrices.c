/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrices.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebednar <ebednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 15:14:46 by ebednar           #+#    #+#             */
/*   Updated: 2020/08/23 15:15:10 by ebednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	init_mat(matrices *mat)
{
	unsigned int i;

	if (!(mat->modelMat = (float *)malloc(16 * sizeof(float))))
		error(4);
	if (!(mat->viewMat = (float *)malloc(16 * sizeof(float))))
		error(4);
	if (!(mat->projMat = (float *)malloc(16 * sizeof(float))))
		error(4);
	if (!(mat->rotMat = (float *)malloc(16 * sizeof(float))))
		error(4);
	if (!(mat->lookAt = (float *)malloc(16 * sizeof(float))))
		error(4);
	i = -1;
	while (++i < 16)
	{
		mat->modelMat[i] = 0.0f;
		mat->viewMat[i] = 0.0f;
		mat->projMat[i] = 0.0f;
		mat->rotMat[i] = 0.0f;
		mat->lookAt[i] = 0.0f;
	}
}

void	persp_matrix(matrices *mat)
{
	proj_matrix	matrix;
	float		tx;
	float		ty;
	float		tz;

	matrix.far = 100.0f;
	matrix.near = 0.1f;
	matrix.fov = 60.0f;
	matrix.right = matrix.near * tanf((matrix.fov / 2.0f) * M_PI / 180.0);
	matrix.left = - matrix.right;
	matrix.top = matrix.right * (float)HEIGHT / (float)WIDTH;
	matrix.bottom = - matrix.top;
	tx = 0.0f;
	ty = 0.0f;	
	tz = - (2.0f * matrix.far * matrix.near)/(matrix.far - matrix.near);
	mat->projMat[0] = matrix.near / matrix.right;
	mat->projMat[3] = tx;
	mat->projMat[5] = matrix.near / matrix.top;
	mat->projMat[7] = ty;
	mat->projMat[10] = - (matrix.far + matrix.near) / (matrix.far - matrix.near);
	mat->projMat[11] = tz;
	mat->projMat[14] = - 1.0f;
}

void	view_matrix(matrices *mat, float tx, float ty, float tz)
{
	int	i;

	i = -1;
	while (++i < 16)
		mat->viewMat[i] = 0.0;
	mat->viewMat[0] = 1.0f;
	mat->viewMat[3] = tx;
	mat->viewMat[5] = 1.0f;
	mat->viewMat[7] = ty;
	mat->viewMat[10] = 1.0f;
	mat->viewMat[11] = tz;
	mat->viewMat[15] = 1.0f;
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

float*	multyply_mat(float *result, float *mat1, float *mat2)
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
			ptr[k++] = mat1[i] * mat2[j] + mat1[i + 1] * mat2[j + 4] + mat1[i + 2]
			* mat2[j + 8] + mat1[i + 3] * mat2[j + 12];
		i += 4;
	}
	i = -1;
	while (++i < 16)
		result[i] = ptr[i];
	return result;
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
