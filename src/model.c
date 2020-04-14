#include "scop.h"

static void	checkIndecies(model* mod, char* line)
{
	char*	ptr1;
	int		count;

	count = 0;
	ptr1 = line + 1;
	while (*ptr1 != '\0')
	{
		if (*ptr1 >= '0' && *ptr1 <= '9')
		{
			while ((*ptr1 >= '0' && *ptr1 <= '9') || *ptr1 == '/')
			{
				ptr1++;
			}
			count++;
		}
		else
			ptr1++;
	}
	if (count == 3)
		mod->iCount++;
	else if (count == 4)
		mod->iCount += 2;
}

static void	readFloat(float* data, char* line, int offset)
{
	char*	ptr1;
	char*	ptr2;
	int	i;

	i = -1;
	while (line[++i] != '\0')
	{
		if (line[i] == 'f')
			line[i] = ' ';
	}
	i = -1;
	ptr1 = line + 2;
	while (++i < (offset == 3 ? 2 : 3))
	{
		data[i + offset] = strtof(ptr1, &ptr2);
		ptr1 = ptr2;
	}
}

static void readVert(float** modData, unsigned int** indData, char* path, model* mod)
{
	char*	line;
	int		fd;
	int		vert[4];
	int		i;

	if ((fd = open(path, O_RDONLY)) < 0)
		error(3);
	i = -1;
	while (++i < 4)
		vert[i] = 0;
	while(get_next_line(fd, &line))
	{
		if (line[0] == 'v' && line[1] == ' ')
			readFloat(modData[vert[0]++], line, 0);
		if (line[0] == 'v' && line[1] == 't')
			readFloat(modData[vert[1]++], line, 3);
		if (line[0] == 'v' && line[1] == 'n')
			readFloat(modData[vert[2]++], line, 5);
		if (line[0] == 'f')
			readInt(indData, &(vert[3]), line);
		free(line);
	}
	if (vert[1] == 0)
		fillTexture(modData, mod);
	if (vert[2] == 0)
	 	fillNormal(modData, indData, mod->iCount);
	close(fd);
}

static void	vertCount(model* mod, char* path)
{
	int		fd;
	char*	line;

	mod->isTexture = 1;
	mod->vCount = 0;
	mod->iCount = 0;
	if ((fd = open(path, O_RDONLY)) < 0)
		error(3);
	while(get_next_line(fd, &line))
	{
		if (line[0] == 'v' && line[1] == ' ')
			mod->vCount++;
		if (line[0] == 'f')
			checkIndecies(mod, line);
		free(line);
	}
	close(fd);
	printf("verticies in model %d\n", mod->vCount);
	printf("faces in model %d\n", mod->iCount);
}

void		loadModel(model* mod, char* path)
{
	float**	modData;
	unsigned int**	indData;
	int i;

	vertCount(mod, path);
	if (!(modData = (float **)malloc(mod->vCount * sizeof(float *))))
		error(4);
	if (!(indData = (unsigned int **)malloc(mod->iCount * sizeof(unsigned int *))))
		error(4);
	i = -1;
	while (++i < mod->vCount)
		if (!(modData[i] = (float *)malloc(8 * sizeof(float))))
			error(4);
	i = -1;
	while (++i < mod->iCount)
		if (!(indData[i] = (unsigned int *)malloc(3 * sizeof(unsigned int))))
			error(4);
	readVert(modData, indData, path, mod);
	if (!(mod->verticies = (float *)malloc((8 * mod->vCount) * sizeof(float))))
			error(4);
	if (!(mod->indicies = (unsigned int *)malloc((3 * mod->iCount) * sizeof(unsigned int))))
			error(4);
	fillVerticies(mod, modData, indData);
}