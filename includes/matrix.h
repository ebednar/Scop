#ifndef MATRIX_H
# define MATRIX_H

typedef struct {
	float *projMat;
	float *viewMat;
	float **modelMat;
	float *vp;
	float *mvp;
	float *rotMat;
	float *lookAt;
	unsigned int	modelCount;
} matrices;

void			InitMat(matrices *mat);
void			OrtMatrix(matrices *mat);
void			ViewMatrix(matrices *mat, float tx, float ty, float tz);
void			TranslateMatrix(float *mat, float tx, float ty, float tz);
float*			MultyplyMat(float *result, float *mat1, float *mat2);
void			PerspMatrix(matrices *mat);
void			RotateXMatrix(float *mat, float angle);
void			RotateYMatrix(float *mat, float angle);
void			RotateZMatrix(float *mat, float angle);
void			updateMatrix(matrices *mat);

#endif