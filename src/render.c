/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebednar <ebednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 15:14:58 by ebednar           #+#    #+#             */
/*   Updated: 2020/10/23 22:50:31 by ebednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	unbind(void)
{
	glBindVertexArray(0);
	glUseProgram(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void	vertex_buffer(t_render *rend, const void *data, unsigned int size)
{
	glGenBuffers(1, &rend->vbo_id);
	glBindBuffer(GL_ARRAY_BUFFER, rend->vbo_id);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void	index_buffer(t_render *rend, const unsigned int *data
, unsigned int count)
{
	glGenBuffers(1, &rend->ibo_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rend->ibo_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int),
	data, GL_STATIC_DRAW);
}

void	set_buffers(t_render *rend, t_model *mod)
{
	glGenVertexArrays(1, &rend->vao);
	glBindVertexArray(rend->vao);
	vertex_buffer(rend, mod->verticies, mod->v_count * 8 * sizeof(float));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
	(GLvoid*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
	(GLvoid*)(5 * sizeof(float)));
	index_buffer(rend, mod->indicies, mod->i_count * 3);
	glBindVertexArray(0);
	glGenVertexArrays(1, &rend->lightvao);
	glBindVertexArray(rend->lightvao);
	glBindBuffer(GL_ARRAY_BUFFER, rend->vbo_id);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
	(GLvoid*)(3 * sizeof(float)));
	unbind();
}

void	start_frame(t_render *rend)
{
	rend->current_frame = glfwGetTime();
	rend->delta_time = rend->current_frame - rend->old_frame;
	rend->old_frame = rend->current_frame;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
