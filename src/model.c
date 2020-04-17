#include "scop.h"

static void	readFloat(float* data, char* line, int offset)
{
	char*	ptr1;
	char*	ptr2;
	int	i;

	i = -1;
	while (line[++i] != '\0')
	{
		if ((line[i] < '0' || line[i] > '9') && line[i] != '.' && line[i] != '-' && line[i] != '+')
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
	int				fd;
	char*			line;
	unsigned int	vtCount;
	unsigned int	vnCount;

	checkFile(path);
	mod->isTexture = 1;
	mod->vCount = 0;
	mod->iCount = 0;
	vtCount = 0;
	vnCount = 0;
	mod->materialName = NULL;
	if ((fd = open(path, O_RDONLY)) < 0)
		error(3);
	while(get_next_line(fd, &line))
	{
		if (line[0] == 'v' && line[1] == ' ')
			mod->vCount++;
		if (line[0] == 'v' && line[1] == 't')
			vtCount++;
		if (line[0] == 'v' && line[1] == 'n')
			vnCount++;
		if (line[0] == 'f')
			checkIndecies(mod, line);
		if (!(ft_strncmp(line, "mtllib", 6)))
			readMaterial(mod, line);
		free(line);
	}
	close(fd);
	if (mod->vCount == 0 || mod->iCount == 0 || vnCount > mod->vCount || vtCount > mod->vCount)
		error(6);
	printf("verticies in model %d\n", mod->vCount);
	printf("faces in model %d\n", mod->iCount);
}

void		loadModel(model* mod, char* path)
{
	float**			modData;
	unsigned int**	indData;
	unsigned int	i;

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