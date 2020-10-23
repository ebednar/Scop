/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebednar <ebednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 21:48:26 by ebednar           #+#    #+#             */
/*   Updated: 2020/10/23 21:56:15 by ebednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

typedef struct	s_matrices
{
	float		*proj_mat;
	float		*view_mat;
	float		*model_mat;
	float		*rot_mat;
	float		*look_at;
}				t_matrices;

typedef struct	s_proj_matrix
{
	float		right;
	float		left;
	float		top;
	float		bottom;
	float		far;
	float		near;
	float		fov;
}				t_proj_matrix;

void			init_mat(t_matrices *mat);
void			view_matrix(t_matrices *mat, float tx, float ty, float tz);
void			translate_matrix(float *mat, float tx, float ty, float tz);
float			*multyply_mat(float *result, float *mat1, float *mat2);
void			persp_matrix(t_matrices *mat);
void			rotate_matrix(float *mat, float a, float b, float c);
void			scale_matrix(float *mat, float tx, float ty, float tz);

#endif
