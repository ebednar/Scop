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
#include <stdio.h>
#include <stdlib.h>

# include "libft.h"
# define GLFW_INCLUDE_GLCOREARB
# include <GLFW/glfw3.h>

typedef struct {
	unsigned int	renderID;
} vertexBuf;

typedef struct {
	unsigned int	renderID;
} indexBuf;

typedef struct {
	unsigned char	header[54];
	unsigned int	dataOffset;
	unsigned int	width;
	unsigned int	height;
	unsigned int	size;
	unsigned char	*data;
} image;

void			Error(int code);
unsigned int	CreateShader();
void			key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void			VertexBuffer(vertexBuf* vb, const void* data, unsigned int size);
void			BindBuffer(unsigned int renderID);
void			IndexBuffer(indexBuf* ib, const unsigned int* data, unsigned int count);
void			BindIndex(unsigned int renderID);
unsigned int	LoadImage(const char* filePath);

#endif