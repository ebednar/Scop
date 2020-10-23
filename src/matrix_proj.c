/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_proj.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebednar <ebednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 20:26:07 by ebednar           #+#    #+#             */
/*   Updated: 2020/10/23 22:18:09 by ebednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	persp_matrix(t_matrices *mat)
{
	t_proj_matrix	matrix;
	float			tx;
	float			ty;
	float			tz;

	matrix.far = 100.0f;
	matrix.near = 0.1f;
	matrix.fov = 60.0f;
	matrix.right = matrix.near * tanf((matrix.fov / 2.0f) * M_PI / 180.0);
	matrix.left = -matrix.right;
	matrix.top = matrix.right * (float)HEIGHT / (float)WIDTH;
	matrix.bottom = -matrix.top;
	tx = 0.0f;
	ty = 0.0f;
	tz = -(2.0f * matrix.far * matrix.near) / (matrix.far - matrix.near);
	mat->proj_mat[0] = matrix.near / matrix.right;
	mat->proj_mat[3] = tx;
	mat->proj_mat[5] = matrix.near / matrix.top;
	mat->proj_mat[7] = ty;
	mat->proj_mat[10] = -(matrix.far + matrix.near)
	/ (matrix.far - matrix.near);
	mat->proj_mat[11] = tz;
	mat->proj_mat[14] = -1.0f;
}
