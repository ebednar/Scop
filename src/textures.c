#include "scop.h"

static void		ReadFile(image *img, int fd)
{
	ssize_t	readed;
	char	buff[img->dataOffset];

	readed = read(fd, buff, img->dataOffset - 54);
	readed = read(fd, img->data, img->size);
	printf("%zd\n", readed);
}

static void		ApplyTexture(image *img)
{
	unsigned int	texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img->width, img->height, 0, GL_BGR, GL_UNSIGNED_BYTE, img->data);
	glGenerateMipmap(GL_TEXTURE_2D);
	free(img->data);
	glBindTexture(GL_TEXTURE_2D, 0);
}

unsigned int	LoadImage(const char* filePath)
{
	int		fd;
	ssize_t	readed;
	image	img;
	unsigned char*	ptr;

	if ((fd = open(filePath, O_RDONLY)) < 0)
		Error(3);
	readed = read(fd, img.header, 54);
	if ( img.header[0]!='B' || img.header[1]!='M' )
	{
    	ft_putendl("incorrect bmp file");
    	return 0;
	}
	ptr = img.header + 10;
	ft_memcpy(&img.dataOffset, ptr, 4);
	printf("data offset %d\n", img.dataOffset);
	ptr = img.header + 34;
	ft_memcpy(&img.size, ptr, 4);
	printf("image size %d\n", img.size);
	ptr = img.header + 18;
	ft_memcpy(&img.width, ptr, 4);
	printf("image width %d\n", img.width);
	ptr = img.header + 22;
	ft_memcpy(&img.height, ptr, 4);
	printf("image height %d\n", img.height);
	img.data = (unsigned char *)malloc(sizeof(unsigned char) * img.size);
	ReadFile(&img, fd);
	close(fd);
	ApplyTexture(&img);
	return 1;
}