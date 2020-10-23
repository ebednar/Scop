/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebednar <ebednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 15:15:03 by ebednar           #+#    #+#             */
/*   Updated: 2020/10/23 22:13:00 by ebednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void		read_header(t_image *img)
{
	unsigned char	*ptr;

	ptr = img->header + 10;
	ft_memcpy(&img->data_offset, ptr, 4);
	ptr = img->header + 34;
	ft_memcpy(&img->size, ptr, 4);
	ptr = img->header + 18;
	ft_memcpy(&img->width, ptr, 4);
	ptr = img->header + 22;
	ft_memcpy(&img->height, ptr, 4);
	if (img->size == 0)
		img->size = img->width * img->height * 3;
	if (img->data_offset == 0)
		img->data_offset = 54;
}

static void		read_data(t_image *img, int fd)
{
	ssize_t	readed;
	char	buff[img->data_offset];

	readed = read(fd, buff, img->data_offset - 54);
	readed = read(fd, img->data, img->size);
}

static int		apply_texture(t_image *img)
{
	unsigned int	texture;

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img->width,
	img->height, 0, GL_BGR, GL_UNSIGNED_BYTE, img->data);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	free(img->data);
	return (texture);
}

unsigned int	load_image(const char *file_path)
{
	int		fd;
	int		texture;
	ssize_t	readed;
	t_image	img;

	if ((fd = open(file_path, O_RDONLY)) < 0)
		error(3);
	readed = read(fd, img.header, 54);
	if (img.header[0] != 'B' || img.header[1] != 'M')
	{
		ft_putendl("incorrect bmp file");
		return (0);
	}
	read_header(&img);
	img.data = (unsigned char *)malloc(sizeof(unsigned char) * img.size);
	read_data(&img, fd);
	close(fd);
	texture = apply_texture(&img);
	return (texture);
}
