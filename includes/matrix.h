#ifndef MATRIX_H
# define MATRIX_H

typedef struct {
	float			*projMat;
	float			*viewMat;
	float			**modelMat;
	float			*vp;
	float			*mvp;
	float			*rotMat;
	float			*lookAt;
	unsigned int	modelCount;
} matrices;

void			initMat(matrices *mat);
void			ortMatrix(matrices *mat);
void			viewMatrix(matrices *mat, float tx, float ty, float tz);
void			translateMatrix(float *mat, float tx, float ty, float tz);
float*			multyplyMat(float *result, float *mat1, float *mat2);
void			perspMatrix(matrices *mat);
void			rotateXMatrix(float *mat, float angle);
void			rotateYMatrix(float *mat, float angle);
void			rotateZMatrix(float *mat, float angle);
void			scaleMatrix(float *mat, float tx, float ty, float tz);

#endif