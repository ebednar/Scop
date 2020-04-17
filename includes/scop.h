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
	GLFWwindow		*window;
	unsigned int	vboID;
	unsigned int	iboID;
	unsigned int	texture;
	shaders			shader;
	camera*			cam;
	unsigned int	vao;
	unsigned int	lightvao;
	float			lightSwitch[3];
	char			keys[1024];
	float			deltaTime;
	float			oldFrame;
	float			currentFrame;
	float			x;
	float			y;
	float			z;
	float			angX;
	float			angY;
	float			angZ;
	short int		state;
	short int		wire;
	short int		scene;
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
	float*			verticies;
	unsigned int	vCount;
	unsigned int*	indicies;
	unsigned int	iCount;
	int				isTexture;
	char*			materialName;
	float			specular[3];
	int				shininess;
} model;

void			initGLFW();
void			makeContext(render* rend);
void			error(int code);
void			initBaseData(render* rend, matrices* mat, model* mod);
void			startPos(render* rend);
unsigned int	createShader(char* vertShader, char* fragShader);
void			key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void			mouse_callback(GLFWwindow* window, double xpos, double ypos);
void			vertexBuffer(render* rend, const void* data, unsigned int size);
void			bindBuffer(unsigned int renderID);
void			setBuffers(render* rend, model* mod);
void			unbind();
void			indexBuffer(render* rend, const unsigned int* data, unsigned int count);
unsigned int	loadImage(const char* filePath);
void			camera_(camera* camera, matrices* mat);
void			camera_init(camera* camera);
void			normalize(float *vec);
void			cross(float* vec3, float* vec1, float* vec2);
void			do_movement(render* rend, float delta);
void			lightUniform(unsigned int shader, model* mod);
void			loadModel(model* mod, char* path);
void			checkIndecies(model* mod, char* line);
void			fillTexture(float** modData, model* mod);
void			fillNormal(float** modData, unsigned int** indData, int iCount);
void			fillVerticies(model* mod, float** modData, unsigned int** indData);
void			readInt(unsigned int** data, int* numb, char* line);
void			startFrame(render* rend);
void			drawCycle(render* rend, matrices* mat, model* mod);
void			drawFrame(render* rend, matrices* mat, unsigned int vao, model* mod);
void			drawPointLight(render* rend, matrices* mat, unsigned int vao, model* mod);
void			readMaterial(model* mod, char* str);
void			checkFile(char* path);

#endif