#include "scop.h"

void	checkFile(char* path)
{	
	char*	ptr;

	ptr = path + ft_strlen(path) - 4;
	if (ft_strcmp(".obj", ptr))
		error(5);
	//ft_putchar(*(ft_strcpy(".obj", path + ft_strlen(path) - 4)));
}

void		error(int code)
{
	if (code == 1)
		ft_putendl("glwf init error");
	if (code == 2)
		ft_putendl("glwf window creation error");
	if (code == 3)
		ft_putendl("can't read file");
	if (code == 4)
		ft_putendl("memory allocation failed");
	if (code == 5)
		ft_putendl("Usage: ./scop [file_name.obj]");
	if (code == 6)
		ft_putendl("corrupted file");
	exit(code);
}