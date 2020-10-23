/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_light_u.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebednar <ebednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 21:00:45 by ebednar           #+#    #+#             */
/*   Updated: 2020/10/23 22:10:59 by ebednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void	light_uniform2(unsigned int shader)
{
	glUniform3f(glGetUniformLocation(shader, "pointLight.ambient"),
	0.1f, 0.1f, 0.1f);
	glUniform3f(glGetUniformLocation(shader, "pointLight.diffuse"),
	0.8f, 0.8f, 0.8f);
	glUniform3f(glGetUniformLocation(shader, "pointLight.specular"),
	1.0f, 1.0f, 1.0f);
	glUniform3f(glGetUniformLocation(shader, "pointLight.position"),
	2.5f, 1.0f, 1.5f);
	glUniform1f(glGetUniformLocation(shader, "spotLight.cutoff"),
	cos(6.5f * M_PI / 180));
	glUniform1f(glGetUniformLocation(shader, "spotLight.outerCutoff"),
	cos(12.5f * M_PI / 180));
	glUniform3f(glGetUniformLocation(shader, "spotLight.ambient"),
	0.1f, 0.1f, 0.1f);
	glUniform3f(glGetUniformLocation(shader, "spotLight.diffuse"),
	0.8f, 0.8f, 0.8f);
	glUniform3f(glGetUniformLocation(shader, "spotLight.specular"),
	0.9f, 0.9f, 0.9f);
	glUniform1f(glGetUniformLocation(shader, "spotLight.constant"), 1.0f);
	glUniform1f(glGetUniformLocation(shader, "spotLight.linear"), 0.09f);
	glUniform1f(glGetUniformLocation(shader, "spotLight.quadratic"), 0.032f);
}

void		light_uniform(unsigned int shader, t_model *mod)
{
	glUniform1i(glGetUniformLocation(shader, "u_Texture"), 0);
	glUniform1i(glGetUniformLocation(shader, "u_isText"), mod->is_texture);
	glUniform1i(glGetUniformLocation(shader, "material.diffuse"), 0);
	glUniform3f(glGetUniformLocation(shader, "material.specular"),
	mod->specular[0], mod->specular[1], mod->specular[2]);
	glUniform1f(glGetUniformLocation(shader, "material.shininess"),
	mod->shininess);
	glUniform3f(glGetUniformLocation(shader, "dirLight.direction"),
	-0.2f, -1.0f, -0.3f);
	glUniform3f(glGetUniformLocation(shader, "dirLight.ambient"),
	0.05f, 0.05f, 0.05f);
	glUniform3f(glGetUniformLocation(shader, "dirLight.diffuse"),
	0.15f, 0.15f, 0.15f);
	glUniform3f(glGetUniformLocation(shader, "dirLight.specular"),
	0.3f, 0.3f, 0.3f);
	glUniform1f(glGetUniformLocation(shader, "pointLight.constant"), 1.0f);
	glUniform1f(glGetUniformLocation(shader, "pointLight.linear"), 0.09f);
	glUniform1f(glGetUniformLocation(shader, "pointLight.quadratic"), 0.032f);
	light_uniform2(shader);
}
