#include "scop.h"

static void	readInt(unsigned int** data, int* numb, char* line)
{
	char*	ptr1;
	int	i;
	int	count;
	int	ind[4];

	i = -1;
	count = 0;
	ptr1 = line + 1;
	while (*ptr1 != '\0')
	{
		if (*ptr1 >= '0' && *ptr1 <= '9')
		{
			ind[count] = ft_atoi(ptr1) - 1;
			while (*ptr1 >= '0' && *ptr1 <= '9')
				ptr1++;
			count++;
		}
		else
			ptr1++;
	}
	while (++i < 3)
		data[*numb][i] = ind[i];
	(*numb)++;
	if (count == 4)
	{
		data[*numb][0] = ind[2];
		data[*numb][1] = ind[3];
		data[*numb][2] = ind[0];
		(*numb)++;
	}
}

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
			while (*ptr1 >= '0' && *ptr1 <= '9')
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

static void readVert(float** modData, unsigned int** indData, char* path, int vCount, int iCount)
{
	char*	line;
	int		fd;
	int		vert[4];
	int		i;

	if ((fd = open(path, O_RDONLY)) < 0)
		error(3);
	i = iCount;
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
	 	fillTexture(modData, indData, vCount, iCount);
	 if (vert[2] == 0)
	 	fillNormal(modData, vCount);
	close(fd);
}

static void	vertCount(model* mod, char* path)
{
	int		fd;
	char*	line;

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
	int j;
	int k;

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
	printf("check\n");
	readVert(modData, indData, path, mod->vCount, mod->iCount);
	if (!(mod->verticies = (float *)malloc((8 * mod->vCount) * sizeof(float))))
			error(4);
	if (!(mod->indicies = (unsigned int *)malloc((3 * mod->iCount) * sizeof(unsigned int))))
			error(4);
	i = -1;
	k = -1;
	while (++i < mod->vCount)
	{
		j = -1;
		while (++j < 8)
			mod->verticies[++k] =  modData[i][j];
	}
	i = -1;
	k = -1;
	while (++i < mod->iCount)
	{
		j = -1;
		while (++j < 3)
			mod->indicies[++k] =  indData[i][j];
	}
	i = -1;
	while (++i < mod->vCount)
		free(modData[i]);
	i = -1;
	while (++i < mod->iCount)
		free(indData[i]);
	free(modData);
	free(indData);

	i = 0;
	printf("start\n");
	while (i < mod->iCount * 3)
	{
		printf ("%u ", mod->indicies[i]);
		i++;
		if (i % 3 == 0)
			printf ("\n");
	}
	printf("end\n");
}