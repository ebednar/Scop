#ifndef MATRIX_H
# define MATRIX_H

typedef struct {
	float *projMat;
	float *viewMat;
	float *modelMat;
	float *vp;
	float *mvp;
} matrices;

void			InitMat(matrices *mat);
void			OrtMatrix(matrices *mat);
void			ViewMatrix(matrices *mat, float tx, float ty, float tz);
void			ModelMatrix(matrices *mat, float tx, float ty, float tz);
float*			MultyplyMat(float *result, float *mat1, float *mat2);
void			PerspMatrix(matrices *mat);

#endif