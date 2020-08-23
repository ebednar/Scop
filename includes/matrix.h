#ifndef MATRIX_H
# define MATRIX_H

typedef struct {
	float			*projMat;
	float			*viewMat;
	float			*modelMat;
	float			*rotMat;
	float			*lookAt;
} matrices;

void			init_mat(matrices *mat);
void			ort_matrix(matrices *mat);
void			view_matrix(matrices *mat, float tx, float ty, float tz);
void			translate_matrix(float *mat, float tx, float ty, float tz);
float*			multyply_mat(float *result, float *mat1, float *mat2);
void			persp_matrix(matrices *mat);
void			rotate_matrix(float *mat, float a, float b, float c);
void			scale_matrix(float *mat, float tx, float ty, float tz);

#endif