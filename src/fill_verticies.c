#include "scop.h"

void	fillTexture(float** modData, int vCount)
{
	int i;

	ft_putendl("no texture\n");
	i = vCount;
	i = 0;
	while (i < vCount)
	{
		modData[i][3] = 0.0;
		modData[i][4] = 0.0;
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