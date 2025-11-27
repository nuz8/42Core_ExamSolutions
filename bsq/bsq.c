/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 01:58:07 by pamatya           #+#    #+#             */
/*   Updated: 2025/11/27 20:49:39 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

int		solveBSQ(FILE *file);

static void	fillDPTable(bsq* obj);
static void	findIndex(bsq* obj);
static void	fillMap(bsq* obj);
static void	printBSQ(bsq* obj);

int	solveBSQ(FILE *file)
{
	bsq		*obj = malloc(sizeof(bsq));

	if (!obj)
		return (fprintf(stderr, "malloc error\n"), -1);
	init_bsq(obj, file);
	fillDPTable(obj);
	findIndex(obj);
	fillMap(obj);
	printBSQ(obj);
	cleanAll(obj);
	return (0);
}

static void	fillDPTable(bsq* obj)
{
	int		i = -1, j = -1, rows = obj->rows, width = obj->width;
	int		top, left, topLeft;
	char**	map = obj->map;
	int**	dpTable = obj->dpTable;
	char	empty = obj->empty, obs = obj->obs;

	// initializing first row of dpTable
	while (++i < width)
	{
		if (map[0][i] == empty)
			dpTable[0][i] = 1;
		else if (map[0][i] == obs)
			dpTable[0][i] = 0;
	}

	// initializing first column of dpTable
	while (++j < rows)
	{
		if (map[j][0] == empty)
			dpTable[j][0] = 1;
		else if (map[j][0] == obs)
			dpTable[j][0] = 0;
	}

	// filling the rest of the DP table
	j = 0;
	while (++j < rows)
	{
		i = 0;
		while (++i < width)
		{
			if (map[j][i] == empty)
			{
				top = dpTable[j - 1][i];
				left = dpTable[j][i - 1];
				topLeft = dpTable[j - 1][i - 1];
				dpTable[j][i] = 1 + (top < left ? (top < topLeft ? top : topLeft) : (left < topLeft ? left : topLeft));
			}
			else
				dpTable[j][i] = 0;
		}
	}
}

static void	findIndex(bsq* obj)
{
	int**	dpTable = obj->dpTable;
	int		i = -1, j = -1, rows = obj->rows, width = obj->width;
	int		ix = 0, iy = 0, newMax = 0;

	while (++j < rows)
	{
		i = -1;
		while (++i < width)
		{
			if (dpTable[j][i] > newMax)
			{
				newMax = dpTable[j][i];
				ix = i;
				iy = j;
			}
		}
	}
	obj->index_mxX = ix;
	obj->index_mxY = iy;
	obj->bSq = newMax;
}

static void	fillMap(bsq* obj)
{
	int		ex = obj->index_mxX, ey = obj->index_mxY;
	int		sx = ex - obj->bSq, sy = ey - obj->bSq;
	int		i = sx, j = sy;
	char**	map = obj->map;
	char	full = obj->full;

	while (++j <= ey)
	{
		i = sx;
		while (++i <= ex)
			map[j][i] = full;
	}
}

static void	printBSQ(bsq* obj)
{
	if (obj->map)
	{
		int	i = -1;
		while (obj->map[++i])
			fprintf(stdout, "%s\n", obj->map[i]);
	}
}
