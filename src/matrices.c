#include "scop.h"

float*	OrtMatrix()
{
	float right = 960.0f;
	float left = 0.0f;
	float top = 540.0f;
	float bottom = 0.0f;
	float far = 1.0f;
	float near = -1.0f;
	float tx = - (right + left)/(right - left);
	float ty = - (top + bottom)/(top - bottom);	
	float tz = - (far + near)/(far - near);
	float* ortMat =(float *)malloc(16 * sizeof(float));
	int i;
	i = 0;
	while (i < 16)
	{
		ortMat[i] = 0.0f;
		i++;
	}
	ortMat[0] = 2.0f / (right - left);
	ortMat[3] = tx;
	ortMat[5] = 2.0f / (top - bottom);
	ortMat[7] = ty;
	ortMat[10] = - 2.0f / (far - near);
	ortMat[11] = tz;
	ortMat[15] = 1.0f;
	return ortMat;
}

float*	ViewMatrix()
{
	float tx = - 100.0f;
	float ty = 0.0f;
	float tz = 0.0f;
	float* viewMat =(float *)malloc(16 * sizeof(float));
	ft_bzero(viewMat, 16);
	viewMat[0] = 1.0f;
	viewMat[3] = tx;
	viewMat[5] = 1.0f;
	viewMat[7] = ty;
	viewMat[10] = 1.0f;
	viewMat[11] = tz;
	viewMat[15] = 1.0f;
	return viewMat;
}

float*	MultyplyMat(float *mat1, float *mat2)
{
	int i;
	int j;
	int k;
	j = 0;
	i = 0;
	k = 0;
	float* result =(float *)malloc(16 * sizeof(float)); 
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
	free(mat1);
	free(mat2);
	return result;
}