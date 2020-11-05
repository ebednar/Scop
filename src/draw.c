/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebednar <ebednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 15:14:27 by ebednar           #+#    #+#             */
/*   Updated: 2020/11/05 20:03:39 by ebednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void	scene2(t_render *rend, t_matrices *mat, t_model *mod)
{
	int		i;
	float	angle;

	i = -1;
	while (++i < 10)
	{
		translate_matrix(mat->model_mat, 2.0f * (i % 4), 0.0f, 2.0f * (i / 3));
		angle = 10.0f * i;
		rotate_matrix(mat->model_mat, angle, angle * 2,
		(float)glfwGetTime() * 40.0f);
		glUniformMatrix4fv(glGetUniformLocation(rend->shader.mod_shader, "u_M"),
		1, GL_TRUE, mat->model_mat);
		glDrawElements(GL_TRIANGLES, mod->i_count * 3, GL_UNSIGNED_INT, 0);
	}
}

static void	init_frame(t_render *rend)
{
	glUseProgram(rend->shader.mod_shader);
	glUniform3f(glGetUniformLocation(rend->shader.mod_shader, "u_lightSwitch"),
	rend->light_switch[0], rend->light_switch[1], rend->light_switch[2]);
	glUniform1i(glGetUniformLocation(rend->shader.mod_shader, "u_state"),
	rend->state);
	glUniform3f(glGetUniformLocation(rend->shader.mod_shader, "u_viewPos"),
	rend->cam->pos[0], rend->cam->pos[1], rend->cam->pos[2]);
	glUniform3f(glGetUniformLocation(rend->shader.mod_shader,
	"spotLight.direction"), rend->cam->front[0], rend->cam->front[1],
	rend->cam->front[2]);
}

void		draw_frame(t_render *rend, t_matrices *mat, unsigned int vao
, t_model *mod)
{
	init_frame(rend);
	glBindVertexArray(vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rend->ibo_id);
	glBindTexture(GL_TEXTURE_2D, rend->texture);
	camera_m(rend->cam, mat);
	glUniformMatrix4fv(glGetUniformLocation(rend->shader.mod_shader, "u_P"), 1,
	GL_TRUE, mat->proj_mat);
	glUniformMatrix4fv(glGetUniformLocation(rend->shader.mod_shader, "u_V"), 1,
	GL_TRUE, mat->look_at);
	if (rend->scene == -1)
	{
		translate_matrix(mat->model_mat, rend->x, rend->y, rend->z);
		rotate_matrix(mat->model_mat, rend->ang_x, rend->ang_y, rend->ang_z);
		glUniformMatrix4fv(glGetUniformLocation(rend->shader.mod_shader, "u_M")
		, 1, GL_TRUE, mat->model_mat);
		glDrawElements(GL_TRIANGLES, mod->i_count * 3, GL_UNSIGNED_INT, 0);
	}
	else
		scene2(rend, mat, mod);
}

void		draw_point_light(t_render *rend, t_matrices *mat, unsigned int vao
, t_model *mod)
{
	glUseProgram(rend->shader.light_shader);
	glUniform1i(glGetUniformLocation(rend->shader.light_shader
	, "u_Texture"), 0);
	glBindVertexArray(vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rend->ibo_id);
	glUniformMatrix4fv(glGetUniformLocation(rend->shader.light_shader
	, "u_P"), 1, GL_TRUE, mat->proj_mat);
	glUniformMatrix4fv(glGetUniformLocation(rend->shader.light_shader
	, "u_V"), 1, GL_TRUE, mat->look_at);
	translate_matrix(mat->model_mat, 2.5, 1.0, 1.5);
	scale_matrix(mat->model_mat, 0.05, 0.05, 0.05);
	glUniformMatrix4fv(glGetUniformLocation(rend->shader.light_shader
	, "u_M"), 1, GL_TRUE, mat->model_mat);
	glDrawElements(GL_TRIANGLES, mod->i_count * 3, GL_UNSIGNED_INT, 0);
}

void		draw_cycle(t_render *rend, t_matrices *mat, t_model *mod)
{
	start_frame(rend);
	draw_frame(rend, mat, rend->vao, mod);
	draw_point_light(rend, mat, rend->lightvao, mod);
	unbind();
	glfwSwapBuffers(rend->window);
}
