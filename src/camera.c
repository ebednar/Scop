#include "scop.h"

void	Normalize(float *vec)
{
	float length;

	length = sqrt(vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2]);
	vec[0] = vec[0] / length;
	vec[1] = vec[1] / length;
	vec[2] = vec[2] / length;
}

void	Cross(float* vec3, float* vec1, float* vec2)
{
	vec3[0] = vec1[1] * vec2[2] - vec1[2] * vec2[1];
	vec3[1] = vec1[2] * vec2[0] - vec1[0] * vec2[2];
	vec3[2] = vec1[0] * vec2[1] - vec1[1] * vec2[0];
}

void	Camera_init(camera* cam)
{
	int i;

	if (!(cam->pos = (float *)malloc(3 * sizeof(float ))))
		Error(4);
	if (!(cam->direction = (float *)malloc(3 * sizeof(float ))))
		Error(4);
	if (!(cam->up = (float *)malloc(3 * sizeof(float ))))
		Error(4);
	if (!(cam->right = (float *)malloc(3 * sizeof(float ))))
		Error(4);
	if (!(cam->front = (float *)malloc(3 * sizeof(float ))))
		Error(4);
	i = -1;
	while (++i < 3)
	{
		cam->pos[i] = 0.0;
		cam->front[i] = 0.0;
	}
	cam->pos[2] = 3.0f;
	cam->front[2] = -1.0f;
}

void	Camera_(camera* camera, matrices* mat)
{
	float up[3] = {0.0, 1.0, 0.0};
	int i;

	i = -1;
	while (++i < 3)
		camera->direction[i] = - camera->front[i];
	Normalize(camera->direction);
	Cross(camera->right, up, camera->direction);
	Normalize(camera->right);
	Cross(camera->up, camera->direction, camera->right);
	float mat1[16] = {1.0f, 0.0f, 0.0f, -camera->pos[0], 0.0f, 1.0f, 0.0f, -camera->pos[1], 0.0f, 0.0f, 1.0f, -camera->pos[2], 0.0f, 0.0f, 0.0f, 1.0f};
	float mat2[16] = {camera->right[0], camera->right[1], camera->right[2], 0.0, camera->up[0], camera->up[1], camera->up[2], 0.0f, camera->direction[0], camera->direction[1], camera->direction[2], 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};
	MultyplyMat(mat->lookAt, mat2, mat1);
	}
