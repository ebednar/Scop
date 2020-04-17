#include "scop.h"

void	checkIndecies(model* mod, char* line)
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
	else
		error(6);
}

static void divSquare(unsigned int** data, int* numb, int count, int* ind)
{
	int i;

	i = -1;
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

void		readInt(unsigned int** data, int* numb, char* line)
{
	char*	ptr1;
	int		count;
	int		ind[4];

	count = 0;
	ptr1 = line + 1;
	while (*ptr1 != '\0')
	{
		if (*ptr1 >= '0' && *ptr1 <= '9')
		{
			ind[count] = ft_atoi(ptr1) - 1;
			while ((*ptr1 >= '0' && *ptr1 <= '9') || *ptr1 == '/')
				ptr1++;
			count++;
		}
		else
			ptr1++;
	}
	divSquare(data, numb, count, ind);
}