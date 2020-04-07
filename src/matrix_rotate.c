#include "scop.h"

void	rotateMatrix(float *mat, float a, float b, float c)
{
	float ptr[16];
	int		i;

	i = -1;
	while (++i < 16)
		ptr[i] = 0.0;
	a = a * M_PI / 180.0;
	b = b * M_PI / 180.0;
	c = c * M_PI / 180.0;
	ptr[0] = 1;
	ptr[5] = cos(a);
	ptr[6] = -sin(a);
	ptr[9] = sin(a);
	ptr[10] = cos(a);
	ptr[15] = 1;
	multyplyMat(ptr, mat, ptr);
	i = -1;
	while (++i < 16)
		mat[i] = ptr[i];
}


void	rotateXMatrix(float *mat, float angle)
{
	float ptr[16];
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
	multyplyMat(ptr, mat, ptr);
	i = -1;
	while (++i < 16)
		mat[i] = ptr[i];
}

void	rotateYMatrix(float *mat, float angle)
{
	float ptr[16];
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
	multyplyMat(ptr, mat, ptr);
	i = -1;
	while (++i < 16)
		mat[i] = ptr[i];
}

void	rotateZMatrix(float *mat, float angle)
{
	float ptr[16];
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
	multyplyMat(ptr, mat, ptr);
	i = -1;
	while (++i < 16)
		mat[i] = ptr[i];
}