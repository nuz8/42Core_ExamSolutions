/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 01:58:07 by pamatya           #+#    #+#             */
/*   Updated: 2025/11/27 01:16:30 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

/*
Allowed functions and globals: malloc, calloc, realloc, free, fopen, fclose,
getline, fscanf, fputs, fprintf, stderr, stdout, stdin, errno
*/

typedef struct bsq
{
	char**	map;
	int**	dpTable;
	char*	line;
	size_t	len;
	ssize_t	read;
	int		rows;
	int		width;
	int		index_mxX;
	int		index_mxY;
	int		bSq;
	char	empty;
	char	obs;
	char	full;
}	bsq;

int		solveBSQ(FILE *file);
void	init_bsq(bsq* obj);
void	getControlChars(bsq* obj);
int		init_map(bsq *obj, FILE* file);
int		init_dpTable(bsq *obj);
void	fillDPTable(bsq* obj);
void	findIndex(bsq* obj);
void	fillMap(bsq* obj);
void	printBSQ(bsq* obj);
void	cleanAll(bsq *obj);
void	print_struct_bsq(bsq* obj);

int	main(int ac, char** av)
{
	int		i = 0, ret = 1;
	FILE*	file;

	if (ac == 1)
	{
		FILE*	file = stdin;
		return (solveBSQ(file));
	}
	else
	{
		while (++i < ac)
		{
			file = fopen(av[i], "r");
			if (!file)
			{
				fprintf(stderr, "Error: cannot open file: %s\n", av[i]);
				continue;
			}
			ret = solveBSQ(file);
			fclose(file);
		}
	}
	return (ret);
}

int	solveBSQ(FILE *file)
{
	bsq		*obj = malloc(sizeof(bsq));

	if (!obj)
		return (fprintf(stderr, "malloc error\n"), -1);
	init_bsq(obj);
	obj->read = getline(&obj->line, &obj->len, file);
	if (obj->read != -1)
		getControlChars(obj);
	if (init_map(obj, file) == -1)
		return (1);
	if (init_dpTable(obj) == -1)
		return (1);
	fillDPTable(obj);
	findIndex(obj);
	fillMap(obj);
	printBSQ(obj);
	cleanAll(obj);
	return (0);
}

void	init_bsq(bsq* obj)
{
	obj->map = NULL;
	obj->dpTable = NULL;
	obj->line = NULL;
	obj->len = 0;
	obj->read = 0;
	obj->rows = 0;
	obj->width = 0;
	obj->empty = 0;
	obj->obs = 0;
	obj->full = 0;
	obj->index_mxX = 0;
	obj->index_mxY = 0;
	obj->bSq = 0;
}

void	getControlChars(bsq* obj)
{
	size_t	len = strlen(obj->line);
	
	if (len == 6)
	{
		char rows[3] = {obj->line[0], obj->line[1], 0};
		obj->rows = atoi(rows);			// this fn needs to be coded
		obj->empty = obj->line[2];
		obj->obs = obj->line[3];
		obj->full = obj->line[4];
	}
	else
	{
		char rows[2] = {obj->line[0], 0};
		obj->rows = atoi(rows);			// this fn needs to be coded
		obj->empty = obj->line[1];
		obj->obs = obj->line[2];
		obj->full = obj->line[3];
	}
}

int	init_map(bsq *obj, FILE* file)
{
	int	i = -1, j = -1;

	obj->read = getline(&obj->line, &obj->len, file);	// line now has already the 1st row of the map
	obj->width = (int)(obj->read) - 1;

	obj->map = malloc((obj->rows + 1) * sizeof(char*));
	if (!obj->map)
		return (cleanAll(obj), -1);

	obj->map[obj->rows] = NULL;
	while (++i < obj->rows)
	{
		obj->map[i] = calloc((obj->width + 1), sizeof(char));
		if (!obj->map[i])
			return (cleanAll(obj), -1);
	}
	while (++j < (obj->rows) && !(obj->read < 0))
	{
		i = -1;
		while (++i < (obj->width))
			obj->map[j][i] = obj->line[i];
		obj->read = getline(&obj->line, &obj->len, file);
	}
	return (0);
}

int	init_dpTable(bsq *obj)
{
	int	i = -1;
	obj->dpTable = malloc((obj->rows + 1) * sizeof(int*));
	if (!obj->dpTable)
		return (cleanAll(obj), -1);
	obj->dpTable[obj->rows] = NULL;
	while (++i < obj->rows)
	{
		obj->dpTable[i] = calloc((obj->width), sizeof(int));
		if (!obj->dpTable[i])
			return (fprintf(stderr, "Calloc error\n"), cleanAll(obj), -1);
	}
	return (0);
}

void	fillDPTable(bsq* obj)
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

void	findIndex(bsq* obj)
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

void	fillMap(bsq* obj)
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

void	printBSQ(bsq* obj)
{
	if (obj->map)
	{
		int	i = -1;
		while (obj->map[++i])
			fprintf(stdout, "%s\n", obj->map[i]);
	}
}

void	cleanAll(bsq *obj)
{
	int	i = -1;
	if (obj->map)
	{
		while (obj->map[++i])
			free(obj->map[i]);
		free(obj->map);
		obj->map = NULL;
	}

	if (obj->dpTable)
	{
		i = -1;
		while (obj->dpTable[++i])
			free(obj->dpTable[i]);
		free(obj->dpTable);
		obj->dpTable = NULL;
	}
	if (obj->line)
		free(obj->line);
	if (obj)
		free(obj);
}

void	print_struct_bsq(bsq* obj)
{	
	int	i, j;
	
	fprintf(stdout, "rows	:	%d\n", obj->rows);
	fprintf(stdout, "width	:	%d\n", obj->width);
	fprintf(stdout, "empty	:	%c\n", obj->empty);
	fprintf(stdout, "obs	:	%c\n", obj->obs);
	fprintf(stdout, "full	:	%c\n", obj->full);
	fprintf(stdout, "index	:	(%d, %d)\n", obj->index_mxX, obj->index_mxY);
	fprintf(stdout, "bSq	:	%d\n", obj->bSq);
	fprintf(stdout, "\n");

	// printing the map
	if (obj->map)
	{
		i = -1;
		while (obj->map[++i])
			fprintf(stdout, "%d:\t:%d\t%s\n", i + 1, obj->width, obj->map[i]);
	}
	fprintf(stdout, "\n");

	// printing dpTable
	if (obj->dpTable)
	{
		j = -1;
		while (++j < obj->rows)
		{
			i = -1;
			fprintf(stdout, "%d:\t:%d\t", j + 1, obj->width);
			while (++i < obj->width)
				fprintf(stdout, "%d", obj->dpTable[j][i]);
			fprintf(stdout, "\n");
		}
	}
	fprintf(stdout, "\n");
}
