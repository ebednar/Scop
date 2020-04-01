#include "scop.h"

static void		ReadHeader(image *img)
{
	unsigned char*	ptr;
	ptr = img->header + 10;
	ft_memcpy(&img->dataOffset, ptr, 4);
	printf("data offset %d\n", img->dataOffset);
	ptr = img->header + 34;
	ft_memcpy(&img->size, ptr, 4);
	printf("image size %d\n", img->size);
	ptr = img->header + 18;
	ft_memcpy(&img->width, ptr, 4);
	printf("image width %d\n", img->width);
	ptr = img->header + 22;
	ft_memcpy(&img->height, ptr, 4);
	printf("image height %d\n", img->height);
	if (img->size == 0)
		img->size = img->width * img->height * 3;
	if (img->dataOffset == 0)
		img->dataOffset = 54;
}

static void		ReadData(image *img, int fd)
{
	ssize_t	readed;
	char	buff[img->dataOffset];

	readed = read(fd, buff, img->dataOffset - 54);
	readed = read(fd, img->data, img->size);
}

static int		ApplyTexture(image *img)
{
	unsigned int	texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img->width, img->height, 0, GL_BGR, GL_UNSIGNED_BYTE, img->data);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	free(img->data);
	return texture;
}

unsigned int	LoadImage(const char* filePath)
{
	int		fd;
	ssize_t	readed;
	image	img;

	if ((fd = open(filePath, O_RDONLY)) < 0)
		Error(3);
	readed = read(fd, img.header, 54);
	if ( img.header[0]!='B' || img.header[1]!='M' )
	{
    	ft_putendl("incorrect bmp file");
    	return 0;
	}
	ReadHeader(&img);
	img.data = (unsigned char *)malloc(sizeof(unsigned char) * img.size);
	ReadData(&img, fd);
	close(fd);
	int texture = ApplyTexture(&img);
	return texture;
}