/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebednar <ebednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 18:10:36 by ebednar           #+#    #+#             */
/*   Updated: 2020/03/15 21:37:10 by ebednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H

#include <stdio.h>
#include <stdlib.h>

# include "libft.h"
# define GLFW_INCLUDE_GLCOREARB
# include <GLFW/glfw3.h>

void Error(int code);
unsigned int CreateShader(const char* vertexShader, const char* fragmentShader);

#endif