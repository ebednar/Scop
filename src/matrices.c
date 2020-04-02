#include "scop.h"

void	InitMat(matrices *mat)
{
	int i;

	if (!(mat->modelMat = (float *)malloc(16 * sizeof(float))))
		Error(4);
	if (!(mat->viewMat = (float *)malloc(16 * sizeof(float))))
		Error(4);
	if (!(mat->projMat = (float *)malloc(16 * sizeof(float))))
		Error(4);
	if (!(mat->vp = (float *)malloc(16 * sizeof(float))))
		Error(4);
	if (!(mat->mvp = (float *)malloc(16 * sizeof(float))))
		Error(4);
	i = 0;
	while (i < 16)
	{
		mat->modelMat[i] = 0.0f;
		mat->viewMat[i] = 0.0f;
		mat->projMat[i] = 0.0f;
		i++;
	}
}

void	PerspMatrix(matrices *mat)
{
	float right;
	float left;
	float top;
	float bottom;
	float far = 100.0f;
	float near = 0.1f;
	float fov = 45.0f;
	right = near * tanf(fov / 2.0f);
	left = - right;
	top = left * (float)HEIGHT / (float)WIDTH;
	bottom = - top;
	printf("%f %f %f %f\n", right, left, top, bottom);
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

void	OrtMatrix(matrices *mat)
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

void	ViewMatrix(matrices *mat, float tx, float ty, float tz)
{
	mat->viewMat[0] = 1.0f;
	mat->viewMat[3] = tx;
	mat->viewMat[5] = 1.0f;
	mat->viewMat[7] = ty;
	mat->viewMat[10] = 1.0f;
	mat->viewMat[11] = tz;
	mat->viewMat[15] = 1.0f;
}

void	ModelMatrix(matrices *mat, float tx, float ty, float tz)
{
	mat->modelMat[0] = 1.0f;
	mat->modelMat[3] = tx;
	mat->modelMat[5] = 1.0f;
	mat->modelMat[7] = ty;
	mat->modelMat[10] = 1.0f;
	mat->modelMat[11] = tz;
	mat->modelMat[15] = 1.0f;
}

float*	MultyplyMat(float *result, float *mat1, float *mat2)
{
	int i;
	int j;
	int k;
	j = 0;
	i = 0;
	k = 0;
	while (i < 16)
	{
		while (j < 4)
		{
			result[k] = mat1[i] * mat2[j] + mat1[i + 1] * mat2[j + 4] + mat1[i + 2] * mat2[j + 8] + mat1[i + 3] * mat2[j + 12];
			j++;
			k++;
		}
		j = 0;
		i += 4;
	}
	return result;
}
