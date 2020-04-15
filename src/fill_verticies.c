#include "scop.h"

void	fillTexture(float** modData, model* mod)
{
	int i;

	mod->isTexture = 0;
	i = 0;
	while (i < mod->vCount)
	{
		if (i % 3 == 0)
		{
			modData[i][3] = 0.9f;
			modData[i][4] = 0.1f;
		}
		else if (i % 3 == 1)
		{
			modData[i][3] = 0.1f;
			modData[i][4] = 0.9f;
		}
		else if (i % 3 == 2)
		{
			modData[i][3] = 0.02f;
			modData[i][4] = 0.02f;
		}
		i ++;
	}
}

void	fillNormal(float** modData, unsigned int** indData, int iCount)
{
	int		i;
	float	vec1[3];
	float	vec2[3];
	float	norm[3];

	i = -1;
	while(++i < iCount)
	{
		vec1[0] = modData[indData[i][1]][0] - modData[indData[i][0]][0];
		vec1[1] = modData[indData[i][1]][1] - modData[indData[i][0]][1];
		vec1[2] = modData[indData[i][1]][2] - modData[indData[i][0]][2];
		vec2[0] = modData[indData[i][2]][0] - modData[indData[i][0]][0];
		vec2[1] = modData[indData[i][2]][1] - modData[indData[i][0]][1];
		vec2[2] = modData[indData[i][2]][2] - modData[indData[i][0]][2];
		cross(norm, vec1, vec2);
		modData[indData[i][0]][5] = norm[0];
		modData[indData[i][1]][5] = norm[0];
		modData[indData[i][2]][5] = norm[0];
		modData[indData[i][0]][6] = norm[1];
		modData[indData[i][1]][6] = norm[1];
		modData[indData[i][2]][6] = norm[1];
		modData[indData[i][0]][7] = norm[2];
		modData[indData[i][1]][7] = norm[2];
		modData[indData[i][2]][7] = norm[2];
	}
}

static void	freeData(model* mod, float** modData, unsigned int** indData)
{
	int i;

	i = -1;
	while (++i < mod->vCount)
		free(modData[i]);
	i = -1;
	while (++i < mod->iCount)
		free(indData[i]);
	free(modData);
	free(indData);
}

void	fillVerticies(model* mod, float** modData, unsigned int** indData)
{
	int i;
	int j;
	int k;

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
	freeData(mod, modData, indData);
}
