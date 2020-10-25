/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebednar <ebednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 18:10:36 by ebednar           #+#    #+#             */
/*   Updated: 2020/10/23 22:10:10 by ebednar          ###   ########.fr       */
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

typedef struct		s_shaders
{
	unsigned int	mod_shader;
	unsigned int	light_shader;
}					t_shaders;

typedef struct		s_camera
{
	float			*pos;
	float			*direction;
	float			*right;
	float			*up;
	float			*front;
	float			last_x;
	float			last_y;
	float			yaw;
	float			pitch;
}					t_camera;

typedef struct		s_render
{
	GLFWwindow		*window;
	unsigned int	vbo_id;
	unsigned int	ibo_id;
	unsigned int	texture;
	t_shaders		shader;
	t_camera		*cam;
	unsigned int	vao;
	unsigned int	lightvao;
	float			light_switch[3];
	char			keys[1024];
	char			fkeys[1024];
	float			delta_time;
	float			old_frame;
	float			current_frame;
	float			x;
	float			y;
	float			z;
	float			ang_x;
	float			ang_y;
	float			ang_z;
	short int		state;
	short int		wire;
	short int		scene;
}					t_render;

typedef struct		s_image
{
	unsigned char	header[54];
	unsigned int	data_offset;
	unsigned int	width;
	unsigned int	height;
	unsigned int	size;
	unsigned char	*data;
}					t_image;

typedef struct		s_model
{
	float			*verticies;
	unsigned int	v_count;
	unsigned int	*indicies;
	unsigned int	i_count;
	int				is_texture;
	char			*material_name;
	float			specular[3];
	int				shininess;
}					t_model;

void				init_glfw();
void				make_context(t_render *rend);
void				error(int code);
void				init_base_data(t_render *rend, t_matrices *mat
, t_model *mod);
void				start_pos(t_render *rend);
unsigned int		create_shader(char *vert_shader, char *frag_shader);
void				key_callback(t_render *rend);
void				mouse_callback(GLFWwindow *window, double xpos
, double ypos);
void				vertex_buffer(t_render *rend, const void *data
, unsigned int size);
void				bind_buffer(unsigned int render_id);
void				set_buffers(t_render *rend, t_model *mod);
void				unbind();
void				index_buffer(t_render *rend, const unsigned int *data
, unsigned int count);
unsigned int		load_image(const char *file_path);
void				camera_m(t_camera *camera, t_matrices *mat);
void				camera_init(t_camera *camera);
void				normalize(float *vec);
void				cross(float *vec3, float *vec1, float *vec2);
void				do_movement(t_render *rend, float delta);
void				light_uniform(unsigned int shader, t_model *mod);
void				load_model(t_model *mod, char *path);
void				check_indecies(t_model *mod, char *line);
void				fill_texture(float **mod_data, t_model *mod);
void				fill_normal(float **mod_data, unsigned int **ind_data
, int i_count);
void				fill_verticies(t_model *mod, float **mod_data
, unsigned int **ind_data);
void				read_int(unsigned int **data, int *numb, char *line);
void				start_frame(t_render *rend);
void				draw_cycle(t_render *rend, t_matrices *mat, t_model *mod);
void				draw_frame(t_render *rend, t_matrices *mat, unsigned int vao
, t_model *mod);
void				draw_point_light(t_render *rend, t_matrices *mat
, unsigned int vao, t_model *mod);
void				read_material(t_model *mod, char *str);
void				check_file(char *path);

#endif
