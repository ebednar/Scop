/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebednar <ebednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 18:10:36 by ebednar           #+#    #+#             */
/*   Updated: 2020/03/15 23:03:53 by ebednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H
# define GL_SILENCE_DEPRECATION
# include <stdio.h>
# include <math.h>
# include "libft.h"
# define GLFW_INCLUDE_GLCOREARB
# include <GLFW/glfw3.h>
# include "matrix.h"

# define WIDTH 1280
# define HEIGHT 720

typedef struct {
	unsigned int modShader;
	unsigned int lightShader;
} shaders;

typedef struct {
	float* pos;
	float* direction;
	float* right;
	float* up;
	float* front;
	float	lastX;
	float	lastY;
	float	yaw;
	float	pitch;
} camera;

typedef struct {
	unsigned int	vboID;
	unsigned int	iboID;
	unsigned int	texture;
	shaders			shader;
	camera*			cam;
	unsigned int	vao;
	unsigned int	lightvao;
	float			switchLight[3];
	char	keys[1024];
} render;

typedef struct {
	unsigned char	header[54];
	unsigned int	dataOffset;
	unsigned int	width;
	unsigned int	height;
	unsigned int	size;
	unsigned char	*data;
} image;

typedef struct {
	float*	verticies;
	int		vCount;
	unsigned int*	indicies;
	int		iCount;
	float	pos[3];
} model;

void			initGLFW();
void			makeContext(GLFWwindow* window);
void			error(int code);
void			initBaseData(GLFWwindow* window, render* rend, matrices* mat);
unsigned int	createShader(char* vertShader, char* fragShader);
void			key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void			mouse_callback(GLFWwindow* window, double xpos, double ypos);
void			vertexBuffer(render* rend, const void* data, unsigned int size);
void			bindBuffer(unsigned int renderID);
void			indexBuffer(render* rend, const unsigned int* data, unsigned int count);
unsigned int	loadImage(const char* filePath);
void			camera_(camera* camera, matrices* mat);
void			camera_init(camera* camera);
void			normalize(float *vec);
void			cross(float* vec3, float* vec1, float* vec2);
void			do_movement(render* rend, float delta);
void			lightUniform(unsigned int shader);
void			loadModel(model* mod, char* path);
void			fillTexture(float** modData, unsigned int** indData, int vCount, int iCount);
void			fillNormal(float** modData, int vCount);

#endif