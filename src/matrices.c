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

void	initMat(matrices *mat)
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

void	perspMatrix(matrices *mat)
{
	float right;
	float left;
	float top;
	float bottom;
	float far = 100.0f;
	float near = 0.1f;
	float fov = 60.0f;
	right = near * tanf((fov / 2.0f) * M_PI / 180.0);
	left = - right;
	top = right * (float)HEIGHT / (float)WIDTH;
	bottom = - top;
	float tx = 0.0f;
	float ty = 0.0f;	
	float tz = - (2.0f * far * near)/(far - near);
	mat->projMat[0] = near / right;
	mat->projMat[3] = tx;
	mat->projMat[5] = near / top;
	mat->projMat[7] = ty;
	mat->projMat[10] = - (far + near) / (far - near);
	mat->projMat[11] = tz;
	mat->projMat[14] = - 1.0f;
}

void	ortMatrix(matrices *mat)
{
	float right = 1.0f;
	float left = - 1.0f;
	float top = 1.0f;
	float bottom = -1.0f;
	float far = 10.0f;
	float near = 0.1f;
	float tx = - (right + left)/(right - left);
	float ty = - (top + bottom)/(top - bottom);	
	float tz = - (far + near)/(far - near);
	mat->projMat[0] = 2.0f / (right - left);
	mat->projMat[3] = tx;
	mat->projMat[5] = 2.0f / (top - bottom);
	mat->projMat[7] = ty;
	mat->projMat[10] = - 2.0f / (far - near);
	mat->projMat[11] = tz;
	mat->projMat[15] = 1.0f;
}

void	viewMatrix(matrices *mat, float tx, float ty, float tz)
{
	int i;

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

void	translateMatrix(float *mat, float tx, float ty, float tz)
{
	int i;

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

float*	multyplyMat(float *result, float *mat1, float *mat2)
{
	float ptr[16];
	int i;
	int j;
	int k;
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

void	scaleMatrix(float *mat, float tx, float ty, float tz)
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
	multyplyMat(ptr, mat, ptr);
	i = -1;
	while (++i < 16)
		mat[i] = ptr[i];
}
