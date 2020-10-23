/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebednar <ebednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 15:14:21 by ebednar           #+#    #+#             */
/*   Updated: 2020/10/23 22:22:39 by ebednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void		normalize(float *vec)
{
	float	length;

	length = sqrt(vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2]);
	vec[0] = vec[0] / length;
	vec[1] = vec[1] / length;
	vec[2] = vec[2] / length;
}

void		cross(float *vec3, float *vec1, float *vec2)
{
	vec3[0] = vec1[1] * vec2[2] - vec1[2] * vec2[1];
	vec3[1] = vec1[2] * vec2[0] - vec1[0] * vec2[2];
	vec3[2] = vec1[0] * vec2[1] - vec1[1] * vec2[0];
}

void		camera_init(t_camera *cam)
{
	cam->last_x = WIDTH / 2;
	cam->last_y = HEIGHT / 2;
	cam->yaw = -90.0f;
	cam->pitch = 0.0f;
	if (!(cam->pos = (float *)malloc(3 * sizeof(float ))))
		error(4);
	if (!(cam->direction = (float *)malloc(3 * sizeof(float ))))
		error(4);
	if (!(cam->up = (float *)malloc(3 * sizeof(float ))))
		error(4);
	if (!(cam->right = (float *)malloc(3 * sizeof(float ))))
		error(4);
	if (!(cam->front = (float *)malloc(3 * sizeof(float ))))
		error(4);
	cam->pos[0] = 0.0;
	cam->front[0] = 0.0;
	cam->pos[1] = 0.0;
	cam->front[1] = 0.0;
	cam->pos[2] = 3.0f;
	cam->front[2] = -1.0f;
}

static void	base_mat(t_camera *cam, float *mat1, float *mat2)
{
	ft_bzero(mat1, 16 * 4);
	mat1[0] = 1.0f;
	mat1[3] = -cam->pos[0];
	mat1[5] = 1.0f;
	mat1[7] = -cam->pos[1];
	mat1[10] = 1.0f;
	mat1[11] = -cam->pos[2];
	mat1[15] = 1.0f;
	ft_bzero(mat2, 16 * 4);
	mat2[0] = cam->right[0];
	mat2[1] = cam->right[1];
	mat2[2] = cam->right[2];
	mat2[4] = cam->up[0];
	mat2[5] = cam->up[1];
	mat2[6] = cam->up[2];
	mat2[8] = cam->direction[0];
	mat2[9] = cam->direction[1];
	mat2[10] = cam->direction[2];
	mat2[15] = 1.0f;
}

void		camera_m(t_camera *cam, t_matrices *mat)
{
	float	up[3];
	int		i;
	float	mat1[16];
	float	mat2[16];

	ft_bzero(up, 12);
	up[1] = 1.0f;
	i = -1;
	while (++i < 3)
		cam->direction[i] = -cam->front[i];
	normalize(cam->direction);
	cross(cam->right, up, cam->direction);
	normalize(cam->right);
	cross(cam->up, cam->direction, cam->right);
	base_mat(cam, mat1, mat2);
	multyply_mat(mat->look_at, mat2, mat1);
}
