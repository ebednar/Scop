#include "scop.h"

static void	readSpecular(model* mod, char* line)
{
	char*	ptr1;
	char*	ptr2;
	int	i;

	i = -1;
	while (line[++i] != '\0')
	{
		if ((line[i] < '0' || line[i] > '9') && line[i] != '.')
			line[i] = ' ';
	}
	i = -1;
	ptr1 = line + 2;
	while (++i < 3)
	{
		mod->specular[i] = strtof(ptr1, &ptr2);
		ptr1 = ptr2;
	}
}

void	loadMaterial(model* mod)
{
	int		fd;
	char*	str;
	char*	line;

	str = ft_strjoin("res/models/", mod->materialName);
	free(mod->materialName);
	if ((fd = open(str, O_RDONLY)) < 0)
	{
		ft_putendl("no material file");
		close(fd);
		free(str);
		return ;
	}
	free(str);
	while(get_next_line(fd, &line))
	{
		if (line[0] == 'N' && line[1] == 's')
			mod->shininess = ft_atoi(line + 2);
		if (line[0] == 'K' && line[1] == 's')
			readSpecular(mod, line);
		free(line);
	}
	close(fd);
}

void	readMaterial(model* mod, char* str)
{
	int count;

	str = str + 7;
	count = ft_strlen(str);
	if (!(mod->materialName = (char *)malloc(count * sizeof(char) + 1)))
		error(4);
	ft_strcpy(mod->materialName, str);
	ft_putstr("material ");
	ft_putendl(mod->materialName);
	loadMaterial(mod);
}
