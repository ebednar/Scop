#include "scop.h"

void	fillTexture(float** modData, unsigned int** indData, int vCount, int iCount)
{
	int i;

	i = vCount;
	i = 0;
	while (i < iCount)
	{
		modData[indData[i][0]][3] = 0.0;
		modData[indData[i][0]][4] = 0.0;
		modData[indData[i][1]][3] = 2.0;
		modData[indData[i][1]][4] = 0.0;
		modData[indData[i][2]][3] = 1.0;
		modData[indData[i][2]][4] = 2.0;
		i ++;
	}
}

void	fillNormal(float** modData, int vCount)
{
	int		i;

	i = -1;
	while(++i < vCount)
	{
		modData[i][6] = 1.0f;
		modData[i][5] = 0.0f;
		modData[i][7] = 0.0f;
	}
}