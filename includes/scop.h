/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebednar <ebednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 18:10:36 by ebednar           #+#    #+#             */
/*   Updated: 2020/08/23 15:52:51 by ebednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H
# define GL_SILENCE_DEPRECATION
# define GLFW_INCLUDE_GLCOREARB
# include <GLFW/glfw3.h>
# include <math.h>
# include "libft.h"
# include "matrix.h"

# define WIDTH 1280
# define HEIGHT 720

typedef struct {
	unsigned int modShader;
	unsigned int lightShader;
} shaders;

typedef struct {
	float	*pos;
	float	*direction;
	float	*right;
	float	*up;
	float	*front;
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
	camera			*cam;
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
	float			*verticies;
	unsigned int	vCount;
	unsigned int	*indicies;
	unsigned int	iCount;
	int				isTexture;
	char			*materialName;
	float			specular[3];
	int				shininess;
} model;

void			init_glfw();
void			make_context(render *rend);
void			error(int code);
void			init_base_data(render *rend, matrices *mat, model *mod);
void			start_pos(render *rend);
unsigned int	create_shader(char *vertShader, char *fragShader);
void			key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);
void			mouse_callback(GLFWwindow *window, double xpos, double ypos);
void			vertex_buffer(render *rend, const void* data, unsigned int size);
void			bind_buffer(unsigned int renderID);
void			set_buffers(render *rend, model *mod);
void			unbind();
void			index_buffer(render *rend, const unsigned int *data, unsigned int count);
unsigned int	load_image(const char *filePath);
void			camera_(camera *camera, matrices *mat);
void			camera_init(camera *camera);
void			normalize(float *vec);
void			cross(float *vec3, float *vec1, float *vec2);
void			do_movement(render *rend, float delta);
void			light_uniform(unsigned int shader, model *mod);
void			load_model(model *mod, char *path);
void			check_indecies(model *mod, char *line);
void			fill_texture(float **modData, model *mod);
void			fill_normal(float **modData, unsigned int **indData, int iCount);
void			fill_verticies(model *mod, float **modData, unsigned int **indData);
void			read_int(unsigned int **data, int *numb, char *line);
void			start_frame(render *rend);
void			draw_cycle(render *rend, matrices *mat, model *mod);
void			draw_frame(render *rend, matrices *mat, unsigned int vao, model *mod);
void			draw_point_light(render *rend, matrices *mat, unsigned int vao, model *mod);
void			read_material(model *mod, char *str);
void			check_file(char *path);

#endif